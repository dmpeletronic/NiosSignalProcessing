--IP Functional Simulation Model
--VERSION_BEGIN 10.1SP1 cbx_mgl 2011:01:19:21:15:40:SJ cbx_simgen 2011:01:19:21:13:40:SJ  VERSION_END


-- Copyright (C) 1991-2011 Altera Corporation
-- Your use of Altera Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Altera Program License 
-- Subscription Agreement, Altera MegaCore Function License 
-- Agreement, or other applicable license agreement, including, 
-- without limitation, that your use is for the sole purpose of 
-- programming logic devices manufactured by Altera and sold by 
-- Altera or its authorized distributors.  Please refer to the 
-- applicable agreement for further details.

-- You may only use these simulation model output files for simulation
-- purposes and expressly not for synthesis or any other purposes (in which
-- event Altera disclaims all warranties of any kind).


--synopsys translate_off

--synthesis_resources = lut 1 
 LIBRARY ieee;
 USE ieee.std_logic_1164.all;

 ENTITY  timing_adapter_0 IS 
	 PORT 
	 ( 
		 clk	:	IN  STD_LOGIC;
		 in_data	:	IN  STD_LOGIC_VECTOR (31 DOWNTO 0);
		 in_empty	:	IN  STD_LOGIC_VECTOR (1 DOWNTO 0);
		 in_endofpacket	:	IN  STD_LOGIC;
		 in_ready	:	OUT  STD_LOGIC;
		 in_startofpacket	:	IN  STD_LOGIC;
		 in_valid	:	IN  STD_LOGIC;
		 out_data	:	OUT  STD_LOGIC_VECTOR (31 DOWNTO 0);
		 out_empty	:	OUT  STD_LOGIC_VECTOR (1 DOWNTO 0);
		 out_endofpacket	:	OUT  STD_LOGIC;
		 out_ready	:	IN  STD_LOGIC;
		 out_startofpacket	:	OUT  STD_LOGIC;
		 out_valid	:	OUT  STD_LOGIC;
		 reset_n	:	IN  STD_LOGIC
	 ); 
 END timing_adapter_0;

 ARCHITECTURE RTL OF timing_adapter_0 IS

	 ATTRIBUTE synthesis_clearbox : natural;
	 ATTRIBUTE synthesis_clearbox OF RTL : ARCHITECTURE IS 1;
	 SIGNAL	timing_adapter_0_ready_0_1q	:	STD_LOGIC := '0';
	 SIGNAL  s_wire_vcc :	STD_LOGIC;
 BEGIN

	in_ready <= timing_adapter_0_ready_0_1q;
	out_data <= ( in_data(31 DOWNTO 0));
	out_empty <= ( in_empty(1 DOWNTO 0));
	out_endofpacket <= in_endofpacket;
	out_startofpacket <= in_startofpacket;
	out_valid <= (timing_adapter_0_ready_0_1q AND in_valid);
	s_wire_vcc <= '1';
	PROCESS (clk, reset_n)
	BEGIN
		IF (reset_n = '0') THEN
				timing_adapter_0_ready_0_1q <= '0';
		ELSIF (clk = '1' AND clk'event) THEN
				timing_adapter_0_ready_0_1q <= out_ready;
		END IF;
	END PROCESS;

 END RTL; --timing_adapter_0
--synopsys translate_on
--VALID FILE
