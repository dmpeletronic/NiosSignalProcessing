--Legal Notice: (C)2011 Altera Corporation. All rights reserved.  Your
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

library altera_mf;
use altera_mf.all;

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

library lpm;
use lpm.all;

entity slow_down_fifo_dual_clock_fifo is 
        port (
              -- inputs:
                 signal aclr : IN STD_LOGIC;
                 signal data : IN STD_LOGIC_VECTOR (35 DOWNTO 0);
                 signal rdclk : IN STD_LOGIC;
                 signal rdreq : IN STD_LOGIC;
                 signal wrclk : IN STD_LOGIC;
                 signal wrreq : IN STD_LOGIC;

              -- outputs:
                 signal q : OUT STD_LOGIC_VECTOR (35 DOWNTO 0);
                 signal rdempty : OUT STD_LOGIC;
                 signal wrfull : OUT STD_LOGIC;
                 signal wrusedw : OUT STD_LOGIC_VECTOR (7 DOWNTO 0)
              );
end entity slow_down_fifo_dual_clock_fifo;


architecture europa of slow_down_fifo_dual_clock_fifo is
  component dcfifo is
GENERIC (
      intended_device_family : STRING;
        lpm_numwords : NATURAL;
        lpm_showahead : STRING;
        lpm_type : STRING;
        lpm_width : NATURAL;
        lpm_widthu : NATURAL;
        overflow_checking : STRING;
        rdsync_delaypipe : NATURAL;
        underflow_checking : STRING;
        use_eab : STRING;
        wrsync_delaypipe : NATURAL
      );
    PORT (
    signal rdempty : OUT STD_LOGIC;
        signal wrfull : OUT STD_LOGIC;
        signal wrusedw : OUT STD_LOGIC_VECTOR (7 DOWNTO 0);
        signal q : OUT STD_LOGIC_VECTOR (35 DOWNTO 0);
        signal aclr : IN STD_LOGIC;
        signal rdreq : IN STD_LOGIC;
        signal data : IN STD_LOGIC_VECTOR (35 DOWNTO 0);
        signal wrclk : IN STD_LOGIC;
        signal rdclk : IN STD_LOGIC;
        signal wrreq : IN STD_LOGIC
      );
  end component dcfifo;
                signal int_wrfull :  STD_LOGIC;
                signal internal_q1 :  STD_LOGIC_VECTOR (35 DOWNTO 0);
                signal internal_rdempty1 :  STD_LOGIC;
                signal internal_wrusedw :  STD_LOGIC_VECTOR (7 DOWNTO 0);

begin

  wrfull <= to_std_logic((((std_logic_vector'("0000000000000000000000000") & (internal_wrusedw))>=(std_logic_vector'("000000000000000000000000100000000") - std_logic_vector'("000000000000000000000000000000011"))))) OR int_wrfull;
  dual_clock_fifo : dcfifo
    generic map(
      intended_device_family => "CYCLONEIII",
      lpm_numwords => 256,
      lpm_showahead => "OFF",
      lpm_type => "dcfifo",
      lpm_width => 36,
      lpm_widthu => 8,
      overflow_checking => "ON",
      rdsync_delaypipe => 4,
      underflow_checking => "ON",
      use_eab => "ON",
      wrsync_delaypipe => 4
    )
    port map(
            aclr => aclr,
            data => data,
            q => internal_q1,
            rdclk => rdclk,
            rdempty => internal_rdempty1,
            rdreq => rdreq,
            wrclk => wrclk,
            wrfull => int_wrfull,
            wrreq => wrreq,
            wrusedw => internal_wrusedw
    );

  --vhdl renameroo for output signals
  q <= internal_q1;
  --vhdl renameroo for output signals
  rdempty <= internal_rdempty1;
  --vhdl renameroo for output signals
  wrusedw <= internal_wrusedw;

end europa;



-- turn off superfluous VHDL processor warnings 
-- altera message_level Level1 
-- altera message_off 10034 10035 10036 10037 10230 10240 10030 

library altera;
use altera.altera_europa_support_lib.all;

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity slow_down_fifo_dcfifo_with_controls is 
        port (
              -- inputs:
                 signal data : IN STD_LOGIC_VECTOR (35 DOWNTO 0);
                 signal rdclk : IN STD_LOGIC;
                 signal rdreq : IN STD_LOGIC;
                 signal wrclk : IN STD_LOGIC;
                 signal wrreq : IN STD_LOGIC;
                 signal wrreset_n : IN STD_LOGIC;

              -- outputs:
                 signal q : OUT STD_LOGIC_VECTOR (35 DOWNTO 0);
                 signal rdempty : OUT STD_LOGIC;
                 signal wrfull : OUT STD_LOGIC;
                 signal wrlevel : OUT STD_LOGIC_VECTOR (8 DOWNTO 0)
              );
end entity slow_down_fifo_dcfifo_with_controls;


architecture europa of slow_down_fifo_dcfifo_with_controls is
component slow_down_fifo_dual_clock_fifo is 
           port (
                 -- inputs:
                    signal aclr : IN STD_LOGIC;
                    signal data : IN STD_LOGIC_VECTOR (35 DOWNTO 0);
                    signal rdclk : IN STD_LOGIC;
                    signal rdreq : IN STD_LOGIC;
                    signal wrclk : IN STD_LOGIC;
                    signal wrreq : IN STD_LOGIC;

                 -- outputs:
                    signal q : OUT STD_LOGIC_VECTOR (35 DOWNTO 0);
                    signal rdempty : OUT STD_LOGIC;
                    signal wrfull : OUT STD_LOGIC;
                    signal wrusedw : OUT STD_LOGIC_VECTOR (7 DOWNTO 0)
                 );
end component slow_down_fifo_dual_clock_fifo;

                signal internal_q :  STD_LOGIC_VECTOR (35 DOWNTO 0);
                signal internal_rdempty :  STD_LOGIC;
                signal internal_wrfull :  STD_LOGIC;
                signal module_input :  STD_LOGIC;
                signal wrreq_valid :  STD_LOGIC;
                signal wrusedw :  STD_LOGIC_VECTOR (7 DOWNTO 0);

begin

  --the_dcfifo, which is an e_instance
  the_dcfifo : slow_down_fifo_dual_clock_fifo
    port map(
      q => internal_q,
      rdempty => internal_rdempty,
      wrfull => internal_wrfull,
      wrusedw => wrusedw,
      aclr => module_input,
      data => data,
      rdclk => rdclk,
      rdreq => rdreq,
      wrclk => wrclk,
      wrreq => wrreq_valid
    );

  module_input <= NOT wrreset_n;

  wrlevel <= Std_Logic_Vector'(A_ToStdLogicVector(std_logic'('0')) & wrusedw);
  wrreq_valid <= wrreq AND NOT internal_wrfull;
  --vhdl renameroo for output signals
  q <= internal_q;
  --vhdl renameroo for output signals
  rdempty <= internal_rdempty;
  --vhdl renameroo for output signals
  wrfull <= internal_wrfull;

end europa;



-- turn off superfluous VHDL processor warnings 
-- altera message_level Level1 
-- altera message_off 10034 10035 10036 10037 10230 10240 10030 

library altera;
use altera.altera_europa_support_lib.all;

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity slow_down_fifo is 
        port (
              -- inputs:
                 signal avalonst_sink_data : IN STD_LOGIC_VECTOR (31 DOWNTO 0);
                 signal avalonst_sink_empty : IN STD_LOGIC_VECTOR (1 DOWNTO 0);
                 signal avalonst_sink_endofpacket : IN STD_LOGIC;
                 signal avalonst_sink_startofpacket : IN STD_LOGIC;
                 signal avalonst_sink_valid : IN STD_LOGIC;
                 signal avalonst_source_ready : IN STD_LOGIC;
                 signal rdclock : IN STD_LOGIC;
                 signal rdreset_n : IN STD_LOGIC;
                 signal wrclock : IN STD_LOGIC;
                 signal wrreset_n : IN STD_LOGIC;

              -- outputs:
                 signal avalonst_sink_ready : OUT STD_LOGIC;
                 signal avalonst_source_data : OUT STD_LOGIC_VECTOR (31 DOWNTO 0);
                 signal avalonst_source_empty : OUT STD_LOGIC_VECTOR (1 DOWNTO 0);
                 signal avalonst_source_endofpacket : OUT STD_LOGIC;
                 signal avalonst_source_startofpacket : OUT STD_LOGIC;
                 signal avalonst_source_valid : OUT STD_LOGIC
              );
end entity slow_down_fifo;


architecture europa of slow_down_fifo is
component slow_down_fifo_dcfifo_with_controls is 
           port (
                 -- inputs:
                    signal data : IN STD_LOGIC_VECTOR (35 DOWNTO 0);
                    signal rdclk : IN STD_LOGIC;
                    signal rdreq : IN STD_LOGIC;
                    signal wrclk : IN STD_LOGIC;
                    signal wrreq : IN STD_LOGIC;
                    signal wrreset_n : IN STD_LOGIC;

                 -- outputs:
                    signal q : OUT STD_LOGIC_VECTOR (35 DOWNTO 0);
                    signal rdempty : OUT STD_LOGIC;
                    signal wrfull : OUT STD_LOGIC;
                    signal wrlevel : OUT STD_LOGIC_VECTOR (8 DOWNTO 0)
                 );
end component slow_down_fifo_dcfifo_with_controls;

                signal avalonst_sink_signals :  STD_LOGIC_VECTOR (35 DOWNTO 0);
                signal avalonst_source_signals :  STD_LOGIC_VECTOR (35 DOWNTO 0);
                signal data :  STD_LOGIC_VECTOR (35 DOWNTO 0);
                signal no_stop_write :  STD_LOGIC;
                signal no_stop_write_d1 :  STD_LOGIC;
                signal q :  STD_LOGIC_VECTOR (35 DOWNTO 0);
                signal rdclk :  STD_LOGIC;
                signal rdempty :  STD_LOGIC;
                signal rdreq :  STD_LOGIC;
                signal ready_0 :  STD_LOGIC;
                signal ready_1 :  STD_LOGIC;
                signal ready_selector :  STD_LOGIC;
                signal wrclk :  STD_LOGIC;
                signal wrfull :  STD_LOGIC;
                signal wrlevel :  STD_LOGIC_VECTOR (8 DOWNTO 0);
                signal wrreq :  STD_LOGIC;

begin

  --the_dcfifo_with_controls, which is an e_instance
  the_dcfifo_with_controls : slow_down_fifo_dcfifo_with_controls
    port map(
      q => q,
      rdempty => rdempty,
      wrfull => wrfull,
      wrlevel => wrlevel,
      data => data,
      rdclk => rdclk,
      rdreq => rdreq,
      wrclk => wrclk,
      wrreq => wrreq,
      wrreset_n => wrreset_n
    );


  --in, which is an e_atlantic_slave
  --out, which is an e_atlantic_master
  avalonst_sink_signals <= Std_Logic_Vector'(A_ToStdLogicVector(avalonst_sink_startofpacket) & A_ToStdLogicVector(avalonst_sink_endofpacket) & avalonst_sink_empty & avalonst_sink_data);
  (avalonst_source_startofpacket, avalonst_source_endofpacket, avalonst_source_empty(1), avalonst_source_empty(0), avalonst_source_data(31), avalonst_source_data(30), avalonst_source_data(29), avalonst_source_data(28), avalonst_source_data(27), avalonst_source_data(26), avalonst_source_data(25), avalonst_source_data(24), avalonst_source_data(23), avalonst_source_data(22), avalonst_source_data(21), avalonst_source_data(20), avalonst_source_data(19), avalonst_source_data(18), avalonst_source_data(17), avalonst_source_data(16), avalonst_source_data(15), avalonst_source_data(14), avalonst_source_data(13), avalonst_source_data(12), avalonst_source_data(11), avalonst_source_data(10), avalonst_source_data(9), avalonst_source_data(8), avalonst_source_data(7), avalonst_source_data(6), avalonst_source_data(5), avalonst_source_data(4), avalonst_source_data(3), avalonst_source_data(2), avalonst_source_data(1), avalonst_source_data(0)) <= avalonst_source_signals;
  no_stop_write <= ((ready_selector AND ready_1)) OR ((NOT(ready_selector) AND ready_0));
  wrreq <= avalonst_sink_valid AND no_stop_write_d1;
  ready_1 <= NOT(wrfull);
  ready_0 <= NOT(wrfull) AND NOT(avalonst_sink_valid);
  ready_selector <= to_std_logic(((std_logic_vector'("00000000000000000000000") & (wrlevel))<std_logic_vector'("00000000000000000000000011111100")));
  process (wrclk, wrreset_n)
  begin
    if wrreset_n = '0' then
      no_stop_write_d1 <= std_logic'('0');
    elsif wrclk'event and wrclk = '1' then
      no_stop_write_d1 <= no_stop_write;
    end if;

  end process;

  data <= avalonst_sink_signals;
  avalonst_source_signals <= q;
  wrclk <= wrclock;
  rdclk <= rdclock;
  avalonst_sink_ready <= no_stop_write AND no_stop_write_d1;
  process (rdclock, rdreset_n)
  begin
    if rdreset_n = '0' then
      avalonst_source_valid <= std_logic'('0');
    elsif rdclock'event and rdclock = '1' then
      avalonst_source_valid <= avalonst_source_ready AND NOT(rdempty);
    end if;

  end process;

  rdreq <= avalonst_source_ready AND NOT(rdempty);

end europa;

