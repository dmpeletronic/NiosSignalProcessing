##
##Legal Notice: (C)2007 Altera Corporation. All rights reserved. Your
##use of Altera Corporation's design tools, logic functions and other
##software and tools, and its AMPP partner logic functions, and any
##output files any of the foregoing (including device programming or
##simulation files), and any associated documentation or information are
##expressly subject to the terms and conditions of the Altera Program
##License Subscription Agreement or other applicable license agreement,
##including, without limitation, that your use is for the sole purpose
##of programming logic devices manufactured by Altera and sold by Altera
##or its authorized distributors. Please refer to the applicable
##agreement for further details.

if { ![info exists quartus(nameofexecutable)] || $quartus(nameofexecutable) != "quartus_sta" } {
	puts "Restarting in quartus_sta..."

	set cmd quartus_sta
	if { [info exists quartus(binpath)] } {
		set cmd [file join $quartus(binpath) $cmd]
	}

	set res [catch { exec $cmd -t [info script] batch } output]

	# This procedure is 'clever' in that it will write a message using
	# post_message if available and refert to puts otherwise.
	# if post_message fails, this procedure changes itself into one that
	# uses a simple 'puts' and continues.
	proc out { msg } {
		set type info
		regexp {^\W*(Info|Extra Info|Warning|Critical Warning|Error): (.*)$} $msg x type msg
		regsub " " $type _ type
		if { [catch { post_message -type $type $msg } res] } {
			proc out { msg } {puts $msg}
			out $msg
		}
	}

	foreach line [split $output \n] {
		out $line
	}
	return 0
}

set scriptname [info script]
if { ! [regexp (.*)_report_timing.tcl $scriptname _ corename] } {
	error "Couldn't determine corename from $scriptname"
}

if {[namespace which -variable ::argv] != "" && [lindex $::argv 0] == "batch" } {
	post_message -type info "Running in batch mode"

	set batch_mode_en 1
	set proj_name [glob *.qpf]
	if { ! [is_project_open] } {
		project_open -revision [get_current_revision $proj_name] $proj_name
	}

	catch {delete_timing_netlist }
	create_timing_netlist
	read_sdc

	set opcs [list]
	foreach_in_collection op [get_available_operating_conditions] {
		lappend opcs $op
	}

	update_timing_netlist
} else {
	set batch_mode_en 0
	set opcs [list ""]
}

set fpga_tREAD_CAPTURE_SETUP_ERROR 0
set fpga_tREAD_CAPTURE_HOLD_ERROR 0
set fpga_RESYNC_SETUP_ERROR 0
set fpga_RESYNC_HOLD_ERROR 0
set fpga_PA_DQS_SETUP_ERROR 0
set fpga_PA_DQS_HOLD_ERROR 0
set WR_DQS_DQ_SETUP_ERROR 0
set WR_DQS_DQ_HOLD_ERROR 0
set fpga_tCK_ADDR_CTRL_SETUP_ERROR 0
set fpga_tCK_ADDR_CTRL_HOLD_ERROR 0
set fpga_tDQSS_SETUP_ERROR 0
set fpga_tDQSS_HOLD_ERROR 0
set fpga_tDSSH_SETUP_ERROR 0
set fpga_tDSSH_HOLD_ERROR 0
set write_deskew_mode "none"
set read_deskew_mode "none"
set write_deskew_t10 0
set write_deskew_hc_t10 0
set write_deskew_t9i 0
set write_deskew_hc_t9i 0
set write_deskew_t9ni 0
set write_deskew_hc_t9ni 0
set write_deskew_range 0

set period 6.666

load_package atoms
read_atom_netlist

proc traverse_atom_path {atom_id atom_oport_id path} {
	# Return list of {atom oterm_id} pairs by tracing the atom netlist starting from the given atom_id through the given path
	# Path consists of list of {atom_type fanin|fanout|end <port_type> <-optional>}
	set result [list]
	if {[llength $path] > 0} {
		set path_point [lindex $path 0]
		set atom_type [lindex $path_point 0]
		set next_direction [lindex $path_point 1]
		set port_type [lindex $path_point 2]
		set atom_optional [lindex $path_point 3]
		if {[get_atom_node_info -key type -node $atom_id] == $atom_type} {
			if {$next_direction == "end"} {
				if {[get_atom_port_info -key type -node $atom_id -port_id $atom_oport_id -type oport] == $port_type} {
					lappend result [list $atom_id $atom_oport_id]
				}
			} elseif {$next_direction == "fanin"} {
				set atom_iport [get_atom_iport_by_type -node $atom_id -type $port_type]
				if {$atom_iport != -1} {
					set iport_fanin [get_atom_port_info -key fanin -node $atom_id -port_id $atom_iport -type iport]
					set source_atom [lindex $iport_fanin 0]
					set source_oterm [lindex $iport_fanin 1]
					set result [traverse_atom_path $source_atom $source_oterm [lrange $path 1 end]]
				}
			} elseif {$next_direction == "fanout"} {
				set atom_oport [get_atom_oport_by_type -node $atom_id -type $port_type]
				if {$atom_oport != -1} {
					set oport_fanout [get_atom_port_info -key fanout -node $atom_id -port_id $atom_oport -type oport]
					foreach dest $oport_fanout {
						set dest_atom [lindex $dest 0]
						set dest_iterm [lindex $dest 1]
						set fanout_result_list [traverse_atom_path $dest_atom -1 [lrange $path 1 end]]
						foreach fanout_result $fanout_result_list {
							if {[lsearch $result $fanout_result] == -1} {
								lappend result $fanout_result
							}
						}
					}
				}
			} else {
				error "Unexpected path"
			}
		} elseif {$atom_optional == "-optional"} {
			set result [traverse_atom_path $atom_id $atom_oport_id [lrange $path 1 end]]
		}
	}
	return $result
}

# Get the fitter name of the PLL output driving the given pin
proc traverse_to_ddio_out_pll_clock {pin msg_list_name} {
	upvar 1 $msg_list_name msg_list
	set result ""
	if {$pin != ""} {
		set pin_id [get_atom_node_by_name -name $pin]
		set pin_to_pll_path [list {IO_PAD fanin PADIN} {IO_OBUF fanin I} {PSEUDO_DIFF_OUT fanin I -optional} {DDIO_OUT fanin CLKHI -optional} {CLKBUF fanin INCLK -optional} {PLL end CLK}]
		set pll_id_list [traverse_atom_path $pin_id -1 $pin_to_pll_path]
		if {[llength $pll_id_list] == 1} {
			set atom_oterm_pair [lindex $pll_id_list 0]
			set result [get_atom_port_info -key name -node [lindex $atom_oterm_pair 0] -port_id [lindex $atom_oterm_pair 1] -type oport]
		} else {
			lappend msg_list "Error: PLL clock not found for $pin"
		}
	}
	return $result
}

proc verify_high_performance_timing_assumptions {instname pin_array_name write_deskew_t10} {
	upvar 1 $pin_array_name pins
	set num_errors 0
	load_package verify_ddr
	set ck_pins [lsort $pins(ck_p)]
	set ckn_pins [lsort $pins(ck_n)]
	set ck_ckn_pairs [list]
	set failed_assumptions [list]

	if {[llength $ck_pins] > 0 && [llength $ck_pins] == [llength $ckn_pins]} {
  		for {set ck_index 0} {$ck_index != [llength $ck_pins]} {incr ck_index} {
    		lappend ck_ckn_pairs [list [lindex $ck_pins $ck_index] [lindex $ckn_pins $ck_index]]
		}
	} else {
		incr num_errors
		lappend failed_assumptions "Error: Could not locate same number of CK pins as CK# pins"
	}

	set read_pins_list [list]
	set write_pins_list [list]
	foreach dqsgroup $pins(dqsgroup) {
		set dqs [lindex $dqsgroup 0]
		set dq_list [lindex $dqsgroup 2]
		lappend read_pins_list [list $dqs $dq_list]
		set dm_list [lindex $dqsgroup 1]
		lappend write_pins_list [list $dqs [concat $dq_list $dm_list]]
	}
	set all_write_dqs_list [get_all_dqs_pins $pins(dqsgroup)]
	set all_d_list [get_all_dq_pins $pins(dqsgroup)]
	if {[llength $pins(dqsgroup)] == 0} {
		incr num_errors
		lappend failed_assumptions "Error: Could not locate DQS pins"
	}

	if {$num_errors == 0} {
		set msg_list [list]
		set clk_to_write_d [traverse_to_ddio_out_pll_clock [lindex $all_d_list 0] msg_list]
		set clk_to_write_clock [traverse_to_ddio_out_pll_clock [lindex $all_write_dqs_list 0] msg_list]
		set clk_to_ck_ckn [traverse_to_ddio_out_pll_clock [lindex $ck_pins 0] msg_list]

		foreach msg $msg_list {
			set verify_assumptions_exception 1
			incr num_errors
			lappend failed_assumptions $msg
		}

		if {$num_errors == 0} {
			#puts "calling verify_assumptions -memory_type ddr -read_pins_list $read_pins_list -write_pins_list $write_pins_list -ck_ckn_pairs $ck_ckn_pairs -clk_to_write_d $clk_to_write_d -clk_to_write_clock $clk_to_write_clock -clk_to_ck_ckn $clk_to_ck_ckn -mimic_pin [lindex $ck_pins 0]  "
			set verify_assumptions_exception 0
			set verify_assumptions_result {0}
			set verify_assumptions_exception [catch {verify_assumptions -memory_type ddr -read_pins_list $read_pins_list -write_pins_list $write_pins_list -ck_ckn_pairs $ck_ckn_pairs -clk_to_write_d $clk_to_write_d -clk_to_write_clock $clk_to_write_clock -clk_to_ck_ckn $clk_to_ck_ckn -mimic_pin [lindex $ck_pins 0]  } verify_assumptions_result]
			if {$verify_assumptions_exception == 0} {
				incr num_errors [lindex $verify_assumptions_result 0]
				set failed_assumptions [concat $failed_assumptions [lrange $verify_assumptions_result 1 end]]
			}
		}
		if {$verify_assumptions_exception != 0} {
			lappend failed_assumptions "Error: Macro timing assumptions could not be verified"
			incr num_errors
		}
	}

	if {$num_errors != 0} {
		for {set i 0} {$i != [llength $failed_assumptions]} {incr i} {
			set raw_msg [lindex $failed_assumptions $i]
			if {[regexp {^\W*(Info|Extra Info|Warning|Critical Warning|Error): (.*)$} $raw_msg -- msg_type msg]} {
				regsub " " $msg_type _ msg_type
				if {$msg_type == "Error"} {
					set msg_type "critical_warning"
				}
				post_message -type $msg_type $msg
			} else {
				post_message -type info $raw_msg
			}
		}
		post_message -type critical_warning "Read Capture and Write timing analyses may not be valid due to violated timing model assumptions"
	}
	return [expr $num_errors == 0]
}

proc ddr_pin {n pin pin_array_name} {
	upvar 1 $pin_array_name pins
	lappend pins($n) $pin
}

load_package report
load_report

if { ! [timing_netlist_exist] } {
	post_message -type error "Timing Netlist has not been created. Run the 'Update Timing Netlist' task first."
	return
}

source "${corename}_ddr_pins.tcl"

set corename [file tail $corename]
set instance_names [get_core_full_instance_list $corename]

for {set inst_index 0} {$inst_index != [llength $instance_names]} {incr inst_index} {
	set full_instance_name [lindex $instance_names $inst_index]
	set instance_name [get_timequest_name $full_instance_name]
	set instname "${instance_name}|${corename}"

	global TimeQuestInfo
	set family $TimeQuestInfo(family)

	set pins(ck_p) [list]
	set pins(ck_n) [list]
	set pins(addrcmd) [list]
	set pins(addrcmd_2t) [list]
	set pins(dqsgroup) [list]
	set pins(dgroup) [list]
	get_ddr_pins $instname pins
	# Find all the DQ pins
	set alldqpins [list]
	set alldqdmpins [list]
	set alldqspins [list]
	foreach dqsgroup $pins(dqsgroup) {
		set alldqpins [concat $alldqpins [lindex $dqsgroup 2]]
		set alldqdmpins [concat $alldqdmpins [lindex $dqsgroup 2] [lindex $dqsgroup 1]]
		lappend alldqspins [lindex $dqsgroup 0]
	}

	set summary [list]
	foreach opc $opcs {
		if {$opc != "" } {
			set_operating_conditions $opc 
			update_timing_netlist
		}

		set opcname [get_operating_conditions_info [get_operating_conditions] -display_name]
		set opcname [string trim $opcname]

		if {$sdram_phy_use_high_performance_timing} {
			set assumptions_valid [verify_high_performance_timing_assumptions $instname pins $write_deskew_t10]
		}
		# endif $sdram_phy_use_high_performance_timing

		if {!$sdram_phy_use_high_performance_timing} {
# Write
set res_0 [report_timing -detail full_path -to [get_ports $alldqdmpins] -npaths 100 -panel_name "$instname Write \u0028setup\u0029" -setup]
set res_1 [report_timing -detail full_path -to [get_ports $alldqdmpins] -npaths 100 -panel_name "$instname Write \u0028hold\u0029" -hold]
lappend summary [list $opcname 0 "Write ($opcname)" [lindex $res_0 1] [lindex $res_1 1]]

		}
		# endif !$sdram_phy_use_high_performance_timing

# Address Command
set res_0 [report_timing -detail full_path -to $pins(addrcmd) -npaths 100 -panel_name "$instname Address Command \u0028setup\u0029" -setup]
set res_1 [report_timing -detail full_path -to $pins(addrcmd) -npaths 100 -panel_name "$instname Address Command \u0028hold\u0029" -hold]
lappend summary [list $opcname 0 "Address Command ($opcname)" [lindex $res_0 1] [lindex $res_1 1]]

# Half Rate Address/Command
set res_0 [report_timing -detail full_path -to $pins(addrcmd_2t) -npaths 100 -panel_name "$instname Half Rate Address/Command \u0028setup\u0029" -setup]
set res_1 [report_timing -detail full_path -to $pins(addrcmd_2t) -npaths 100 -panel_name "$instname Half Rate Address/Command \u0028hold\u0029" -hold]
lappend summary [list $opcname 0 "Half Rate Address/Command ($opcname)" [lindex $res_0 1] [lindex $res_1 1]]

# DQS vs CK
set res_0 [report_timing -detail full_path -to [get_ports $alldqspins] -npaths 100 -panel_name "$instname DQS vs CK \u0028setup\u0029" -setup]
set res_1 [report_timing -detail full_path -to [get_ports $alldqspins] -npaths 100 -panel_name "$instname DQS vs CK \u0028hold\u0029" -hold]
lappend summary [list $opcname 0 "DQS vs CK ($opcname)" [lindex $res_0 1] [lindex $res_1 1]]

		if {!$sdram_phy_use_high_performance_timing} {
# Read Capture
set res_0 [report_timing -detail full_path -from [get_ports $alldqpins] -to [all_registers] -npaths 100 -panel_name "$instname Read Capture \u0028setup\u0029" -setup]
set res_1 [report_timing -detail full_path -from [get_ports $alldqpins] -to [all_registers] -npaths 100 -panel_name "$instname Read Capture \u0028hold\u0029" -hold]
lappend summary [list $opcname 0 "Read Capture ($opcname)" [lindex $res_0 1] [lindex $res_1 1]]

		}
		# endif !$sdram_phy_use_high_performance_timing

# Phy
set res_0 [report_timing -detail full_path -to [get_registers  "$full_instance_name|*" ] -npaths 100 -panel_name "$instname Phy \u0028setup\u0029" -setup]
set res_1 [report_timing -detail full_path -to [get_registers  "$full_instance_name|*" ] -npaths 100 -panel_name "$instname Phy \u0028hold\u0029" -hold]
lappend summary [list $opcname 0 "Phy ($opcname)" [lindex $res_0 1] [lindex $res_1 1]]

# Phy Reset
set res_0 [report_timing -detail full_path -to [get_registers  "$full_instance_name|*" ] -npaths 100 -panel_name "$instname Phy Reset \u0028recovery\u0029" -recovery]
set res_1 [report_timing -detail full_path -to [get_registers  "$full_instance_name|*" ] -npaths 100 -panel_name "$instname Phy Reset \u0028removal\u0029" -removal]
lappend summary [list $opcname 0 "Phy Reset ($opcname)" [lindex $res_0 1] [lindex $res_1 1]]

# Mimic
set res_1 [list xxx ""]
set res_0 [report_timing -detail full_path -from $pins(ck_p) -to * -npaths 100 -panel_name "$instname Mimic \u0028setup\u0029" -setup]
lappend summary [list $opcname 0 "Mimic ($opcname)" [lindex $res_0 1] [lindex $res_1 1]]

set full_instname "${full_instance_name}|${corename}"
set all_read_dqs_list [get_all_dqs_pins $pins(dqsgroup)]
set interface_type [get_io_interface_type $all_read_dqs_list]
if {$interface_type == "VHPAD"} {
	set interface_type "HPAD"
}

if {[string compare -nocase $family "Arria II GX"] == 0 || [string compare -nocase $family "Arria II"] == 0} {
	set family "Arria II"
}

}
set opcname "All Conditions"
set tDCD_total 0.250

if {$sdram_phy_use_high_performance_timing} {
set board_skew 0.020
set tmin_additional_dqs_variation 0.000
set tmax_additional_dqs_variation 0.000
set tDS 0.400
set tDH 0.400
set tDQSQ 0.400
set tQHS 0.500
set tAC 0.700
set all_read_dqs_list [get_all_dqs_pins $pins(dqsgroup)]
set all_write_dqs_list $all_read_dqs_list
set all_d_list [get_all_dq_pins $pins(dqsgroup)]
set mem_if_memtype "DDR SDRAM"
set dqs_phase 60.000
# Write capture
set msg_list [list]
set dqs_pll_output_id [get_output_clock_id $all_write_dqs_list "DQS output" msg_list]
set dqs_pll_clock ""
sett_collection dqs_pll_clock_id [get_clocks [get_pin_info -name $dqs_pll_output_id]]
set dqs_output_phase [get_clock_info -phase $dqs_pll_clock_id]
set dq_pll_output_id [get_output_clock_id $all_d_list "DQ output" msg_list]
set dq_pll_clock ""
sett_collection dq_pll_clock_id [get_clocks [get_pin_info -name $dq_pll_output_id]]
set dq_output_phase [get_clock_info -phase $dq_pll_clock_id]
set dq2dqs_output_phase_offset [expr $dqs_output_phase - $dq_output_phase]
if {$dq2dqs_output_phase_offset < 0} {
  set dq2dqs_output_phase_offset [expr $dq2dqs_output_phase_offset + 360.0]
}
set tccs [get_tccs $mem_if_memtype $all_write_dqs_list $period]
set write_board_skew $board_skew
set su   [round_3dp [expr {$period*$dq2dqs_output_phase_offset/360.0 - $write_board_skew - [lindex $tccs 0]/1000.0 - $tDS}]]
set hold [round_3dp [expr {$period*(0.5 - $dq2dqs_output_phase_offset/360.0) - $tDCD_total - $write_board_skew - [lindex $tccs 1]/1000.0 - $tDH}]]
lappend summary [list $opcname 0 "Write ($opcname)" $su $hold]
# Read capture
set tsw [get_tsw $mem_if_memtype $all_read_dqs_list $period]

################################################################################
# Cyclone III uses a Macro Timing Methodology for the write and capture paths.
# The read data is captured using a PLL phase which is calibrated and tracked
# with the sequencer. The PHY will automatically calibrate the phase of a
# dedicated PLL read clock to center it within the read data valid window
# presented to all DQ capture registers.  The DQS read strobes are ignored, so
# postamble is not an issue. The phase of the read clock is adjusted to account
# for VT variations seen in the mimic path. Also, the exact length of the DQ
# and CK traces don't affect the timing analysis. Note that the read data
# resync to the PHY system clock domain is done through a dual-clock FIFO, so
# no resync timing analysis is needed for that transfer.
################################################################################
set su   [round_3dp [expr {0.25*$period - 0.5*$tDCD_total - $tAC - [lindex $tsw 0]/1000.0 - 0.5 * $board_skew}]]
set hold [round_3dp [expr {0.25*$period - 0.5*$tDCD_total - $tAC - [lindex $tsw 1]/1000.0 - 0.5 * $board_skew}]]
lappend summary [list $opcname 0 "Read Capture ($opcname)" $su $hold]

}
# endif $sdram_phy_use_high_performance_timing
proc sort_proc {a b} {
	set idxs [list 1 2 0]
	foreach i $idxs {
		set ai [lindex $a $i]
		set bi [lindex $b $i]
		if {$ai > $bi} {
			return 1
		} elseif { $ai < $bi } {
			return -1
		}
	}
	return 0
}

set summary [lsort -command sort_proc $summary]
if {[llength $instance_names] <= 1} {
	set f [open "${corename}_summary.csv" w]
} else {
	set f [open "${corename}${inst_index}_summary.csv" w]
}
puts $f "#Path, Setup Margin, Hold Margin"
post_message -type info "                                                         setup  hold"
set panel_name "$instname"
set root_folder_name [get_current_timequest_report_folder]
if { ! [string match "${root_folder_name}*" $panel_name] } {
	set panel_name "${root_folder_name}||$panel_name"
}
# Create the root if it doesn't yet exist
if {[get_report_panel_id $root_folder_name] == -1} {
	set panel_id [create_report_panel -folder $root_folder_name]
}

# Delete any pre-existing summary panel
set panel_id [get_report_panel_id $panel_name]
if {$panel_id != -1} {
	delete_report_panel -id $panel_id
}

# Create summary panel
set panel_id [create_report_panel -table $panel_name]
add_row_to_table -id $panel_id [list "Path" "Operating Condition" "Setup Slack" "Hold Slack"] 
foreach summary_line $summary {
	foreach {corner order path su hold} $summary_line { }
		if { $su < 0 || ($hold!="" && $hold < 0) } {
			set type warning
			set offset 50
		} else {
			set type info
			set offset 53
		}
		set su [format %.3f $su]
		if {$hold != ""} {
			set hold [format %.3f $hold]
		}
		post_message -type $type [format "%-${offset}s | %6s %6s" $path $su $hold]
		puts $f [format "\"%s\",%s,%s" $path $su $hold]
		set fg_colours [list black black]
		if { $su < 0 } {
			lappend fg_colours red
		} else {
			lappend fg_colours black
		}
		if { $hold != "" && $hold < 0 } {
			lappend fg_colours red
		} else {
			lappend fg_colours black
		}
		add_row_to_table -id $panel_id -fcolors $fg_colours [list $path $corner $su $hold] 
	}
	close $f
}
write_timing_report
if {$batch_mode_en == 1} {
	catch {delete_timing_netlist}
}
