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

--synthesis_resources = 
 LIBRARY ieee;
 USE ieee.std_logic_1164.all;

 ENTITY  lcd_pixel_converter IS 
	 PORT 
	 ( 
		 clk	:	IN  STD_LOGIC;
		 data_in	:	IN  STD_LOGIC_VECTOR (31 DOWNTO 0);
		 data_out	:	OUT  STD_LOGIC_VECTOR (23 DOWNTO 0);
		 empty_in	:	IN  STD_LOGIC_VECTOR (1 DOWNTO 0);
		 empty_out	:	OUT  STD_LOGIC_VECTOR (1 DOWNTO 0);
		 eop_in	:	IN  STD_LOGIC;
		 eop_out	:	OUT  STD_LOGIC;
		 ready_in	:	IN  STD_LOGIC;
		 ready_out	:	OUT  STD_LOGIC;
		 reset_n	:	IN  STD_LOGIC;
		 sop_in	:	IN  STD_LOGIC;
		 sop_out	:	OUT  STD_LOGIC;
		 valid_in	:	IN  STD_LOGIC;
		 valid_out	:	OUT  STD_LOGIC
	 ); 
 END lcd_pixel_converter;

 ARCHITECTURE RTL OF lcd_pixel_converter IS

	 ATTRIBUTE synthesis_clearbox : natural;
	 ATTRIBUTE synthesis_clearbox OF RTL : ARCHITECTURE IS 1;
 BEGIN

	data_out <= ( data_in(31 DOWNTO 8));
	empty_out <= ( empty_in(1 DOWNTO 0));
	eop_out <= eop_in;
	ready_out <= ready_in;
	sop_out <= sop_in;
	valid_out <= valid_in;

 END RTL; --lcd_pixel_converter
--synopsys translate_on
--VALID FILE
