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

library altera_mf;
use altera_mf.all;

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

library lpm;
use lpm.all;

entity tse_ddr_clock_bridge_downstream_fifo is 
        port (
              -- inputs:
                 signal aclr : IN STD_LOGIC;
                 signal data : IN STD_LOGIC_VECTOR (83 DOWNTO 0);
                 signal rdclk : IN STD_LOGIC;
                 signal rdreq : IN STD_LOGIC;
                 signal wrclk : IN STD_LOGIC;
                 signal wrreq : IN STD_LOGIC;

              -- outputs:
                 signal q : OUT STD_LOGIC_VECTOR (83 DOWNTO 0);
                 signal rdempty : OUT STD_LOGIC;
                 signal wrfull : OUT STD_LOGIC
              );
end entity tse_ddr_clock_bridge_downstream_fifo;


architecture europa of tse_ddr_clock_bridge_downstream_fifo is
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
        signal q : OUT STD_LOGIC_VECTOR (83 DOWNTO 0);
        signal rdreq : IN STD_LOGIC;
        signal aclr : IN STD_LOGIC;
        signal data : IN STD_LOGIC_VECTOR (83 DOWNTO 0);
        signal wrclk : IN STD_LOGIC;
        signal rdclk : IN STD_LOGIC;
        signal wrreq : IN STD_LOGIC
      );
  end component dcfifo;
                signal internal_q :  STD_LOGIC_VECTOR (83 DOWNTO 0);
                signal internal_rdempty :  STD_LOGIC;
                signal internal_wrfull :  STD_LOGIC;

begin

  downstream_fifo : dcfifo
    generic map(
      intended_device_family => "CYCLONEIII",
      lpm_numwords => 8,
      lpm_showahead => "OFF",
      lpm_type => "dcfifo",
      lpm_width => 84,
      lpm_widthu => 3,
      overflow_checking => "ON",
      rdsync_delaypipe => 5,
      underflow_checking => "ON",
      use_eab => "ON",
      wrsync_delaypipe => 5
    )
    port map(
            aclr => aclr,
            data => data,
            q => internal_q,
            rdclk => rdclk,
            rdempty => internal_rdempty,
            rdreq => rdreq,
            wrclk => wrclk,
            wrfull => internal_wrfull,
            wrreq => wrreq
    );

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

library altera_mf;
use altera_mf.all;

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

library lpm;
use lpm.all;

entity tse_ddr_clock_bridge_upstream_fifo is 
        port (
              -- inputs:
                 signal aclr : IN STD_LOGIC;
                 signal data : IN STD_LOGIC_VECTOR (32 DOWNTO 0);
                 signal rdclk : IN STD_LOGIC;
                 signal rdreq : IN STD_LOGIC;
                 signal wrclk : IN STD_LOGIC;
                 signal wrreq : IN STD_LOGIC;

              -- outputs:
                 signal q : OUT STD_LOGIC_VECTOR (32 DOWNTO 0);
                 signal rdempty : OUT STD_LOGIC;
                 signal wrusedw : OUT STD_LOGIC_VECTOR (5 DOWNTO 0)
              );
end entity tse_ddr_clock_bridge_upstream_fifo;


architecture europa of tse_ddr_clock_bridge_upstream_fifo is
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
    signal wrusedw : OUT STD_LOGIC_VECTOR (5 DOWNTO 0);
        signal rdempty : OUT STD_LOGIC;
        signal q : OUT STD_LOGIC_VECTOR (32 DOWNTO 0);
        signal rdreq : IN STD_LOGIC;
        signal rdclk : IN STD_LOGIC;
        signal aclr : IN STD_LOGIC;
        signal wrreq : IN STD_LOGIC;
        signal data : IN STD_LOGIC_VECTOR (32 DOWNTO 0);
        signal wrclk : IN STD_LOGIC
      );
  end component dcfifo;
                signal internal_q1 :  STD_LOGIC_VECTOR (32 DOWNTO 0);
                signal internal_rdempty1 :  STD_LOGIC;
                signal internal_wrusedw :  STD_LOGIC_VECTOR (5 DOWNTO 0);

begin

  upstream_fifo : dcfifo
    generic map(
      intended_device_family => "CYCLONEIII",
      lpm_numwords => 64,
      lpm_showahead => "OFF",
      lpm_type => "dcfifo",
      lpm_width => 33,
      lpm_widthu => 6,
      overflow_checking => "ON",
      rdsync_delaypipe => 5,
      underflow_checking => "ON",
      use_eab => "ON",
      wrsync_delaypipe => 5
    )
    port map(
            aclr => aclr,
            data => data,
            q => internal_q1,
            rdclk => rdclk,
            rdempty => internal_rdempty1,
            rdreq => rdreq,
            wrclk => wrclk,
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

entity tse_ddr_clock_bridge is 
        port (
              -- inputs:
                 signal master_clk : IN STD_LOGIC;
                 signal master_endofpacket : IN STD_LOGIC;
                 signal master_readdata : IN STD_LOGIC_VECTOR (31 DOWNTO 0);
                 signal master_readdatavalid : IN STD_LOGIC;
                 signal master_reset_n : IN STD_LOGIC;
                 signal master_waitrequest : IN STD_LOGIC;
                 signal slave_address : IN STD_LOGIC_VECTOR (22 DOWNTO 0);
                 signal slave_byteenable : IN STD_LOGIC_VECTOR (3 DOWNTO 0);
                 signal slave_clk : IN STD_LOGIC;
                 signal slave_nativeaddress : IN STD_LOGIC_VECTOR (22 DOWNTO 0);
                 signal slave_read : IN STD_LOGIC;
                 signal slave_reset_n : IN STD_LOGIC;
                 signal slave_write : IN STD_LOGIC;
                 signal slave_writedata : IN STD_LOGIC_VECTOR (31 DOWNTO 0);

              -- outputs:
                 signal master_address : OUT STD_LOGIC_VECTOR (24 DOWNTO 0);
                 signal master_byteenable : OUT STD_LOGIC_VECTOR (3 DOWNTO 0);
                 signal master_nativeaddress : OUT STD_LOGIC_VECTOR (22 DOWNTO 0);
                 signal master_read : OUT STD_LOGIC;
                 signal master_write : OUT STD_LOGIC;
                 signal master_writedata : OUT STD_LOGIC_VECTOR (31 DOWNTO 0);
                 signal slave_endofpacket : OUT STD_LOGIC;
                 signal slave_readdata : OUT STD_LOGIC_VECTOR (31 DOWNTO 0);
                 signal slave_readdatavalid : OUT STD_LOGIC;
                 signal slave_waitrequest : OUT STD_LOGIC
              );
end entity tse_ddr_clock_bridge;


architecture europa of tse_ddr_clock_bridge is
component tse_ddr_clock_bridge_downstream_fifo is 
           port (
                 -- inputs:
                    signal aclr : IN STD_LOGIC;
                    signal data : IN STD_LOGIC_VECTOR (83 DOWNTO 0);
                    signal rdclk : IN STD_LOGIC;
                    signal rdreq : IN STD_LOGIC;
                    signal wrclk : IN STD_LOGIC;
                    signal wrreq : IN STD_LOGIC;

                 -- outputs:
                    signal q : OUT STD_LOGIC_VECTOR (83 DOWNTO 0);
                    signal rdempty : OUT STD_LOGIC;
                    signal wrfull : OUT STD_LOGIC
                 );
end component tse_ddr_clock_bridge_downstream_fifo;

component tse_ddr_clock_bridge_upstream_fifo is 
           port (
                 -- inputs:
                    signal aclr : IN STD_LOGIC;
                    signal data : IN STD_LOGIC_VECTOR (32 DOWNTO 0);
                    signal rdclk : IN STD_LOGIC;
                    signal rdreq : IN STD_LOGIC;
                    signal wrclk : IN STD_LOGIC;
                    signal wrreq : IN STD_LOGIC;

                 -- outputs:
                    signal q : OUT STD_LOGIC_VECTOR (32 DOWNTO 0);
                    signal rdempty : OUT STD_LOGIC;
                    signal wrusedw : OUT STD_LOGIC_VECTOR (5 DOWNTO 0)
                 );
end component tse_ddr_clock_bridge_upstream_fifo;

                signal downstream_data_in :  STD_LOGIC_VECTOR (83 DOWNTO 0);
                signal downstream_data_out :  STD_LOGIC_VECTOR (83 DOWNTO 0);
                signal downstream_rdempty :  STD_LOGIC;
                signal downstream_rdempty_delayed_n :  STD_LOGIC;
                signal downstream_rdreq :  STD_LOGIC;
                signal downstream_wrfull :  STD_LOGIC;
                signal downstream_wrreq :  STD_LOGIC;
                signal downstream_wrreq_delayed :  STD_LOGIC;
                signal internal_master_address :  STD_LOGIC_VECTOR (22 DOWNTO 0);
                signal internal_master_read :  STD_LOGIC;
                signal internal_master_write :  STD_LOGIC;
                signal master_byte_address :  STD_LOGIC_VECTOR (24 DOWNTO 0);
                signal master_hold_read :  STD_LOGIC;
                signal master_hold_write :  STD_LOGIC;
                signal master_new_read :  STD_LOGIC;
                signal master_new_read_term_one :  STD_LOGIC;
                signal master_new_read_term_two :  STD_LOGIC;
                signal master_new_write :  STD_LOGIC;
                signal master_new_write_term_one :  STD_LOGIC;
                signal master_new_write_term_two :  STD_LOGIC;
                signal master_read_write_unchanged_on_wait :  STD_LOGIC;
                signal master_waitrequest_delayed :  STD_LOGIC;
                signal module_input :  STD_LOGIC;
                signal module_input1 :  STD_LOGIC;
                signal upstream_data_in :  STD_LOGIC_VECTOR (32 DOWNTO 0);
                signal upstream_data_out :  STD_LOGIC_VECTOR (32 DOWNTO 0);
                signal upstream_rdempty :  STD_LOGIC;
                signal upstream_rdreq :  STD_LOGIC;
                signal upstream_write_almost_full :  STD_LOGIC;
                signal upstream_write_almost_full_delayed :  STD_LOGIC;
                signal upstream_wrreq :  STD_LOGIC;
                signal upstream_wrusedw :  STD_LOGIC_VECTOR (5 DOWNTO 0);

begin

  --s1, which is an e_avalon_slave
  --m1, which is an e_avalon_master
  upstream_data_in <= master_readdata & A_ToStdLogicVector(master_endofpacket);
  (slave_readdata(31), slave_readdata(30), slave_readdata(29), slave_readdata(28), slave_readdata(27), slave_readdata(26), slave_readdata(25), slave_readdata(24), slave_readdata(23), slave_readdata(22), slave_readdata(21), slave_readdata(20), slave_readdata(19), slave_readdata(18), slave_readdata(17), slave_readdata(16), slave_readdata(15), slave_readdata(14), slave_readdata(13), slave_readdata(12), slave_readdata(11), slave_readdata(10), slave_readdata(9), slave_readdata(8), slave_readdata(7), slave_readdata(6), slave_readdata(5), slave_readdata(4), slave_readdata(3), slave_readdata(2), slave_readdata(1), slave_readdata(0), slave_endofpacket) <= upstream_data_out;
  downstream_data_in <= slave_writedata & slave_address & A_ToStdLogicVector(slave_read) & A_ToStdLogicVector(slave_write) & slave_nativeaddress & slave_byteenable;
  (master_writedata(31), master_writedata(30), master_writedata(29), master_writedata(28), master_writedata(27), master_writedata(26), master_writedata(25), master_writedata(24), master_writedata(23), master_writedata(22), master_writedata(21), master_writedata(20), master_writedata(19), master_writedata(18), master_writedata(17), master_writedata(16), master_writedata(15), master_writedata(14), master_writedata(13), master_writedata(12), master_writedata(11), master_writedata(10), master_writedata(9), master_writedata(8), master_writedata(7), master_writedata(6), master_writedata(5), master_writedata(4), master_writedata(3), master_writedata(2), master_writedata(1), master_writedata(0), internal_master_address(22), internal_master_address(21), internal_master_address(20), internal_master_address(19), internal_master_address(18), internal_master_address(17), internal_master_address(16), internal_master_address(15), internal_master_address(14), internal_master_address(13), internal_master_address(12), internal_master_address(11), internal_master_address(10), internal_master_address(9), internal_master_address(8), internal_master_address(7), internal_master_address(6), internal_master_address(5), internal_master_address(4), internal_master_address(3), internal_master_address(2), internal_master_address(1), internal_master_address(0), internal_master_read, internal_master_write, master_nativeaddress(22), master_nativeaddress(21), master_nativeaddress(20), master_nativeaddress(19), master_nativeaddress(18), master_nativeaddress(17), master_nativeaddress(16), master_nativeaddress(15), master_nativeaddress(14), master_nativeaddress(13), master_nativeaddress(12), master_nativeaddress(11), master_nativeaddress(10), master_nativeaddress(9), master_nativeaddress(8), master_nativeaddress(7), master_nativeaddress(6), master_nativeaddress(5), master_nativeaddress(4), master_nativeaddress(3), master_nativeaddress(2), master_nativeaddress(1), master_nativeaddress(0), master_byteenable(3), master_byteenable(2), master_byteenable(1), master_byteenable(0)) <= downstream_data_out;
  --the_downstream_fifo, which is an e_instance
  the_downstream_fifo : tse_ddr_clock_bridge_downstream_fifo
    port map(
      q => downstream_data_out,
      rdempty => downstream_rdempty,
      wrfull => downstream_wrfull,
      aclr => module_input,
      data => downstream_data_in,
      rdclk => master_clk,
      rdreq => downstream_rdreq,
      wrclk => slave_clk,
      wrreq => downstream_wrreq
    );

  module_input <= NOT slave_reset_n;

  downstream_wrreq <= (slave_read OR slave_write) OR downstream_wrreq_delayed;
  slave_waitrequest <= downstream_wrfull;
  downstream_rdreq <= (NOT(downstream_rdempty) AND NOT(master_waitrequest)) AND NOT(upstream_write_almost_full);
  upstream_write_almost_full <= to_std_logic(((std_logic_vector'("00000000000000000000000000") & (upstream_wrusedw))>=std_logic_vector'("00000000000000000000000000000111")));
  process (slave_clk, slave_reset_n)
  begin
    if slave_reset_n = '0' then
      downstream_wrreq_delayed <= std_logic'('0');
    elsif slave_clk'event and slave_clk = '1' then
      downstream_wrreq_delayed <= slave_read OR slave_write;
    end if;

  end process;

  master_new_read_term_one <= internal_master_read AND downstream_rdempty_delayed_n;
  master_new_read_term_two <= NOT(master_read_write_unchanged_on_wait) AND NOT(upstream_write_almost_full_delayed);
  master_new_read <= master_new_read_term_one AND master_new_read_term_two;
  master_hold_read <= master_read_write_unchanged_on_wait AND internal_master_read;
  master_new_write_term_one <= internal_master_write AND downstream_rdempty_delayed_n;
  master_new_write_term_two <= NOT(master_read_write_unchanged_on_wait) AND NOT(upstream_write_almost_full_delayed);
  master_new_write <= master_new_write_term_one AND master_new_write_term_two;
  master_hold_write <= master_read_write_unchanged_on_wait AND internal_master_write;
  master_read_write_unchanged_on_wait <= master_waitrequest_delayed;
  process (master_clk, master_reset_n)
  begin
    if master_reset_n = '0' then
      master_waitrequest_delayed <= std_logic'('0');
    elsif master_clk'event and master_clk = '1' then
      master_waitrequest_delayed <= master_waitrequest;
    end if;

  end process;

  master_read <= master_new_read OR master_hold_read;
  master_write <= master_new_write OR master_hold_write;
  process (master_clk, master_reset_n)
  begin
    if master_reset_n = '0' then
      downstream_rdempty_delayed_n <= std_logic'('0');
    elsif master_clk'event and master_clk = '1' then
      downstream_rdempty_delayed_n <= NOT(downstream_rdempty);
    end if;

  end process;

  process (master_clk, master_reset_n)
  begin
    if master_reset_n = '0' then
      upstream_write_almost_full_delayed <= std_logic'('0');
    elsif master_clk'event and master_clk = '1' then
      upstream_write_almost_full_delayed <= upstream_write_almost_full;
    end if;

  end process;

  master_byte_address <= internal_master_address & std_logic_vector'("00");
  master_address <= master_byte_address;
  --the_upstream_fifo, which is an e_instance
  the_upstream_fifo : tse_ddr_clock_bridge_upstream_fifo
    port map(
      q => upstream_data_out,
      rdempty => upstream_rdempty,
      wrusedw => upstream_wrusedw,
      aclr => module_input1,
      data => upstream_data_in,
      rdclk => slave_clk,
      rdreq => upstream_rdreq,
      wrclk => master_clk,
      wrreq => upstream_wrreq
    );

  module_input1 <= NOT master_reset_n;

  upstream_wrreq <= master_readdatavalid;
  upstream_rdreq <= NOT(upstream_rdempty);
  process (slave_clk, slave_reset_n)
  begin
    if slave_reset_n = '0' then
      slave_readdatavalid <= std_logic'('0');
    elsif slave_clk'event and slave_clk = '1' then
      slave_readdatavalid <= NOT(upstream_rdempty);
    end if;

  end process;


end europa;

