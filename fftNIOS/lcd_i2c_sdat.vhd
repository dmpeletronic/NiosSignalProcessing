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

entity lcd_i2c_sdat is 
        port (
              -- inputs:
                 signal address : IN STD_LOGIC_VECTOR (1 DOWNTO 0);
                 signal chipselect : IN STD_LOGIC;
                 signal clk : IN STD_LOGIC;
                 signal reset_n : IN STD_LOGIC;
                 signal write_n : IN STD_LOGIC;
                 signal writedata : IN STD_LOGIC;

              -- outputs:
                 signal bidir_port : INOUT STD_LOGIC;
                 signal readdata : OUT STD_LOGIC
              );
end entity lcd_i2c_sdat;


architecture europa of lcd_i2c_sdat is
                signal clk_en :  STD_LOGIC;
                signal data_dir :  STD_LOGIC;
                signal data_in :  STD_LOGIC;
                signal data_out :  STD_LOGIC;
                signal read_mux_out :  STD_LOGIC;

begin

  clk_en <= std_logic'('1');
  --s1, which is an e_avalon_slave
  read_mux_out <= ((to_std_logic((((std_logic_vector'("000000000000000000000000000000") & (address)) = std_logic_vector'("00000000000000000000000000000000")))) AND data_in)) OR ((to_std_logic((((std_logic_vector'("000000000000000000000000000000") & (address)) = std_logic_vector'("00000000000000000000000000000001")))) AND data_dir));
  process (clk, reset_n)
  begin
    if reset_n = '0' then
      readdata <= std_logic'('0');
    elsif clk'event and clk = '1' then
      if std_logic'(clk_en) = '1' then 
        readdata <= read_mux_out;
      end if;
    end if;

  end process;

  process (clk, reset_n)
  begin
    if reset_n = '0' then
      data_out <= std_logic'('0');
    elsif clk'event and clk = '1' then
      if std_logic'(((chipselect AND NOT write_n) AND to_std_logic((((std_logic_vector'("000000000000000000000000000000") & (address)) = std_logic_vector'("00000000000000000000000000000000")))))) = '1' then 
        data_out <= writedata;
      end if;
    end if;

  end process;

  bidir_port <= A_WE_StdLogic((std_logic'(data_dir) = '1'), data_out, std_logic'('Z'));
  data_in <= bidir_port;
  process (clk, reset_n)
  begin
    if reset_n = '0' then
      data_dir <= std_logic'('0');
    elsif clk'event and clk = '1' then
      if std_logic'(((chipselect AND NOT write_n) AND to_std_logic((((std_logic_vector'("000000000000000000000000000000") & (address)) = std_logic_vector'("00000000000000000000000000000001")))))) = '1' then 
        data_dir <= writedata;
      end if;
    end if;

  end process;


end europa;

