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

 LIBRARY sgate;
 USE sgate.sgate_pack.all;

--synthesis_resources = lut 43 mux21 28 oper_add 1 oper_decoder 1 oper_less_than 3 oper_mux 14 
 LIBRARY ieee;
 USE ieee.std_logic_1164.all;

 ENTITY  lcd_24_to_8_bits_dfa IS 
	 PORT 
	 ( 
		 clk	:	IN  STD_LOGIC;
		 in_data	:	IN  STD_LOGIC_VECTOR (23 DOWNTO 0);
		 in_empty	:	IN  STD_LOGIC_VECTOR (1 DOWNTO 0);
		 in_endofpacket	:	IN  STD_LOGIC;
		 in_ready	:	OUT  STD_LOGIC;
		 in_startofpacket	:	IN  STD_LOGIC;
		 in_valid	:	IN  STD_LOGIC;
		 out_data	:	OUT  STD_LOGIC_VECTOR (7 DOWNTO 0);
		 out_empty	:	OUT  STD_LOGIC;
		 out_endofpacket	:	OUT  STD_LOGIC;
		 out_ready	:	IN  STD_LOGIC;
		 out_startofpacket	:	OUT  STD_LOGIC;
		 out_valid	:	OUT  STD_LOGIC;
		 reset_n	:	IN  STD_LOGIC
	 ); 
 END lcd_24_to_8_bits_dfa;

 ARCHITECTURE RTL OF lcd_24_to_8_bits_dfa IS

	 ATTRIBUTE synthesis_clearbox : natural;
	 ATTRIBUTE synthesis_clearbox OF RTL : ARCHITECTURE IS 1;
	 SIGNAL	lcd_24_to_8_bits_dfa_out_data_0_reg0_138q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_out_data_1_reg0_137q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_out_data_2_reg0_136q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_out_data_3_reg0_135q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_out_data_4_reg0_134q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_out_data_5_reg0_133q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_out_data_6_reg0_132q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_out_data_7_reg0_131q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_out_empty_reg0_129q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_out_endofpacket_reg0_140q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_out_startofpacket_reg0_139q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_out_valid_reg0_130q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_state_register_0_128q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_state_register_1_61q	:	STD_LOGIC := '0';
	 SIGNAL  wire_nl_w_lg_lcd_24_to_8_bits_dfa_out_valid_reg0_130q60w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL	lcd_24_to_8_bits_dfa_a_data0_0_40q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_data0_1_39q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_data0_2_38q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_data0_3_37q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_data0_4_36q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_data0_5_35q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_data0_6_34q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_data0_7_33q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_data1_0_48q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_data1_1_47q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_data1_2_46q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_data1_3_45q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_data1_4_44q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_data1_5_43q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_data1_6_42q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_data1_7_41q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_data2_0_56q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_data2_1_55q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_data2_2_54q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_data2_3_53q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_data2_4_52q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_data2_5_51q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_data2_6_50q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_data2_7_49q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_empty_0_60q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_empty_1_59q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_endofpacket_58q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_startofpacket_57q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_24_to_8_bits_dfa_a_valid_32q	:	STD_LOGIC := '0';
	 SIGNAL  wire_nO_w_lg_lcd_24_to_8_bits_dfa_a_valid_32q199w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_a_empty_1m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_a_empty_2m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_a_ready_69m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_a_ready_72m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_a_ready_79m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_a_ready_82m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_b_empty_65m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_b_empty_68m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_b_empty_71m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_b_empty_76m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_b_empty_78m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_b_empty_81m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_b_empty_87m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_b_empty_90m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_b_empty_95m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_b_endofpacket_91m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_b_endofpacket_96m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_b_startofpacket_106m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_b_valid_92m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_new_state_67m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_new_state_70m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_new_state_77m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_new_state_80m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_new_state_88m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_new_state_89m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_new_state_93m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_new_state_94m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_24_to_8_bits_dfa_out_valid_reg0_186m_dataout	:	STD_LOGIC;
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_add0_75_a	:	STD_LOGIC_VECTOR (2 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_add0_75_b	:	STD_LOGIC_VECTOR (2 DOWNTO 0);
	 SIGNAL  wire_gnd	:	STD_LOGIC;
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_add0_75_o	:	STD_LOGIC_VECTOR (2 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_decoder0_105_i	:	STD_LOGIC_VECTOR (1 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_decoder0_105_o	:	STD_LOGIC_VECTOR (3 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_lessthan0_63_a	:	STD_LOGIC_VECTOR (1 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_lessthan0_63_b	:	STD_LOGIC_VECTOR (1 DOWNTO 0);
	 SIGNAL  wire_vcc	:	STD_LOGIC;
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_lessthan0_63_o	:	STD_LOGIC;
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_lessthan1_73_a	:	STD_LOGIC_VECTOR (1 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_lessthan1_73_b	:	STD_LOGIC_VECTOR (1 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_lessthan1_73_o	:	STD_LOGIC;
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_lessthan2_85_a	:	STD_LOGIC_VECTOR (1 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_lessthan2_85_b	:	STD_LOGIC_VECTOR (1 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_lessthan2_85_o	:	STD_LOGIC;
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux0_97_data	:	STD_LOGIC_VECTOR (3 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux0_97_o	:	STD_LOGIC;
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux0_97_sel	:	STD_LOGIC_VECTOR (1 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux10_109_data	:	STD_LOGIC_VECTOR (3 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux10_109_o	:	STD_LOGIC;
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux10_109_sel	:	STD_LOGIC_VECTOR (1 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux11_110_data	:	STD_LOGIC_VECTOR (3 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux11_110_o	:	STD_LOGIC;
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux11_110_sel	:	STD_LOGIC_VECTOR (1 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux12_111_data	:	STD_LOGIC_VECTOR (3 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux12_111_o	:	STD_LOGIC;
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux12_111_sel	:	STD_LOGIC_VECTOR (1 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux13_112_data	:	STD_LOGIC_VECTOR (3 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux13_112_o	:	STD_LOGIC;
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux13_112_sel	:	STD_LOGIC_VECTOR (1 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux1_98_data	:	STD_LOGIC_VECTOR (3 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux1_98_o	:	STD_LOGIC;
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux1_98_sel	:	STD_LOGIC_VECTOR (1 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux2_99_data	:	STD_LOGIC_VECTOR (3 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux2_99_o	:	STD_LOGIC;
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux2_99_sel	:	STD_LOGIC_VECTOR (1 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux3_100_data	:	STD_LOGIC_VECTOR (3 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux3_100_o	:	STD_LOGIC;
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux3_100_sel	:	STD_LOGIC_VECTOR (1 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux4_101_data	:	STD_LOGIC_VECTOR (3 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux4_101_o	:	STD_LOGIC;
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux4_101_sel	:	STD_LOGIC_VECTOR (1 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux5_102_data	:	STD_LOGIC_VECTOR (3 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux5_102_o	:	STD_LOGIC;
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux5_102_sel	:	STD_LOGIC_VECTOR (1 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux6_103_data	:	STD_LOGIC_VECTOR (3 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux6_103_o	:	STD_LOGIC;
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux6_103_sel	:	STD_LOGIC_VECTOR (1 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux7_104_data	:	STD_LOGIC_VECTOR (3 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux7_104_o	:	STD_LOGIC;
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux7_104_sel	:	STD_LOGIC_VECTOR (1 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux8_107_data	:	STD_LOGIC_VECTOR (3 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux8_107_o	:	STD_LOGIC;
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux8_107_sel	:	STD_LOGIC_VECTOR (1 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux9_108_data	:	STD_LOGIC_VECTOR (3 DOWNTO 0);
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux9_108_o	:	STD_LOGIC;
	 SIGNAL  wire_lcd_24_to_8_bits_dfa_mux9_108_sel	:	STD_LOGIC_VECTOR (1 DOWNTO 0);
	 SIGNAL  wire_w36w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w59w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  s_wire_lcd_24_to_8_bits_dfa_always4_64_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_lcd_24_to_8_bits_dfa_always4_74_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_lcd_24_to_8_bits_dfa_always4_84_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_lcd_24_to_8_bits_dfa_always4_86_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_lcd_24_to_8_bits_dfa_in_ready_114_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_vcc :	STD_LOGIC;
 BEGIN

	wire_gnd <= '0';
	wire_vcc <= '1';
	wire_w36w(0) <= NOT s_wire_lcd_24_to_8_bits_dfa_always4_64_dataout;
	wire_w59w(0) <= NOT s_wire_lcd_24_to_8_bits_dfa_always4_74_dataout;
	in_ready <= s_wire_lcd_24_to_8_bits_dfa_in_ready_114_dataout;
	out_data <= ( lcd_24_to_8_bits_dfa_out_data_7_reg0_131q & lcd_24_to_8_bits_dfa_out_data_6_reg0_132q & lcd_24_to_8_bits_dfa_out_data_5_reg0_133q & lcd_24_to_8_bits_dfa_out_data_4_reg0_134q & lcd_24_to_8_bits_dfa_out_data_3_reg0_135q & lcd_24_to_8_bits_dfa_out_data_2_reg0_136q & lcd_24_to_8_bits_dfa_out_data_1_reg0_137q & lcd_24_to_8_bits_dfa_out_data_0_reg0_138q);
	out_empty <= lcd_24_to_8_bits_dfa_out_empty_reg0_129q;
	out_endofpacket <= lcd_24_to_8_bits_dfa_out_endofpacket_reg0_140q;
	out_startofpacket <= lcd_24_to_8_bits_dfa_out_startofpacket_reg0_139q;
	out_valid <= lcd_24_to_8_bits_dfa_out_valid_reg0_130q;
	s_wire_lcd_24_to_8_bits_dfa_always4_64_dataout <= (lcd_24_to_8_bits_dfa_a_endofpacket_58q AND wire_lcd_24_to_8_bits_dfa_lessthan0_63_o);
	s_wire_lcd_24_to_8_bits_dfa_always4_74_dataout <= (lcd_24_to_8_bits_dfa_a_endofpacket_58q AND wire_lcd_24_to_8_bits_dfa_lessthan1_73_o);
	s_wire_lcd_24_to_8_bits_dfa_always4_84_dataout <= (wire_nl_w_lg_lcd_24_to_8_bits_dfa_out_valid_reg0_130q60w(0) OR out_ready);
	s_wire_lcd_24_to_8_bits_dfa_always4_86_dataout <= (lcd_24_to_8_bits_dfa_a_endofpacket_58q AND wire_lcd_24_to_8_bits_dfa_lessthan2_85_o);
	s_wire_lcd_24_to_8_bits_dfa_in_ready_114_dataout <= (wire_nO_w_lg_lcd_24_to_8_bits_dfa_a_valid_32q199w(0) OR wire_lcd_24_to_8_bits_dfa_mux8_107_o);
	s_wire_vcc <= '1';
	PROCESS (clk, reset_n)
	BEGIN
		IF (reset_n = '0') THEN
				lcd_24_to_8_bits_dfa_out_data_0_reg0_138q <= '0';
				lcd_24_to_8_bits_dfa_out_data_1_reg0_137q <= '0';
				lcd_24_to_8_bits_dfa_out_data_2_reg0_136q <= '0';
				lcd_24_to_8_bits_dfa_out_data_3_reg0_135q <= '0';
				lcd_24_to_8_bits_dfa_out_data_4_reg0_134q <= '0';
				lcd_24_to_8_bits_dfa_out_data_5_reg0_133q <= '0';
				lcd_24_to_8_bits_dfa_out_data_6_reg0_132q <= '0';
				lcd_24_to_8_bits_dfa_out_data_7_reg0_131q <= '0';
				lcd_24_to_8_bits_dfa_out_empty_reg0_129q <= '0';
				lcd_24_to_8_bits_dfa_out_endofpacket_reg0_140q <= '0';
				lcd_24_to_8_bits_dfa_out_startofpacket_reg0_139q <= '0';
		ELSIF (clk = '1' AND clk'event) THEN
			IF (s_wire_lcd_24_to_8_bits_dfa_always4_84_dataout = '1') THEN
				lcd_24_to_8_bits_dfa_out_data_0_reg0_138q <= wire_lcd_24_to_8_bits_dfa_mux7_104_o;
				lcd_24_to_8_bits_dfa_out_data_1_reg0_137q <= wire_lcd_24_to_8_bits_dfa_mux6_103_o;
				lcd_24_to_8_bits_dfa_out_data_2_reg0_136q <= wire_lcd_24_to_8_bits_dfa_mux5_102_o;
				lcd_24_to_8_bits_dfa_out_data_3_reg0_135q <= wire_lcd_24_to_8_bits_dfa_mux4_101_o;
				lcd_24_to_8_bits_dfa_out_data_4_reg0_134q <= wire_lcd_24_to_8_bits_dfa_mux3_100_o;
				lcd_24_to_8_bits_dfa_out_data_5_reg0_133q <= wire_lcd_24_to_8_bits_dfa_mux2_99_o;
				lcd_24_to_8_bits_dfa_out_data_6_reg0_132q <= wire_lcd_24_to_8_bits_dfa_mux1_98_o;
				lcd_24_to_8_bits_dfa_out_data_7_reg0_131q <= wire_lcd_24_to_8_bits_dfa_mux0_97_o;
				lcd_24_to_8_bits_dfa_out_empty_reg0_129q <= wire_lcd_24_to_8_bits_dfa_mux12_111_o;
				lcd_24_to_8_bits_dfa_out_endofpacket_reg0_140q <= wire_lcd_24_to_8_bits_dfa_mux13_112_o;
				lcd_24_to_8_bits_dfa_out_startofpacket_reg0_139q <= wire_lcd_24_to_8_bits_dfa_b_startofpacket_106m_dataout;
			END IF;
		END IF;
	END PROCESS;
	PROCESS (clk, reset_n)
	BEGIN
		IF (reset_n = '0') THEN
				lcd_24_to_8_bits_dfa_out_valid_reg0_130q <= '0';
				lcd_24_to_8_bits_dfa_state_register_0_128q <= '0';
				lcd_24_to_8_bits_dfa_state_register_1_61q <= '0';
		ELSIF (clk = '1' AND clk'event) THEN
				lcd_24_to_8_bits_dfa_out_valid_reg0_130q <= wire_lcd_24_to_8_bits_dfa_out_valid_reg0_186m_dataout;
				lcd_24_to_8_bits_dfa_state_register_0_128q <= wire_lcd_24_to_8_bits_dfa_mux11_110_o;
				lcd_24_to_8_bits_dfa_state_register_1_61q <= wire_lcd_24_to_8_bits_dfa_mux10_109_o;
		END IF;
	END PROCESS;
	wire_nl_w_lg_lcd_24_to_8_bits_dfa_out_valid_reg0_130q60w(0) <= NOT lcd_24_to_8_bits_dfa_out_valid_reg0_130q;
	PROCESS (clk, reset_n)
	BEGIN
		IF (reset_n = '0') THEN
				lcd_24_to_8_bits_dfa_a_data0_0_40q <= '0';
				lcd_24_to_8_bits_dfa_a_data0_1_39q <= '0';
				lcd_24_to_8_bits_dfa_a_data0_2_38q <= '0';
				lcd_24_to_8_bits_dfa_a_data0_3_37q <= '0';
				lcd_24_to_8_bits_dfa_a_data0_4_36q <= '0';
				lcd_24_to_8_bits_dfa_a_data0_5_35q <= '0';
				lcd_24_to_8_bits_dfa_a_data0_6_34q <= '0';
				lcd_24_to_8_bits_dfa_a_data0_7_33q <= '0';
				lcd_24_to_8_bits_dfa_a_data1_0_48q <= '0';
				lcd_24_to_8_bits_dfa_a_data1_1_47q <= '0';
				lcd_24_to_8_bits_dfa_a_data1_2_46q <= '0';
				lcd_24_to_8_bits_dfa_a_data1_3_45q <= '0';
				lcd_24_to_8_bits_dfa_a_data1_4_44q <= '0';
				lcd_24_to_8_bits_dfa_a_data1_5_43q <= '0';
				lcd_24_to_8_bits_dfa_a_data1_6_42q <= '0';
				lcd_24_to_8_bits_dfa_a_data1_7_41q <= '0';
				lcd_24_to_8_bits_dfa_a_data2_0_56q <= '0';
				lcd_24_to_8_bits_dfa_a_data2_1_55q <= '0';
				lcd_24_to_8_bits_dfa_a_data2_2_54q <= '0';
				lcd_24_to_8_bits_dfa_a_data2_3_53q <= '0';
				lcd_24_to_8_bits_dfa_a_data2_4_52q <= '0';
				lcd_24_to_8_bits_dfa_a_data2_5_51q <= '0';
				lcd_24_to_8_bits_dfa_a_data2_6_50q <= '0';
				lcd_24_to_8_bits_dfa_a_data2_7_49q <= '0';
				lcd_24_to_8_bits_dfa_a_empty_0_60q <= '0';
				lcd_24_to_8_bits_dfa_a_empty_1_59q <= '0';
				lcd_24_to_8_bits_dfa_a_endofpacket_58q <= '0';
				lcd_24_to_8_bits_dfa_a_startofpacket_57q <= '0';
				lcd_24_to_8_bits_dfa_a_valid_32q <= '0';
		ELSIF (clk = '1' AND clk'event) THEN
			IF (s_wire_lcd_24_to_8_bits_dfa_in_ready_114_dataout = '1') THEN
				lcd_24_to_8_bits_dfa_a_data0_0_40q <= in_data(16);
				lcd_24_to_8_bits_dfa_a_data0_1_39q <= in_data(17);
				lcd_24_to_8_bits_dfa_a_data0_2_38q <= in_data(18);
				lcd_24_to_8_bits_dfa_a_data0_3_37q <= in_data(19);
				lcd_24_to_8_bits_dfa_a_data0_4_36q <= in_data(20);
				lcd_24_to_8_bits_dfa_a_data0_5_35q <= in_data(21);
				lcd_24_to_8_bits_dfa_a_data0_6_34q <= in_data(22);
				lcd_24_to_8_bits_dfa_a_data0_7_33q <= in_data(23);
				lcd_24_to_8_bits_dfa_a_data1_0_48q <= in_data(8);
				lcd_24_to_8_bits_dfa_a_data1_1_47q <= in_data(9);
				lcd_24_to_8_bits_dfa_a_data1_2_46q <= in_data(10);
				lcd_24_to_8_bits_dfa_a_data1_3_45q <= in_data(11);
				lcd_24_to_8_bits_dfa_a_data1_4_44q <= in_data(12);
				lcd_24_to_8_bits_dfa_a_data1_5_43q <= in_data(13);
				lcd_24_to_8_bits_dfa_a_data1_6_42q <= in_data(14);
				lcd_24_to_8_bits_dfa_a_data1_7_41q <= in_data(15);
				lcd_24_to_8_bits_dfa_a_data2_0_56q <= in_data(0);
				lcd_24_to_8_bits_dfa_a_data2_1_55q <= in_data(1);
				lcd_24_to_8_bits_dfa_a_data2_2_54q <= in_data(2);
				lcd_24_to_8_bits_dfa_a_data2_3_53q <= in_data(3);
				lcd_24_to_8_bits_dfa_a_data2_4_52q <= in_data(4);
				lcd_24_to_8_bits_dfa_a_data2_5_51q <= in_data(5);
				lcd_24_to_8_bits_dfa_a_data2_6_50q <= in_data(6);
				lcd_24_to_8_bits_dfa_a_data2_7_49q <= in_data(7);
				lcd_24_to_8_bits_dfa_a_empty_0_60q <= wire_lcd_24_to_8_bits_dfa_a_empty_2m_dataout;
				lcd_24_to_8_bits_dfa_a_empty_1_59q <= wire_lcd_24_to_8_bits_dfa_a_empty_1m_dataout;
				lcd_24_to_8_bits_dfa_a_endofpacket_58q <= in_endofpacket;
				lcd_24_to_8_bits_dfa_a_startofpacket_57q <= in_startofpacket;
				lcd_24_to_8_bits_dfa_a_valid_32q <= in_valid;
			END IF;
		END IF;
	END PROCESS;
	wire_nO_w_lg_lcd_24_to_8_bits_dfa_a_valid_32q199w(0) <= NOT lcd_24_to_8_bits_dfa_a_valid_32q;
	wire_lcd_24_to_8_bits_dfa_a_empty_1m_dataout <= in_empty(1) AND in_endofpacket;
	wire_lcd_24_to_8_bits_dfa_a_empty_2m_dataout <= in_empty(0) AND in_endofpacket;
	wire_lcd_24_to_8_bits_dfa_a_ready_69m_dataout <= s_wire_lcd_24_to_8_bits_dfa_always4_64_dataout AND lcd_24_to_8_bits_dfa_a_valid_32q;
	wire_lcd_24_to_8_bits_dfa_a_ready_72m_dataout <= wire_lcd_24_to_8_bits_dfa_a_ready_69m_dataout AND s_wire_lcd_24_to_8_bits_dfa_always4_84_dataout;
	wire_lcd_24_to_8_bits_dfa_a_ready_79m_dataout <= s_wire_lcd_24_to_8_bits_dfa_always4_74_dataout AND lcd_24_to_8_bits_dfa_a_valid_32q;
	wire_lcd_24_to_8_bits_dfa_a_ready_82m_dataout <= wire_lcd_24_to_8_bits_dfa_a_ready_79m_dataout AND s_wire_lcd_24_to_8_bits_dfa_always4_84_dataout;
	wire_lcd_24_to_8_bits_dfa_b_empty_65m_dataout <= lcd_24_to_8_bits_dfa_a_empty_0_60q AND s_wire_lcd_24_to_8_bits_dfa_always4_64_dataout;
	wire_lcd_24_to_8_bits_dfa_b_empty_68m_dataout <= wire_lcd_24_to_8_bits_dfa_b_empty_65m_dataout AND lcd_24_to_8_bits_dfa_a_valid_32q;
	wire_lcd_24_to_8_bits_dfa_b_empty_71m_dataout <= wire_lcd_24_to_8_bits_dfa_b_empty_68m_dataout AND s_wire_lcd_24_to_8_bits_dfa_always4_84_dataout;
	wire_lcd_24_to_8_bits_dfa_b_empty_76m_dataout <= wire_lcd_24_to_8_bits_dfa_add0_75_o(1) AND s_wire_lcd_24_to_8_bits_dfa_always4_74_dataout;
	wire_lcd_24_to_8_bits_dfa_b_empty_78m_dataout <= wire_lcd_24_to_8_bits_dfa_b_empty_76m_dataout AND lcd_24_to_8_bits_dfa_a_valid_32q;
	wire_lcd_24_to_8_bits_dfa_b_empty_81m_dataout <= wire_lcd_24_to_8_bits_dfa_b_empty_78m_dataout AND s_wire_lcd_24_to_8_bits_dfa_always4_84_dataout;
	wire_lcd_24_to_8_bits_dfa_b_empty_87m_dataout <= lcd_24_to_8_bits_dfa_a_empty_0_60q AND s_wire_lcd_24_to_8_bits_dfa_always4_86_dataout;
	wire_lcd_24_to_8_bits_dfa_b_empty_90m_dataout <= wire_lcd_24_to_8_bits_dfa_b_empty_87m_dataout AND lcd_24_to_8_bits_dfa_a_valid_32q;
	wire_lcd_24_to_8_bits_dfa_b_empty_95m_dataout <= wire_lcd_24_to_8_bits_dfa_b_empty_90m_dataout AND s_wire_lcd_24_to_8_bits_dfa_always4_84_dataout;
	wire_lcd_24_to_8_bits_dfa_b_endofpacket_91m_dataout <= s_wire_lcd_24_to_8_bits_dfa_always4_86_dataout AND lcd_24_to_8_bits_dfa_a_valid_32q;
	wire_lcd_24_to_8_bits_dfa_b_endofpacket_96m_dataout <= wire_lcd_24_to_8_bits_dfa_b_endofpacket_91m_dataout AND s_wire_lcd_24_to_8_bits_dfa_always4_84_dataout;
	wire_lcd_24_to_8_bits_dfa_b_startofpacket_106m_dataout <= lcd_24_to_8_bits_dfa_a_startofpacket_57q AND wire_lcd_24_to_8_bits_dfa_decoder0_105_o(0);
	wire_lcd_24_to_8_bits_dfa_b_valid_92m_dataout <= lcd_24_to_8_bits_dfa_a_valid_32q AND s_wire_lcd_24_to_8_bits_dfa_always4_84_dataout;
	wire_lcd_24_to_8_bits_dfa_new_state_67m_dataout <= wire_w36w(0) WHEN lcd_24_to_8_bits_dfa_a_valid_32q = '1'  ELSE lcd_24_to_8_bits_dfa_state_register_0_128q;
	wire_lcd_24_to_8_bits_dfa_new_state_70m_dataout <= wire_lcd_24_to_8_bits_dfa_new_state_67m_dataout WHEN s_wire_lcd_24_to_8_bits_dfa_always4_84_dataout = '1'  ELSE lcd_24_to_8_bits_dfa_state_register_0_128q;
	wire_lcd_24_to_8_bits_dfa_new_state_77m_dataout <= wire_w59w(0) WHEN lcd_24_to_8_bits_dfa_a_valid_32q = '1'  ELSE lcd_24_to_8_bits_dfa_state_register_1_61q;
	wire_lcd_24_to_8_bits_dfa_new_state_80m_dataout <= wire_lcd_24_to_8_bits_dfa_new_state_77m_dataout WHEN s_wire_lcd_24_to_8_bits_dfa_always4_84_dataout = '1'  ELSE lcd_24_to_8_bits_dfa_state_register_1_61q;
	wire_lcd_24_to_8_bits_dfa_new_state_88m_dataout <= lcd_24_to_8_bits_dfa_state_register_1_61q AND NOT(lcd_24_to_8_bits_dfa_a_valid_32q);
	wire_lcd_24_to_8_bits_dfa_new_state_89m_dataout <= lcd_24_to_8_bits_dfa_state_register_0_128q AND NOT(lcd_24_to_8_bits_dfa_a_valid_32q);
	wire_lcd_24_to_8_bits_dfa_new_state_93m_dataout <= wire_lcd_24_to_8_bits_dfa_new_state_88m_dataout WHEN s_wire_lcd_24_to_8_bits_dfa_always4_84_dataout = '1'  ELSE lcd_24_to_8_bits_dfa_state_register_1_61q;
	wire_lcd_24_to_8_bits_dfa_new_state_94m_dataout <= wire_lcd_24_to_8_bits_dfa_new_state_89m_dataout WHEN s_wire_lcd_24_to_8_bits_dfa_always4_84_dataout = '1'  ELSE lcd_24_to_8_bits_dfa_state_register_0_128q;
	wire_lcd_24_to_8_bits_dfa_out_valid_reg0_186m_dataout <= wire_lcd_24_to_8_bits_dfa_mux9_108_o WHEN s_wire_lcd_24_to_8_bits_dfa_always4_84_dataout = '1'  ELSE lcd_24_to_8_bits_dfa_out_valid_reg0_130q;
	wire_lcd_24_to_8_bits_dfa_add0_75_a <= ( lcd_24_to_8_bits_dfa_a_empty_1_59q & lcd_24_to_8_bits_dfa_a_empty_0_60q & "1");
	wire_lcd_24_to_8_bits_dfa_add0_75_b <= ( "1" & "0" & "1");
	lcd_24_to_8_bits_dfa_add0_75 :  oper_add
	  GENERIC MAP (
		sgate_representation => 0,
		width_a => 3,
		width_b => 3,
		width_o => 3
	  )
	  PORT MAP ( 
		a => wire_lcd_24_to_8_bits_dfa_add0_75_a,
		b => wire_lcd_24_to_8_bits_dfa_add0_75_b,
		cin => wire_gnd,
		o => wire_lcd_24_to_8_bits_dfa_add0_75_o
	  );
	wire_lcd_24_to_8_bits_dfa_decoder0_105_i <= ( lcd_24_to_8_bits_dfa_state_register_1_61q & lcd_24_to_8_bits_dfa_state_register_0_128q);
	lcd_24_to_8_bits_dfa_decoder0_105 :  oper_decoder
	  GENERIC MAP (
		width_i => 2,
		width_o => 4
	  )
	  PORT MAP ( 
		i => wire_lcd_24_to_8_bits_dfa_decoder0_105_i,
		o => wire_lcd_24_to_8_bits_dfa_decoder0_105_o
	  );
	wire_lcd_24_to_8_bits_dfa_lessthan0_63_a <= ( "1" & "0");
	wire_lcd_24_to_8_bits_dfa_lessthan0_63_b <= ( lcd_24_to_8_bits_dfa_a_empty_1_59q & lcd_24_to_8_bits_dfa_a_empty_0_60q);
	lcd_24_to_8_bits_dfa_lessthan0_63 :  oper_less_than
	  GENERIC MAP (
		sgate_representation => 0,
		width_a => 2,
		width_b => 2
	  )
	  PORT MAP ( 
		a => wire_lcd_24_to_8_bits_dfa_lessthan0_63_a,
		b => wire_lcd_24_to_8_bits_dfa_lessthan0_63_b,
		cin => wire_vcc,
		o => wire_lcd_24_to_8_bits_dfa_lessthan0_63_o
	  );
	wire_lcd_24_to_8_bits_dfa_lessthan1_73_a <= ( "0" & "1");
	wire_lcd_24_to_8_bits_dfa_lessthan1_73_b <= ( lcd_24_to_8_bits_dfa_a_empty_1_59q & lcd_24_to_8_bits_dfa_a_empty_0_60q);
	lcd_24_to_8_bits_dfa_lessthan1_73 :  oper_less_than
	  GENERIC MAP (
		sgate_representation => 0,
		width_a => 2,
		width_b => 2
	  )
	  PORT MAP ( 
		a => wire_lcd_24_to_8_bits_dfa_lessthan1_73_a,
		b => wire_lcd_24_to_8_bits_dfa_lessthan1_73_b,
		cin => wire_vcc,
		o => wire_lcd_24_to_8_bits_dfa_lessthan1_73_o
	  );
	wire_lcd_24_to_8_bits_dfa_lessthan2_85_a <= ( "0" & "0");
	wire_lcd_24_to_8_bits_dfa_lessthan2_85_b <= ( lcd_24_to_8_bits_dfa_a_empty_1_59q & lcd_24_to_8_bits_dfa_a_empty_0_60q);
	lcd_24_to_8_bits_dfa_lessthan2_85 :  oper_less_than
	  GENERIC MAP (
		sgate_representation => 0,
		width_a => 2,
		width_b => 2
	  )
	  PORT MAP ( 
		a => wire_lcd_24_to_8_bits_dfa_lessthan2_85_a,
		b => wire_lcd_24_to_8_bits_dfa_lessthan2_85_b,
		cin => wire_vcc,
		o => wire_lcd_24_to_8_bits_dfa_lessthan2_85_o
	  );
	wire_lcd_24_to_8_bits_dfa_mux0_97_data <= ( "0" & lcd_24_to_8_bits_dfa_a_data2_7_49q & lcd_24_to_8_bits_dfa_a_data1_7_41q & lcd_24_to_8_bits_dfa_a_data0_7_33q);
	wire_lcd_24_to_8_bits_dfa_mux0_97_sel <= ( lcd_24_to_8_bits_dfa_state_register_1_61q & lcd_24_to_8_bits_dfa_state_register_0_128q);
	lcd_24_to_8_bits_dfa_mux0_97 :  oper_mux
	  GENERIC MAP (
		width_data => 4,
		width_sel => 2
	  )
	  PORT MAP ( 
		data => wire_lcd_24_to_8_bits_dfa_mux0_97_data,
		o => wire_lcd_24_to_8_bits_dfa_mux0_97_o,
		sel => wire_lcd_24_to_8_bits_dfa_mux0_97_sel
	  );
	wire_lcd_24_to_8_bits_dfa_mux10_109_data <= ( lcd_24_to_8_bits_dfa_state_register_1_61q & wire_lcd_24_to_8_bits_dfa_new_state_93m_dataout & wire_lcd_24_to_8_bits_dfa_new_state_80m_dataout & wire_lcd_24_to_8_bits_dfa_new_state_93m_dataout);
	wire_lcd_24_to_8_bits_dfa_mux10_109_sel <= ( lcd_24_to_8_bits_dfa_state_register_1_61q & lcd_24_to_8_bits_dfa_state_register_0_128q);
	lcd_24_to_8_bits_dfa_mux10_109 :  oper_mux
	  GENERIC MAP (
		width_data => 4,
		width_sel => 2
	  )
	  PORT MAP ( 
		data => wire_lcd_24_to_8_bits_dfa_mux10_109_data,
		o => wire_lcd_24_to_8_bits_dfa_mux10_109_o,
		sel => wire_lcd_24_to_8_bits_dfa_mux10_109_sel
	  );
	wire_lcd_24_to_8_bits_dfa_mux11_110_data <= ( lcd_24_to_8_bits_dfa_state_register_0_128q & wire_lcd_24_to_8_bits_dfa_new_state_94m_dataout & wire_lcd_24_to_8_bits_dfa_new_state_94m_dataout & wire_lcd_24_to_8_bits_dfa_new_state_70m_dataout);
	wire_lcd_24_to_8_bits_dfa_mux11_110_sel <= ( lcd_24_to_8_bits_dfa_state_register_1_61q & lcd_24_to_8_bits_dfa_state_register_0_128q);
	lcd_24_to_8_bits_dfa_mux11_110 :  oper_mux
	  GENERIC MAP (
		width_data => 4,
		width_sel => 2
	  )
	  PORT MAP ( 
		data => wire_lcd_24_to_8_bits_dfa_mux11_110_data,
		o => wire_lcd_24_to_8_bits_dfa_mux11_110_o,
		sel => wire_lcd_24_to_8_bits_dfa_mux11_110_sel
	  );
	wire_lcd_24_to_8_bits_dfa_mux12_111_data <= ( "0" & wire_lcd_24_to_8_bits_dfa_b_empty_95m_dataout & wire_lcd_24_to_8_bits_dfa_b_empty_81m_dataout & wire_lcd_24_to_8_bits_dfa_b_empty_71m_dataout);
	wire_lcd_24_to_8_bits_dfa_mux12_111_sel <= ( lcd_24_to_8_bits_dfa_state_register_1_61q & lcd_24_to_8_bits_dfa_state_register_0_128q);
	lcd_24_to_8_bits_dfa_mux12_111 :  oper_mux
	  GENERIC MAP (
		width_data => 4,
		width_sel => 2
	  )
	  PORT MAP ( 
		data => wire_lcd_24_to_8_bits_dfa_mux12_111_data,
		o => wire_lcd_24_to_8_bits_dfa_mux12_111_o,
		sel => wire_lcd_24_to_8_bits_dfa_mux12_111_sel
	  );
	wire_lcd_24_to_8_bits_dfa_mux13_112_data <= ( "0" & wire_lcd_24_to_8_bits_dfa_b_endofpacket_96m_dataout & wire_lcd_24_to_8_bits_dfa_a_ready_82m_dataout & wire_lcd_24_to_8_bits_dfa_a_ready_72m_dataout);
	wire_lcd_24_to_8_bits_dfa_mux13_112_sel <= ( lcd_24_to_8_bits_dfa_state_register_1_61q & lcd_24_to_8_bits_dfa_state_register_0_128q);
	lcd_24_to_8_bits_dfa_mux13_112 :  oper_mux
	  GENERIC MAP (
		width_data => 4,
		width_sel => 2
	  )
	  PORT MAP ( 
		data => wire_lcd_24_to_8_bits_dfa_mux13_112_data,
		o => wire_lcd_24_to_8_bits_dfa_mux13_112_o,
		sel => wire_lcd_24_to_8_bits_dfa_mux13_112_sel
	  );
	wire_lcd_24_to_8_bits_dfa_mux1_98_data <= ( "0" & lcd_24_to_8_bits_dfa_a_data2_6_50q & lcd_24_to_8_bits_dfa_a_data1_6_42q & lcd_24_to_8_bits_dfa_a_data0_6_34q);
	wire_lcd_24_to_8_bits_dfa_mux1_98_sel <= ( lcd_24_to_8_bits_dfa_state_register_1_61q & lcd_24_to_8_bits_dfa_state_register_0_128q);
	lcd_24_to_8_bits_dfa_mux1_98 :  oper_mux
	  GENERIC MAP (
		width_data => 4,
		width_sel => 2
	  )
	  PORT MAP ( 
		data => wire_lcd_24_to_8_bits_dfa_mux1_98_data,
		o => wire_lcd_24_to_8_bits_dfa_mux1_98_o,
		sel => wire_lcd_24_to_8_bits_dfa_mux1_98_sel
	  );
	wire_lcd_24_to_8_bits_dfa_mux2_99_data <= ( "0" & lcd_24_to_8_bits_dfa_a_data2_5_51q & lcd_24_to_8_bits_dfa_a_data1_5_43q & lcd_24_to_8_bits_dfa_a_data0_5_35q);
	wire_lcd_24_to_8_bits_dfa_mux2_99_sel <= ( lcd_24_to_8_bits_dfa_state_register_1_61q & lcd_24_to_8_bits_dfa_state_register_0_128q);
	lcd_24_to_8_bits_dfa_mux2_99 :  oper_mux
	  GENERIC MAP (
		width_data => 4,
		width_sel => 2
	  )
	  PORT MAP ( 
		data => wire_lcd_24_to_8_bits_dfa_mux2_99_data,
		o => wire_lcd_24_to_8_bits_dfa_mux2_99_o,
		sel => wire_lcd_24_to_8_bits_dfa_mux2_99_sel
	  );
	wire_lcd_24_to_8_bits_dfa_mux3_100_data <= ( "0" & lcd_24_to_8_bits_dfa_a_data2_4_52q & lcd_24_to_8_bits_dfa_a_data1_4_44q & lcd_24_to_8_bits_dfa_a_data0_4_36q);
	wire_lcd_24_to_8_bits_dfa_mux3_100_sel <= ( lcd_24_to_8_bits_dfa_state_register_1_61q & lcd_24_to_8_bits_dfa_state_register_0_128q);
	lcd_24_to_8_bits_dfa_mux3_100 :  oper_mux
	  GENERIC MAP (
		width_data => 4,
		width_sel => 2
	  )
	  PORT MAP ( 
		data => wire_lcd_24_to_8_bits_dfa_mux3_100_data,
		o => wire_lcd_24_to_8_bits_dfa_mux3_100_o,
		sel => wire_lcd_24_to_8_bits_dfa_mux3_100_sel
	  );
	wire_lcd_24_to_8_bits_dfa_mux4_101_data <= ( "0" & lcd_24_to_8_bits_dfa_a_data2_3_53q & lcd_24_to_8_bits_dfa_a_data1_3_45q & lcd_24_to_8_bits_dfa_a_data0_3_37q);
	wire_lcd_24_to_8_bits_dfa_mux4_101_sel <= ( lcd_24_to_8_bits_dfa_state_register_1_61q & lcd_24_to_8_bits_dfa_state_register_0_128q);
	lcd_24_to_8_bits_dfa_mux4_101 :  oper_mux
	  GENERIC MAP (
		width_data => 4,
		width_sel => 2
	  )
	  PORT MAP ( 
		data => wire_lcd_24_to_8_bits_dfa_mux4_101_data,
		o => wire_lcd_24_to_8_bits_dfa_mux4_101_o,
		sel => wire_lcd_24_to_8_bits_dfa_mux4_101_sel
	  );
	wire_lcd_24_to_8_bits_dfa_mux5_102_data <= ( "0" & lcd_24_to_8_bits_dfa_a_data2_2_54q & lcd_24_to_8_bits_dfa_a_data1_2_46q & lcd_24_to_8_bits_dfa_a_data0_2_38q);
	wire_lcd_24_to_8_bits_dfa_mux5_102_sel <= ( lcd_24_to_8_bits_dfa_state_register_1_61q & lcd_24_to_8_bits_dfa_state_register_0_128q);
	lcd_24_to_8_bits_dfa_mux5_102 :  oper_mux
	  GENERIC MAP (
		width_data => 4,
		width_sel => 2
	  )
	  PORT MAP ( 
		data => wire_lcd_24_to_8_bits_dfa_mux5_102_data,
		o => wire_lcd_24_to_8_bits_dfa_mux5_102_o,
		sel => wire_lcd_24_to_8_bits_dfa_mux5_102_sel
	  );
	wire_lcd_24_to_8_bits_dfa_mux6_103_data <= ( "0" & lcd_24_to_8_bits_dfa_a_data2_1_55q & lcd_24_to_8_bits_dfa_a_data1_1_47q & lcd_24_to_8_bits_dfa_a_data0_1_39q);
	wire_lcd_24_to_8_bits_dfa_mux6_103_sel <= ( lcd_24_to_8_bits_dfa_state_register_1_61q & lcd_24_to_8_bits_dfa_state_register_0_128q);
	lcd_24_to_8_bits_dfa_mux6_103 :  oper_mux
	  GENERIC MAP (
		width_data => 4,
		width_sel => 2
	  )
	  PORT MAP ( 
		data => wire_lcd_24_to_8_bits_dfa_mux6_103_data,
		o => wire_lcd_24_to_8_bits_dfa_mux6_103_o,
		sel => wire_lcd_24_to_8_bits_dfa_mux6_103_sel
	  );
	wire_lcd_24_to_8_bits_dfa_mux7_104_data <= ( "0" & lcd_24_to_8_bits_dfa_a_data2_0_56q & lcd_24_to_8_bits_dfa_a_data1_0_48q & lcd_24_to_8_bits_dfa_a_data0_0_40q);
	wire_lcd_24_to_8_bits_dfa_mux7_104_sel <= ( lcd_24_to_8_bits_dfa_state_register_1_61q & lcd_24_to_8_bits_dfa_state_register_0_128q);
	lcd_24_to_8_bits_dfa_mux7_104 :  oper_mux
	  GENERIC MAP (
		width_data => 4,
		width_sel => 2
	  )
	  PORT MAP ( 
		data => wire_lcd_24_to_8_bits_dfa_mux7_104_data,
		o => wire_lcd_24_to_8_bits_dfa_mux7_104_o,
		sel => wire_lcd_24_to_8_bits_dfa_mux7_104_sel
	  );
	wire_lcd_24_to_8_bits_dfa_mux8_107_data <= ( "0" & s_wire_lcd_24_to_8_bits_dfa_always4_84_dataout & wire_lcd_24_to_8_bits_dfa_a_ready_82m_dataout & wire_lcd_24_to_8_bits_dfa_a_ready_72m_dataout);
	wire_lcd_24_to_8_bits_dfa_mux8_107_sel <= ( lcd_24_to_8_bits_dfa_state_register_1_61q & lcd_24_to_8_bits_dfa_state_register_0_128q);
	lcd_24_to_8_bits_dfa_mux8_107 :  oper_mux
	  GENERIC MAP (
		width_data => 4,
		width_sel => 2
	  )
	  PORT MAP ( 
		data => wire_lcd_24_to_8_bits_dfa_mux8_107_data,
		o => wire_lcd_24_to_8_bits_dfa_mux8_107_o,
		sel => wire_lcd_24_to_8_bits_dfa_mux8_107_sel
	  );
	wire_lcd_24_to_8_bits_dfa_mux9_108_data <= ( "0" & wire_lcd_24_to_8_bits_dfa_b_valid_92m_dataout & wire_lcd_24_to_8_bits_dfa_b_valid_92m_dataout & wire_lcd_24_to_8_bits_dfa_b_valid_92m_dataout);
	wire_lcd_24_to_8_bits_dfa_mux9_108_sel <= ( lcd_24_to_8_bits_dfa_state_register_1_61q & lcd_24_to_8_bits_dfa_state_register_0_128q);
	lcd_24_to_8_bits_dfa_mux9_108 :  oper_mux
	  GENERIC MAP (
		width_data => 4,
		width_sel => 2
	  )
	  PORT MAP ( 
		data => wire_lcd_24_to_8_bits_dfa_mux9_108_data,
		o => wire_lcd_24_to_8_bits_dfa_mux9_108_o,
		sel => wire_lcd_24_to_8_bits_dfa_mux9_108_sel
	  );

 END RTL; --lcd_24_to_8_bits_dfa
--synopsys translate_on
--VALID FILE
