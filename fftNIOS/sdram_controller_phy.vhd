--Legal Notice: (C)2012 Altera Corporation. All rights reserved.  Your
--use of Altera Corporation's design tools, logic functions and other
--software and tools, and its AMPP partner logic functions, and any
--output files any of the foregoing (including device programming or
--simulation files), and any associated documentation or information are
--expressly subject to the terms and conditions of the Altera Program
--License Subscription Agreement or other applicable license agreement,
--including, without limitation, that your use is for the sole purpose
--of programming logic devices manufactured by Altera and sold by Altera
--or its authorized distributors.  Please refer to the applicable
--agreement for further details.


-- turn off superfluous VHDL processor warnings 
-- altera message_level Level1 
-- altera message_off 10034 10035 10036 10037 10230 10240 10030 

library altera;
use altera.altera_europa_support_lib.all;

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity sdram_controller_phy is 
        port (
              -- inputs:
                 signal dqs_delay_ctrl_import : IN STD_LOGIC_VECTOR (5 DOWNTO 0);
                 signal dqs_offset_delay_ctrl : IN STD_LOGIC_VECTOR (5 DOWNTO 0);
                 signal global_reset_n : IN STD_LOGIC;
                 signal hc_scan_ck : IN STD_LOGIC;
                 signal hc_scan_din : IN STD_LOGIC_VECTOR (1 DOWNTO 0);
                 signal hc_scan_enable_access : IN STD_LOGIC;
                 signal hc_scan_enable_dm : IN STD_LOGIC_VECTOR (1 DOWNTO 0);
                 signal hc_scan_enable_dq : IN STD_LOGIC_VECTOR (15 DOWNTO 0);
                 signal hc_scan_enable_dqs : IN STD_LOGIC_VECTOR (1 DOWNTO 0);
                 signal hc_scan_enable_dqs_config : IN STD_LOGIC_VECTOR (1 DOWNTO 0);
                 signal hc_scan_update : IN STD_LOGIC_VECTOR (1 DOWNTO 0);
                 signal local_address : IN STD_LOGIC_VECTOR (21 DOWNTO 0);
                 signal local_autopch_req : IN STD_LOGIC;
                 signal local_be : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
                 signal local_burstbegin : IN STD_LOGIC;
                 signal local_powerdn_req : IN STD_LOGIC;
                 signal local_read_req : IN STD_LOGIC;
                 signal local_refresh_req : IN STD_LOGIC;
                 signal local_self_rfsh_req : IN STD_LOGIC;
                 signal local_size : IN STD_LOGIC;
                 signal local_wdata : IN STD_LOGIC_VECTOR (63 DOWNTO 0);
                 signal local_write_req : IN STD_LOGIC;
                 signal oct_ctl_rs_value : IN STD_LOGIC_VECTOR (13 DOWNTO 0);
                 signal oct_ctl_rt_value : IN STD_LOGIC_VECTOR (13 DOWNTO 0);
                 signal pll_phasecounterselect : IN STD_LOGIC_VECTOR (3 DOWNTO 0);
                 signal pll_phasestep : IN STD_LOGIC;
                 signal pll_phaseupdown : IN STD_LOGIC;
                 signal pll_reconfig : IN STD_LOGIC;
                 signal pll_reconfig_counter_param : IN STD_LOGIC_VECTOR (2 DOWNTO 0);
                 signal pll_reconfig_counter_type : IN STD_LOGIC_VECTOR (3 DOWNTO 0);
                 signal pll_reconfig_data_in : IN STD_LOGIC_VECTOR (8 DOWNTO 0);
                 signal pll_reconfig_enable : IN STD_LOGIC;
                 signal pll_reconfig_read_param : IN STD_LOGIC;
                 signal pll_reconfig_soft_reset_en_n : IN STD_LOGIC;
                 signal pll_reconfig_write_param : IN STD_LOGIC;
                 signal pll_ref_clk : IN STD_LOGIC;
                 signal soft_reset_n : IN STD_LOGIC;

              -- outputs:
                 signal aux_full_rate_clk : OUT STD_LOGIC;
                 signal aux_half_rate_clk : OUT STD_LOGIC;
                 signal aux_scan_clk : OUT STD_LOGIC;
                 signal aux_scan_clk_reset_n : OUT STD_LOGIC;
                 signal dll_reference_clk : OUT STD_LOGIC;
                 signal dqs_delay_ctrl_export : OUT STD_LOGIC_VECTOR (5 DOWNTO 0);
                 signal hc_scan_dout : OUT STD_LOGIC_VECTOR (15 DOWNTO 0);
                 signal local_init_done : OUT STD_LOGIC;
                 signal local_powerdn_ack : OUT STD_LOGIC;
                 signal local_rdata : OUT STD_LOGIC_VECTOR (63 DOWNTO 0);
                 signal local_rdata_error : OUT STD_LOGIC;
                 signal local_rdata_valid : OUT STD_LOGIC;
                 signal local_ready : OUT STD_LOGIC;
                 signal local_refresh_ack : OUT STD_LOGIC;
                 signal local_self_rfsh_ack : OUT STD_LOGIC;
                 signal local_wdata_req : OUT STD_LOGIC;
                 signal mem_addr : OUT STD_LOGIC_VECTOR (12 DOWNTO 0);
                 signal mem_ba : OUT STD_LOGIC_VECTOR (1 DOWNTO 0);
                 signal mem_cas_n : OUT STD_LOGIC;
                 signal mem_cke : OUT STD_LOGIC_VECTOR (0 DOWNTO 0);
                 signal mem_clk : INOUT STD_LOGIC_VECTOR (0 DOWNTO 0);
                 signal mem_clk_n : INOUT STD_LOGIC_VECTOR (0 DOWNTO 0);
                 signal mem_cs_n : OUT STD_LOGIC_VECTOR (0 DOWNTO 0);
                 signal mem_dm : OUT STD_LOGIC_VECTOR (1 DOWNTO 0);
                 signal mem_dq : INOUT STD_LOGIC_VECTOR (15 DOWNTO 0);
                 signal mem_dqs : INOUT STD_LOGIC_VECTOR (1 DOWNTO 0);
                 signal mem_dqsn : INOUT STD_LOGIC_VECTOR (1 DOWNTO 0);
                 signal mem_odt : OUT STD_LOGIC_VECTOR (0 DOWNTO 0);
                 signal mem_ras_n : OUT STD_LOGIC;
                 signal mem_reset_n : OUT STD_LOGIC;
                 signal mem_we_n : OUT STD_LOGIC;
                 signal phy_clk : OUT STD_LOGIC;
                 signal pll_phase_done : OUT STD_LOGIC;
                 signal pll_reconfig_busy : OUT STD_LOGIC;
                 signal pll_reconfig_clk : OUT STD_LOGIC;
                 signal pll_reconfig_data_out : OUT STD_LOGIC_VECTOR (8 DOWNTO 0);
                 signal pll_reconfig_reset : OUT STD_LOGIC;
                 signal reset_phy_clk_n : OUT STD_LOGIC;
                 signal reset_request_n : OUT STD_LOGIC
              );
end entity sdram_controller_phy;


architecture europa of sdram_controller_phy is
  component sdram_auk_ddr_hp_controller_wrapper is
PORT (
    signal ddr_cke_h : OUT STD_LOGIC_VECTOR (0 DOWNTO 0);
        signal local_init_done : OUT STD_LOGIC;
        signal ddr_ras_n : OUT STD_LOGIC;
        signal control_be : OUT STD_LOGIC_VECTOR (7 DOWNTO 0);
        signal control_dqs_burst : OUT STD_LOGIC_VECTOR (3 DOWNTO 0);
        signal ddr_we_n : OUT STD_LOGIC;
        signal ddr_odt : OUT STD_LOGIC_VECTOR (0 DOWNTO 0);
        signal control_wdata : OUT STD_LOGIC_VECTOR (63 DOWNTO 0);
        signal ddr_cas_n : OUT STD_LOGIC;
        signal local_rdata : OUT STD_LOGIC_VECTOR (63 DOWNTO 0);
        signal local_rdata_valid : OUT STD_LOGIC;
        signal ddr_cke_l : OUT STD_LOGIC_VECTOR (0 DOWNTO 0);
        signal control_wdata_valid : OUT STD_LOGIC_VECTOR (3 DOWNTO 0);
        signal ddr_a : OUT STD_LOGIC_VECTOR (12 DOWNTO 0);
        signal local_ready : OUT STD_LOGIC;
        signal control_doing_wr : OUT STD_LOGIC;
        signal control_doing_rd : OUT STD_LOGIC_VECTOR (3 DOWNTO 0);
        signal local_powerdn_ack : OUT STD_LOGIC;
        signal local_self_rfsh_ack : OUT STD_LOGIC;
        signal local_refresh_ack : OUT STD_LOGIC;
        signal local_wdata_req : OUT STD_LOGIC;
        signal ddr_ba : OUT STD_LOGIC_VECTOR (1 DOWNTO 0);
        signal ddr_cs_n : OUT STD_LOGIC_VECTOR (0 DOWNTO 0);
        signal control_dm : OUT STD_LOGIC_VECTOR (7 DOWNTO 0);
        signal seq_cal_complete : IN STD_LOGIC;
        signal local_size : IN STD_LOGIC_VECTOR (0 DOWNTO 0);
        signal local_autopch_req : IN STD_LOGIC;
        signal local_wdata : IN STD_LOGIC_VECTOR (63 DOWNTO 0);
        signal local_col_addr : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        signal local_refresh_req : IN STD_LOGIC;
        signal local_row_addr : IN STD_LOGIC_VECTOR (12 DOWNTO 0);
        signal reset_n : IN STD_LOGIC;
        signal local_bank_addr : IN STD_LOGIC_VECTOR (1 DOWNTO 0);
        signal local_burstbegin : IN STD_LOGIC;
        signal control_wlat : IN STD_LOGIC_VECTOR (4 DOWNTO 0);
        signal local_write_req : IN STD_LOGIC;
        signal local_self_rfsh_req : IN STD_LOGIC;
        signal local_powerdn_req : IN STD_LOGIC;
        signal local_cs_addr : IN STD_LOGIC_VECTOR (0 DOWNTO 0);
        signal control_rdata_valid : IN STD_LOGIC_VECTOR (1 DOWNTO 0);
        signal control_rdata : IN STD_LOGIC_VECTOR (63 DOWNTO 0);
        signal local_be : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        signal local_read_req : IN STD_LOGIC;
        signal clk : IN STD_LOGIC
      );
  end component sdram_auk_ddr_hp_controller_wrapper;
  component sdram_phy is
PORT (
    signal mem_cke : OUT STD_LOGIC_VECTOR (0 DOWNTO 0);
        signal ctl_cal_fail : OUT STD_LOGIC;
        signal mem_addr : OUT STD_LOGIC_VECTOR (12 DOWNTO 0);
        signal mem_dm : OUT STD_LOGIC_VECTOR (1 DOWNTO 0);
        signal aux_full_rate_clk : OUT STD_LOGIC;
        signal mem_dq : INOUT STD_LOGIC_VECTOR (15 DOWNTO 0);
        signal mem_ras_n : OUT STD_LOGIC;
        signal dbg_rd_data : OUT STD_LOGIC_VECTOR (31 DOWNTO 0);
        signal mem_cs_n : OUT STD_LOGIC_VECTOR (0 DOWNTO 0);
        signal mem_ba : OUT STD_LOGIC_VECTOR (1 DOWNTO 0);
        signal mem_reset_n : OUT STD_LOGIC;
        signal dbg_waitrequest : OUT STD_LOGIC;
        signal ctl_rdata : OUT STD_LOGIC_VECTOR (63 DOWNTO 0);
        signal ctl_wlat : OUT STD_LOGIC_VECTOR (4 DOWNTO 0);
        signal ctl_rdata_valid : OUT STD_LOGIC_VECTOR (1 DOWNTO 0);
        signal ctl_clk : OUT STD_LOGIC;
        signal ctl_cal_warning : OUT STD_LOGIC;
        signal aux_half_rate_clk : OUT STD_LOGIC;
        signal ctl_cal_success : OUT STD_LOGIC;
        signal mem_dqs_n : INOUT STD_LOGIC_VECTOR (1 DOWNTO 0);
        signal mem_we_n : OUT STD_LOGIC;
        signal mem_odt : OUT STD_LOGIC_VECTOR (0 DOWNTO 0);
        signal mem_cas_n : OUT STD_LOGIC;
        signal ctl_rlat : OUT STD_LOGIC_VECTOR (4 DOWNTO 0);
        signal mem_clk : INOUT STD_LOGIC_VECTOR (0 DOWNTO 0);
        signal ctl_reset_n : OUT STD_LOGIC;
        signal reset_request_n : OUT STD_LOGIC;
        signal mem_dqs : INOUT STD_LOGIC_VECTOR (1 DOWNTO 0);
        signal mem_clk_n : INOUT STD_LOGIC_VECTOR (0 DOWNTO 0);
        signal ctl_doing_rd : IN STD_LOGIC_VECTOR (3 DOWNTO 0);
        signal ctl_dm : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
        signal soft_reset_n : IN STD_LOGIC;
        signal dbg_clk : IN STD_LOGIC;
        signal ctl_cal_req : IN STD_LOGIC;
        signal global_reset_n : IN STD_LOGIC;
        signal dbg_cs : IN STD_LOGIC;
        signal ctl_mem_clk_disable : IN STD_LOGIC_VECTOR (0 DOWNTO 0);
        signal ctl_rst_n : IN STD_LOGIC_VECTOR (1 DOWNTO 0);
        signal ctl_we_n : IN STD_LOGIC_VECTOR (1 DOWNTO 0);
        signal ctl_addr : IN STD_LOGIC_VECTOR (25 DOWNTO 0);
        signal ctl_odt : IN STD_LOGIC_VECTOR (1 DOWNTO 0);
        signal ctl_ba : IN STD_LOGIC_VECTOR (3 DOWNTO 0);
        signal dbg_addr : IN STD_LOGIC_VECTOR (12 DOWNTO 0);
        signal ctl_wdata : IN STD_LOGIC_VECTOR (63 DOWNTO 0);
        signal dbg_wr : IN STD_LOGIC;
        signal ctl_cke : IN STD_LOGIC_VECTOR (1 DOWNTO 0);
        signal ctl_dqs_burst : IN STD_LOGIC_VECTOR (3 DOWNTO 0);
        signal pll_ref_clk : IN STD_LOGIC;
        signal ctl_cs_n : IN STD_LOGIC_VECTOR (1 DOWNTO 0);
        signal ctl_cas_n : IN STD_LOGIC_VECTOR (1 DOWNTO 0);
        signal ctl_cal_byte_lane_sel_n : IN STD_LOGIC_VECTOR (1 DOWNTO 0);
        signal dbg_rd : IN STD_LOGIC;
        signal ctl_ras_n : IN STD_LOGIC_VECTOR (1 DOWNTO 0);
        signal dbg_wr_data : IN STD_LOGIC_VECTOR (31 DOWNTO 0);
        signal ctl_wdata_valid : IN STD_LOGIC_VECTOR (3 DOWNTO 0);
        signal dbg_reset_n : IN STD_LOGIC
      );
  end component sdram_phy;
                signal bank_addr :  STD_LOGIC_VECTOR (1 DOWNTO 0);
                signal col_addr :  STD_LOGIC_VECTOR (7 DOWNTO 0);
                signal control_be_width :  STD_LOGIC_VECTOR (7 DOWNTO 0);
                signal cs_addr :  STD_LOGIC;
                signal ctl_addr_repl :  STD_LOGIC_VECTOR (25 DOWNTO 0);
                signal ctl_addr_sig :  STD_LOGIC_VECTOR (12 DOWNTO 0);
                signal ctl_ba_repl :  STD_LOGIC_VECTOR (3 DOWNTO 0);
                signal ctl_ba_sig :  STD_LOGIC_VECTOR (1 DOWNTO 0);
                signal ctl_cal_byte_lane_sel_n_sig :  STD_LOGIC_VECTOR (1 DOWNTO 0);
                signal ctl_cal_fail_sig :  STD_LOGIC;
                signal ctl_cal_success_sig :  STD_LOGIC;
                signal ctl_cal_warning_sig :  STD_LOGIC;
                signal ctl_cas_n_repl :  STD_LOGIC_VECTOR (1 DOWNTO 0);
                signal ctl_cas_n_sig :  STD_LOGIC;
                signal ctl_cke_h_sig :  STD_LOGIC;
                signal ctl_cke_l_sig :  STD_LOGIC;
                signal ctl_cke_repl :  STD_LOGIC_VECTOR (1 DOWNTO 0);
                signal ctl_cs_n_repl :  STD_LOGIC_VECTOR (1 DOWNTO 0);
                signal ctl_cs_n_sig :  STD_LOGIC;
                signal ctl_dm_sig :  STD_LOGIC_VECTOR (7 DOWNTO 0);
                signal ctl_dm_sig_temp :  STD_LOGIC_VECTOR (7 DOWNTO 0);
                signal ctl_doing_rd_sig :  STD_LOGIC_VECTOR (3 DOWNTO 0);
                signal ctl_dqs_burst_sig :  STD_LOGIC_VECTOR (3 DOWNTO 0);
                signal ctl_mem_clk_disable_sig :  STD_LOGIC;
                signal ctl_odt_repl :  STD_LOGIC_VECTOR (1 DOWNTO 0);
                signal ctl_odt_sig :  STD_LOGIC;
                signal ctl_ras_n_repl :  STD_LOGIC_VECTOR (1 DOWNTO 0);
                signal ctl_ras_n_sig :  STD_LOGIC;
                signal ctl_rdata_sig :  STD_LOGIC_VECTOR (63 DOWNTO 0);
                signal ctl_rdata_valid_sig :  STD_LOGIC_VECTOR (1 DOWNTO 0);
                signal ctl_rlat_sig :  STD_LOGIC_VECTOR (4 DOWNTO 0);
                signal ctl_wdata_sig :  STD_LOGIC_VECTOR (63 DOWNTO 0);
                signal ctl_wdata_valid_sig :  STD_LOGIC_VECTOR (3 DOWNTO 0);
                signal ctl_we_n_repl :  STD_LOGIC_VECTOR (1 DOWNTO 0);
                signal ctl_we_n_sig :  STD_LOGIC;
                signal ctl_wlat_sig :  STD_LOGIC_VECTOR (4 DOWNTO 0);
                signal dbg_rd_data_sig :  STD_LOGIC_VECTOR (31 DOWNTO 0);
                signal dbg_waitrequest_sig :  STD_LOGIC;
                signal internal_aux_full_rate_clk :  STD_LOGIC;
                signal internal_aux_half_rate_clk :  STD_LOGIC;
                signal internal_local_init_done :  STD_LOGIC;
                signal internal_local_powerdn_ack :  STD_LOGIC;
                signal internal_local_rdata_valid :  STD_LOGIC;
                signal internal_local_ready :  STD_LOGIC;
                signal internal_local_refresh_ack :  STD_LOGIC;
                signal internal_local_self_rfsh_ack :  STD_LOGIC;
                signal internal_local_wdata_req :  STD_LOGIC;
                signal internal_mem_addr :  STD_LOGIC_VECTOR (12 DOWNTO 0);
                signal internal_mem_ba :  STD_LOGIC_VECTOR (1 DOWNTO 0);
                signal internal_mem_cas_n :  STD_LOGIC;
                signal internal_mem_cke :  STD_LOGIC_VECTOR (0 DOWNTO 0);
                signal internal_mem_cs_n :  STD_LOGIC_VECTOR (0 DOWNTO 0);
                signal internal_mem_dm :  STD_LOGIC_VECTOR (1 DOWNTO 0);
                signal internal_mem_odt :  STD_LOGIC_VECTOR (0 DOWNTO 0);
                signal internal_mem_ras_n :  STD_LOGIC;
                signal internal_mem_reset_n :  STD_LOGIC;
                signal internal_mem_we_n :  STD_LOGIC;
                signal internal_phy_clk :  STD_LOGIC;
                signal internal_reset_phy_clk_n :  STD_LOGIC;
                signal internal_reset_request_n :  STD_LOGIC;
                signal local_be_sig :  STD_LOGIC_VECTOR (7 DOWNTO 0);
                signal local_rdata_sig :  STD_LOGIC_VECTOR (63 DOWNTO 0);
                signal local_wdata_sig :  STD_LOGIC_VECTOR (63 DOWNTO 0);
                signal phy_clk_sig :  STD_LOGIC;
                signal reset_phy_clk_n_sig :  STD_LOGIC;
                signal row_addr :  STD_LOGIC_VECTOR (12 DOWNTO 0);

begin

  local_wdata_sig(63 DOWNTO 0) <= local_wdata(63 DOWNTO 0);
  local_be_sig(7 DOWNTO 0) <= local_be(7 DOWNTO 0);
  local_rdata <= local_rdata_sig(63 DOWNTO 0);
  ctl_mem_clk_disable_sig <= std_logic'('0');
  ctl_cal_byte_lane_sel_n_sig <= std_logic_vector'("00");
  cs_addr <= std_logic'('0');
  bank_addr <= local_address(21 DOWNTO 20);
  row_addr <= local_address(19 DOWNTO 7);
  col_addr(7 DOWNTO 1) <= local_address(6 DOWNTO 0);
  col_addr(0) <= std_logic'('0');
  internal_phy_clk <= phy_clk_sig;
  internal_reset_phy_clk_n <= reset_phy_clk_n_sig;
  sdram_auk_ddr_hp_controller_wrapper_inst : sdram_auk_ddr_hp_controller_wrapper
    port map(
            clk => phy_clk_sig,
            control_be => control_be_width,
            control_dm => ctl_dm_sig,
            control_doing_rd => ctl_doing_rd_sig,
            control_doing_wr => open,
            control_dqs_burst => ctl_dqs_burst_sig,
            control_rdata => ctl_rdata_sig,
            control_rdata_valid => ctl_rdata_valid_sig,
            control_wdata => ctl_wdata_sig,
            control_wdata_valid => ctl_wdata_valid_sig,
            control_wlat => ctl_wlat_sig,
            ddr_a => ctl_addr_sig,
            ddr_ba => ctl_ba_sig,
            ddr_cas_n => ctl_cas_n_sig,
            ddr_cke_h(0) => ctl_cke_h_sig,
            ddr_cke_l(0) => ctl_cke_l_sig,
            ddr_cs_n(0) => ctl_cs_n_sig,
            ddr_odt(0) => ctl_odt_sig,
            ddr_ras_n => ctl_ras_n_sig,
            ddr_we_n => ctl_we_n_sig,
            local_autopch_req => local_autopch_req,
            local_bank_addr => bank_addr,
            local_be => local_be_sig,
            local_burstbegin => local_burstbegin,
            local_col_addr => col_addr,
            local_cs_addr => A_TOSTDLOGICVECTOR(cs_addr),
            local_init_done => internal_local_init_done,
            local_powerdn_ack => internal_local_powerdn_ack,
            local_powerdn_req => local_powerdn_req,
            local_rdata => local_rdata_sig,
            local_rdata_valid => internal_local_rdata_valid,
            local_read_req => local_read_req,
            local_ready => internal_local_ready,
            local_refresh_ack => internal_local_refresh_ack,
            local_refresh_req => local_refresh_req,
            local_row_addr => row_addr,
            local_self_rfsh_ack => internal_local_self_rfsh_ack,
            local_self_rfsh_req => local_self_rfsh_req,
            local_size => A_TOSTDLOGICVECTOR(local_size),
            local_wdata => local_wdata_sig,
            local_wdata_req => internal_local_wdata_req,
            local_write_req => local_write_req,
            reset_n => reset_phy_clk_n_sig,
            seq_cal_complete => ctl_cal_success_sig
    );

  ctl_addr_repl <= A_REP_VECTOR(ctl_addr_sig, 2);
  ctl_ba_repl <= A_REP_VECTOR(ctl_ba_sig, 2);
  ctl_odt_repl <= A_REP(ctl_odt_sig, 2);
  ctl_cas_n_repl <= A_REP(ctl_cas_n_sig, 2);
  ctl_ras_n_repl <= A_REP(ctl_ras_n_sig, 2);
  ctl_we_n_repl <= A_REP(ctl_we_n_sig, 2);
  ctl_cke_repl <= Std_Logic_Vector'(A_ToStdLogicVector(ctl_cke_l_sig) & A_ToStdLogicVector(ctl_cke_h_sig));
  ctl_cs_n_repl <= Std_Logic_Vector'(A_ToStdLogicVector(ctl_cs_n_sig) & A_ToStdLogicVector(std_logic'('1')));
  ctl_dm_sig_temp <= ctl_dm_sig;
  sdram_phy_inst : sdram_phy
    port map(
            aux_full_rate_clk => internal_aux_full_rate_clk,
            aux_half_rate_clk => internal_aux_half_rate_clk,
            ctl_addr => ctl_addr_repl,
            ctl_ba => ctl_ba_repl,
            ctl_cal_byte_lane_sel_n => ctl_cal_byte_lane_sel_n_sig,
            ctl_cal_fail => ctl_cal_fail_sig,
            ctl_cal_req => std_logic'('0'),
            ctl_cal_success => ctl_cal_success_sig,
            ctl_cal_warning => ctl_cal_warning_sig,
            ctl_cas_n => ctl_cas_n_repl,
            ctl_cke => ctl_cke_repl,
            ctl_clk => phy_clk_sig,
            ctl_cs_n => ctl_cs_n_repl,
            ctl_dm => ctl_dm_sig_temp,
            ctl_doing_rd => ctl_doing_rd_sig,
            ctl_dqs_burst => ctl_dqs_burst_sig,
            ctl_mem_clk_disable => A_TOSTDLOGICVECTOR(ctl_mem_clk_disable_sig),
            ctl_odt => ctl_odt_repl,
            ctl_ras_n => ctl_ras_n_repl,
            ctl_rdata => ctl_rdata_sig,
            ctl_rdata_valid => ctl_rdata_valid_sig,
            ctl_reset_n => reset_phy_clk_n_sig,
            ctl_rlat => ctl_rlat_sig,
            ctl_rst_n => std_logic_vector'("11"),
            ctl_wdata => ctl_wdata_sig,
            ctl_wdata_valid => ctl_wdata_valid_sig,
            ctl_we_n => ctl_we_n_repl,
            ctl_wlat => ctl_wlat_sig,
            dbg_addr => std_logic_vector'("0000000000000"),
            dbg_clk => internal_phy_clk,
            dbg_cs => std_logic'('0'),
            dbg_rd => std_logic'('0'),
            dbg_rd_data => dbg_rd_data_sig,
            dbg_reset_n => internal_reset_phy_clk_n,
            dbg_waitrequest => dbg_waitrequest_sig,
            dbg_wr => std_logic'('0'),
            dbg_wr_data => std_logic_vector'("00000000000000000000000000000000"),
            global_reset_n => global_reset_n,
            mem_addr => internal_mem_addr,
            mem_ba => internal_mem_ba,
            mem_cas_n => internal_mem_cas_n,
            mem_cke(0) => internal_mem_cke(0),
            mem_clk(0) => mem_clk(0),
            mem_clk_n(0) => mem_clk_n(0),
            mem_cs_n(0) => internal_mem_cs_n(0),
            mem_dm => internal_mem_dm(1 DOWNTO 0),
            mem_dq => mem_dq,
            mem_dqs => mem_dqs(1 DOWNTO 0),
            mem_dqs_n => mem_dqsn(1 DOWNTO 0),
            mem_odt(0) => internal_mem_odt(0),
            mem_ras_n => internal_mem_ras_n,
            mem_reset_n => internal_mem_reset_n,
            mem_we_n => internal_mem_we_n,
            pll_ref_clk => pll_ref_clk,
            reset_request_n => internal_reset_request_n,
            soft_reset_n => soft_reset_n
    );

  --<< start europa
  --vhdl renameroo for output signals
  aux_full_rate_clk <= internal_aux_full_rate_clk;
  --vhdl renameroo for output signals
  aux_half_rate_clk <= internal_aux_half_rate_clk;
  --vhdl renameroo for output signals
  local_init_done <= internal_local_init_done;
  --vhdl renameroo for output signals
  local_powerdn_ack <= internal_local_powerdn_ack;
  --vhdl renameroo for output signals
  local_rdata_valid <= internal_local_rdata_valid;
  --vhdl renameroo for output signals
  local_ready <= internal_local_ready;
  --vhdl renameroo for output signals
  local_refresh_ack <= internal_local_refresh_ack;
  --vhdl renameroo for output signals
  local_self_rfsh_ack <= internal_local_self_rfsh_ack;
  --vhdl renameroo for output signals
  local_wdata_req <= internal_local_wdata_req;
  --vhdl renameroo for output signals
  mem_addr <= internal_mem_addr;
  --vhdl renameroo for output signals
  mem_ba <= internal_mem_ba;
  --vhdl renameroo for output signals
  mem_cas_n <= internal_mem_cas_n;
  --vhdl renameroo for output signals
  mem_cke <= internal_mem_cke;
  --vhdl renameroo for output signals
  mem_cs_n <= internal_mem_cs_n;
  --vhdl renameroo for output signals
  mem_dm <= internal_mem_dm;
  --vhdl renameroo for output signals
  mem_odt <= internal_mem_odt;
  --vhdl renameroo for output signals
  mem_ras_n <= internal_mem_ras_n;
  --vhdl renameroo for output signals
  mem_reset_n <= internal_mem_reset_n;
  --vhdl renameroo for output signals
  mem_we_n <= internal_mem_we_n;
  --vhdl renameroo for output signals
  phy_clk <= internal_phy_clk;
  --vhdl renameroo for output signals
  reset_phy_clk_n <= internal_reset_phy_clk_n;
  --vhdl renameroo for output signals
  reset_request_n <= internal_reset_request_n;

end europa;

