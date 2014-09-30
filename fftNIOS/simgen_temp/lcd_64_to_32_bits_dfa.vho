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

--synthesis_resources = lut 110 mux21 72 oper_decoder 1 oper_less_than 2 oper_mux 7 
 LIBRARY ieee;
 USE ieee.std_logic_1164.all;

 ENTITY  lcd_64_to_32_bits_dfa IS 
	 PORT 
	 ( 
		 clk	:	IN  STD_LOGIC;
		 in_data	:	IN  STD_LOGIC_VECTOR (63 DOWNTO 0);
		 in_empty	:	IN  STD_LOGIC_VECTOR (2 DOWNTO 0);
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
 END lcd_64_to_32_bits_dfa;

 ARCHITECTURE RTL OF lcd_64_to_32_bits_dfa IS

	 ATTRIBUTE synthesis_clearbox : natural;
	 ATTRIBUTE synthesis_clearbox OF RTL : ARCHITECTURE IS 1;
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_0_reg0_305q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_10_reg0_295q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_11_reg0_294q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_12_reg0_293q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_13_reg0_292q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_14_reg0_291q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_15_reg0_290q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_16_reg0_289q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_17_reg0_288q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_18_reg0_287q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_19_reg0_286q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_1_reg0_304q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_20_reg0_285q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_21_reg0_284q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_22_reg0_283q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_23_reg0_282q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_24_reg0_281q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_25_reg0_280q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_26_reg0_279q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_27_reg0_278q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_28_reg0_277q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_29_reg0_276q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_2_reg0_303q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_30_reg0_275q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_31_reg0_274q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_3_reg0_302q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_4_reg0_301q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_5_reg0_300q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_6_reg0_299q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_7_reg0_298q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_8_reg0_297q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_data_9_reg0_296q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_empty_0_reg0_272q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_empty_1_reg0_308q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_endofpacket_reg0_307q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_startofpacket_reg0_306q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_out_valid_reg0_273q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_state_register_0_271q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_state_register_1_145q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_state_register_2_144q	:	STD_LOGIC := '0';
	 SIGNAL  wire_nl_w_lg_lcd_64_to_32_bits_dfa_out_valid_reg0_273q82w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data0_0_82q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data0_1_81q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data0_2_80q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data0_3_79q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data0_4_78q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data0_5_77q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data0_6_76q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data0_7_75q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data1_0_90q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data1_1_89q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data1_2_88q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data1_3_87q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data1_4_86q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data1_5_85q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data1_6_84q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data1_7_83q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data2_0_98q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data2_1_97q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data2_2_96q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data2_3_95q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data2_4_94q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data2_5_93q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data2_6_92q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data2_7_91q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data3_0_106q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data3_1_105q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data3_2_104q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data3_3_103q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data3_4_102q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data3_5_101q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data3_6_100q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data3_7_99q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data4_0_114q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data4_1_113q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data4_2_112q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data4_3_111q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data4_4_110q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data4_5_109q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data4_6_108q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data4_7_107q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data5_0_122q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data5_1_121q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data5_2_120q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data5_3_119q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data5_4_118q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data5_5_117q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data5_6_116q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data5_7_115q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data6_0_130q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data6_1_129q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data6_2_128q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data6_3_127q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data6_4_126q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data6_5_125q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data6_6_124q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data6_7_123q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data7_0_138q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data7_1_137q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data7_2_136q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data7_3_135q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data7_4_134q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data7_5_133q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data7_6_132q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_data7_7_131q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_empty_0_143q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_empty_1_142q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_empty_2_141q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_endofpacket_140q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_startofpacket_139q	:	STD_LOGIC := '0';
	 SIGNAL	lcd_64_to_32_bits_dfa_a_valid_74q	:	STD_LOGIC := '0';
	 SIGNAL  wire_nO_w_lg_lcd_64_to_32_bits_dfa_a_valid_74q199w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_a_empty_1m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_a_empty_2m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_a_empty_3m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_a_ready_163m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_a_ready_169m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_0_222m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_10_212m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_11_211m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_12_210m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_13_209m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_14_208m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_15_207m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_16_206m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_17_205m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_18_204m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_19_203m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_1_221m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_20_202m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_21_201m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_22_200m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_23_199m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_24_198m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_25_197m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_26_196m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_27_195m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_28_194m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_29_193m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_2_220m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_30_192m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_31_191m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_3_219m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_4_218m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_5_217m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_6_216m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_7_215m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_8_214m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_data_9_213m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_empty_156m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_empty_157m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_empty_161m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_empty_162m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_empty_167m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_empty_168m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_empty_174m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_empty_175m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_empty_179m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_empty_180m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_empty_186m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_empty_187m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_endofpacket_149m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_endofpacket_153m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_endofpacket_181m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_endofpacket_188m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_startofpacket_223m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_b_valid_182m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_new_state_147m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_new_state_148m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_new_state_151m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_new_state_152m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_new_state_158m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_new_state_159m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_new_state_160m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_new_state_164m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_new_state_165m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_new_state_166m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_new_state_176m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_new_state_177m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_new_state_178m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_new_state_183m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_new_state_184m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_new_state_185m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_lcd_64_to_32_bits_dfa_out_valid_reg0_420m_dataout	:	STD_LOGIC;
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_decoder0_189_i	:	STD_LOGIC_VECTOR (2 DOWNTO 0);
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_decoder0_189_o	:	STD_LOGIC_VECTOR (7 DOWNTO 0);
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_lessthan0_154_a	:	STD_LOGIC_VECTOR (2 DOWNTO 0);
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_lessthan0_154_b	:	STD_LOGIC_VECTOR (2 DOWNTO 0);
	 SIGNAL  wire_vcc	:	STD_LOGIC;
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_lessthan0_154_o	:	STD_LOGIC;
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_lessthan1_172_a	:	STD_LOGIC_VECTOR (2 DOWNTO 0);
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_lessthan1_172_b	:	STD_LOGIC_VECTOR (2 DOWNTO 0);
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_lessthan1_172_o	:	STD_LOGIC;
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_mux0_224_data	:	STD_LOGIC_VECTOR (7 DOWNTO 0);
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_mux0_224_o	:	STD_LOGIC;
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_mux0_224_sel	:	STD_LOGIC_VECTOR (2 DOWNTO 0);
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_mux1_225_data	:	STD_LOGIC_VECTOR (7 DOWNTO 0);
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_mux1_225_o	:	STD_LOGIC;
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_mux1_225_sel	:	STD_LOGIC_VECTOR (2 DOWNTO 0);
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_mux2_226_data	:	STD_LOGIC_VECTOR (7 DOWNTO 0);
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_mux2_226_o	:	STD_LOGIC;
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_mux2_226_sel	:	STD_LOGIC_VECTOR (2 DOWNTO 0);
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_mux3_227_data	:	STD_LOGIC_VECTOR (7 DOWNTO 0);
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_mux3_227_o	:	STD_LOGIC;
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_mux3_227_sel	:	STD_LOGIC_VECTOR (2 DOWNTO 0);
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_mux4_228_data	:	STD_LOGIC_VECTOR (7 DOWNTO 0);
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_mux4_228_o	:	STD_LOGIC;
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_mux4_228_sel	:	STD_LOGIC_VECTOR (2 DOWNTO 0);
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_mux5_229_data	:	STD_LOGIC_VECTOR (7 DOWNTO 0);
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_mux5_229_o	:	STD_LOGIC;
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_mux5_229_sel	:	STD_LOGIC_VECTOR (2 DOWNTO 0);
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_mux6_230_data	:	STD_LOGIC_VECTOR (7 DOWNTO 0);
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_mux6_230_o	:	STD_LOGIC;
	 SIGNAL  wire_lcd_64_to_32_bits_dfa_mux6_230_sel	:	STD_LOGIC_VECTOR (2 DOWNTO 0);
	 SIGNAL  wire_w81w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w68w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  s_wire_lcd_64_to_32_bits_dfa_always4_155_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_lcd_64_to_32_bits_dfa_always4_171_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_lcd_64_to_32_bits_dfa_always4_173_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_lcd_64_to_32_bits_dfa_in_ready_232_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_vcc :	STD_LOGIC;
 BEGIN

	wire_vcc <= '1';
	wire_w81w(0) <= NOT s_wire_lcd_64_to_32_bits_dfa_always4_155_dataout;
	wire_w68w(0) <= NOT s_wire_lcd_64_to_32_bits_dfa_always4_173_dataout;
	in_ready <= s_wire_lcd_64_to_32_bits_dfa_in_ready_232_dataout;
	out_data <= ( lcd_64_to_32_bits_dfa_out_data_31_reg0_274q & lcd_64_to_32_bits_dfa_out_data_30_reg0_275q & lcd_64_to_32_bits_dfa_out_data_29_reg0_276q & lcd_64_to_32_bits_dfa_out_data_28_reg0_277q & lcd_64_to_32_bits_dfa_out_data_27_reg0_278q & lcd_64_to_32_bits_dfa_out_data_26_reg0_279q & lcd_64_to_32_bits_dfa_out_data_25_reg0_280q & lcd_64_to_32_bits_dfa_out_data_24_reg0_281q & lcd_64_to_32_bits_dfa_out_data_23_reg0_282q & lcd_64_to_32_bits_dfa_out_data_22_reg0_283q & lcd_64_to_32_bits_dfa_out_data_21_reg0_284q & lcd_64_to_32_bits_dfa_out_data_20_reg0_285q & lcd_64_to_32_bits_dfa_out_data_19_reg0_286q & lcd_64_to_32_bits_dfa_out_data_18_reg0_287q & lcd_64_to_32_bits_dfa_out_data_17_reg0_288q & lcd_64_to_32_bits_dfa_out_data_16_reg0_289q & lcd_64_to_32_bits_dfa_out_data_15_reg0_290q & lcd_64_to_32_bits_dfa_out_data_14_reg0_291q & lcd_64_to_32_bits_dfa_out_data_13_reg0_292q & lcd_64_to_32_bits_dfa_out_data_12_reg0_293q & lcd_64_to_32_bits_dfa_out_data_11_reg0_294q & lcd_64_to_32_bits_dfa_out_data_10_reg0_295q & lcd_64_to_32_bits_dfa_out_data_9_reg0_296q & lcd_64_to_32_bits_dfa_out_data_8_reg0_297q & lcd_64_to_32_bits_dfa_out_data_7_reg0_298q & lcd_64_to_32_bits_dfa_out_data_6_reg0_299q & lcd_64_to_32_bits_dfa_out_data_5_reg0_300q & lcd_64_to_32_bits_dfa_out_data_4_reg0_301q & lcd_64_to_32_bits_dfa_out_data_3_reg0_302q & lcd_64_to_32_bits_dfa_out_data_2_reg0_303q & lcd_64_to_32_bits_dfa_out_data_1_reg0_304q & lcd_64_to_32_bits_dfa_out_data_0_reg0_305q);
	out_empty <= ( lcd_64_to_32_bits_dfa_out_empty_1_reg0_308q & lcd_64_to_32_bits_dfa_out_empty_0_reg0_272q);
	out_endofpacket <= lcd_64_to_32_bits_dfa_out_endofpacket_reg0_307q;
	out_startofpacket <= lcd_64_to_32_bits_dfa_out_startofpacket_reg0_306q;
	out_valid <= lcd_64_to_32_bits_dfa_out_valid_reg0_273q;
	s_wire_lcd_64_to_32_bits_dfa_always4_155_dataout <= (lcd_64_to_32_bits_dfa_a_endofpacket_140q AND wire_lcd_64_to_32_bits_dfa_lessthan0_154_o);
	s_wire_lcd_64_to_32_bits_dfa_always4_171_dataout <= (wire_nl_w_lg_lcd_64_to_32_bits_dfa_out_valid_reg0_273q82w(0) OR out_ready);
	s_wire_lcd_64_to_32_bits_dfa_always4_173_dataout <= (lcd_64_to_32_bits_dfa_a_endofpacket_140q AND wire_lcd_64_to_32_bits_dfa_lessthan1_172_o);
	s_wire_lcd_64_to_32_bits_dfa_in_ready_232_dataout <= (wire_nO_w_lg_lcd_64_to_32_bits_dfa_a_valid_74q199w(0) OR wire_lcd_64_to_32_bits_dfa_mux0_224_o);
	s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout <= (((wire_lcd_64_to_32_bits_dfa_decoder0_189_o(7) OR wire_lcd_64_to_32_bits_dfa_decoder0_189_o(5)) OR wire_lcd_64_to_32_bits_dfa_decoder0_189_o(3)) OR wire_lcd_64_to_32_bits_dfa_decoder0_189_o(1));
	s_wire_vcc <= '1';
	PROCESS (clk, reset_n)
	BEGIN
		IF (reset_n = '0') THEN
				lcd_64_to_32_bits_dfa_out_data_0_reg0_305q <= '0';
				lcd_64_to_32_bits_dfa_out_data_10_reg0_295q <= '0';
				lcd_64_to_32_bits_dfa_out_data_11_reg0_294q <= '0';
				lcd_64_to_32_bits_dfa_out_data_12_reg0_293q <= '0';
				lcd_64_to_32_bits_dfa_out_data_13_reg0_292q <= '0';
				lcd_64_to_32_bits_dfa_out_data_14_reg0_291q <= '0';
				lcd_64_to_32_bits_dfa_out_data_15_reg0_290q <= '0';
				lcd_64_to_32_bits_dfa_out_data_16_reg0_289q <= '0';
				lcd_64_to_32_bits_dfa_out_data_17_reg0_288q <= '0';
				lcd_64_to_32_bits_dfa_out_data_18_reg0_287q <= '0';
				lcd_64_to_32_bits_dfa_out_data_19_reg0_286q <= '0';
				lcd_64_to_32_bits_dfa_out_data_1_reg0_304q <= '0';
				lcd_64_to_32_bits_dfa_out_data_20_reg0_285q <= '0';
				lcd_64_to_32_bits_dfa_out_data_21_reg0_284q <= '0';
				lcd_64_to_32_bits_dfa_out_data_22_reg0_283q <= '0';
				lcd_64_to_32_bits_dfa_out_data_23_reg0_282q <= '0';
				lcd_64_to_32_bits_dfa_out_data_24_reg0_281q <= '0';
				lcd_64_to_32_bits_dfa_out_data_25_reg0_280q <= '0';
				lcd_64_to_32_bits_dfa_out_data_26_reg0_279q <= '0';
				lcd_64_to_32_bits_dfa_out_data_27_reg0_278q <= '0';
				lcd_64_to_32_bits_dfa_out_data_28_reg0_277q <= '0';
				lcd_64_to_32_bits_dfa_out_data_29_reg0_276q <= '0';
				lcd_64_to_32_bits_dfa_out_data_2_reg0_303q <= '0';
				lcd_64_to_32_bits_dfa_out_data_30_reg0_275q <= '0';
				lcd_64_to_32_bits_dfa_out_data_31_reg0_274q <= '0';
				lcd_64_to_32_bits_dfa_out_data_3_reg0_302q <= '0';
				lcd_64_to_32_bits_dfa_out_data_4_reg0_301q <= '0';
				lcd_64_to_32_bits_dfa_out_data_5_reg0_300q <= '0';
				lcd_64_to_32_bits_dfa_out_data_6_reg0_299q <= '0';
				lcd_64_to_32_bits_dfa_out_data_7_reg0_298q <= '0';
				lcd_64_to_32_bits_dfa_out_data_8_reg0_297q <= '0';
				lcd_64_to_32_bits_dfa_out_data_9_reg0_296q <= '0';
				lcd_64_to_32_bits_dfa_out_empty_0_reg0_272q <= '0';
				lcd_64_to_32_bits_dfa_out_empty_1_reg0_308q <= '0';
				lcd_64_to_32_bits_dfa_out_endofpacket_reg0_307q <= '0';
				lcd_64_to_32_bits_dfa_out_startofpacket_reg0_306q <= '0';
		ELSIF (clk = '1' AND clk'event) THEN
			IF (s_wire_lcd_64_to_32_bits_dfa_always4_171_dataout = '1') THEN
				lcd_64_to_32_bits_dfa_out_data_0_reg0_305q <= wire_lcd_64_to_32_bits_dfa_b_data_0_222m_dataout;
				lcd_64_to_32_bits_dfa_out_data_10_reg0_295q <= wire_lcd_64_to_32_bits_dfa_b_data_10_212m_dataout;
				lcd_64_to_32_bits_dfa_out_data_11_reg0_294q <= wire_lcd_64_to_32_bits_dfa_b_data_11_211m_dataout;
				lcd_64_to_32_bits_dfa_out_data_12_reg0_293q <= wire_lcd_64_to_32_bits_dfa_b_data_12_210m_dataout;
				lcd_64_to_32_bits_dfa_out_data_13_reg0_292q <= wire_lcd_64_to_32_bits_dfa_b_data_13_209m_dataout;
				lcd_64_to_32_bits_dfa_out_data_14_reg0_291q <= wire_lcd_64_to_32_bits_dfa_b_data_14_208m_dataout;
				lcd_64_to_32_bits_dfa_out_data_15_reg0_290q <= wire_lcd_64_to_32_bits_dfa_b_data_15_207m_dataout;
				lcd_64_to_32_bits_dfa_out_data_16_reg0_289q <= wire_lcd_64_to_32_bits_dfa_b_data_16_206m_dataout;
				lcd_64_to_32_bits_dfa_out_data_17_reg0_288q <= wire_lcd_64_to_32_bits_dfa_b_data_17_205m_dataout;
				lcd_64_to_32_bits_dfa_out_data_18_reg0_287q <= wire_lcd_64_to_32_bits_dfa_b_data_18_204m_dataout;
				lcd_64_to_32_bits_dfa_out_data_19_reg0_286q <= wire_lcd_64_to_32_bits_dfa_b_data_19_203m_dataout;
				lcd_64_to_32_bits_dfa_out_data_1_reg0_304q <= wire_lcd_64_to_32_bits_dfa_b_data_1_221m_dataout;
				lcd_64_to_32_bits_dfa_out_data_20_reg0_285q <= wire_lcd_64_to_32_bits_dfa_b_data_20_202m_dataout;
				lcd_64_to_32_bits_dfa_out_data_21_reg0_284q <= wire_lcd_64_to_32_bits_dfa_b_data_21_201m_dataout;
				lcd_64_to_32_bits_dfa_out_data_22_reg0_283q <= wire_lcd_64_to_32_bits_dfa_b_data_22_200m_dataout;
				lcd_64_to_32_bits_dfa_out_data_23_reg0_282q <= wire_lcd_64_to_32_bits_dfa_b_data_23_199m_dataout;
				lcd_64_to_32_bits_dfa_out_data_24_reg0_281q <= wire_lcd_64_to_32_bits_dfa_b_data_24_198m_dataout;
				lcd_64_to_32_bits_dfa_out_data_25_reg0_280q <= wire_lcd_64_to_32_bits_dfa_b_data_25_197m_dataout;
				lcd_64_to_32_bits_dfa_out_data_26_reg0_279q <= wire_lcd_64_to_32_bits_dfa_b_data_26_196m_dataout;
				lcd_64_to_32_bits_dfa_out_data_27_reg0_278q <= wire_lcd_64_to_32_bits_dfa_b_data_27_195m_dataout;
				lcd_64_to_32_bits_dfa_out_data_28_reg0_277q <= wire_lcd_64_to_32_bits_dfa_b_data_28_194m_dataout;
				lcd_64_to_32_bits_dfa_out_data_29_reg0_276q <= wire_lcd_64_to_32_bits_dfa_b_data_29_193m_dataout;
				lcd_64_to_32_bits_dfa_out_data_2_reg0_303q <= wire_lcd_64_to_32_bits_dfa_b_data_2_220m_dataout;
				lcd_64_to_32_bits_dfa_out_data_30_reg0_275q <= wire_lcd_64_to_32_bits_dfa_b_data_30_192m_dataout;
				lcd_64_to_32_bits_dfa_out_data_31_reg0_274q <= wire_lcd_64_to_32_bits_dfa_b_data_31_191m_dataout;
				lcd_64_to_32_bits_dfa_out_data_3_reg0_302q <= wire_lcd_64_to_32_bits_dfa_b_data_3_219m_dataout;
				lcd_64_to_32_bits_dfa_out_data_4_reg0_301q <= wire_lcd_64_to_32_bits_dfa_b_data_4_218m_dataout;
				lcd_64_to_32_bits_dfa_out_data_5_reg0_300q <= wire_lcd_64_to_32_bits_dfa_b_data_5_217m_dataout;
				lcd_64_to_32_bits_dfa_out_data_6_reg0_299q <= wire_lcd_64_to_32_bits_dfa_b_data_6_216m_dataout;
				lcd_64_to_32_bits_dfa_out_data_7_reg0_298q <= wire_lcd_64_to_32_bits_dfa_b_data_7_215m_dataout;
				lcd_64_to_32_bits_dfa_out_data_8_reg0_297q <= wire_lcd_64_to_32_bits_dfa_b_data_8_214m_dataout;
				lcd_64_to_32_bits_dfa_out_data_9_reg0_296q <= wire_lcd_64_to_32_bits_dfa_b_data_9_213m_dataout;
				lcd_64_to_32_bits_dfa_out_empty_0_reg0_272q <= wire_lcd_64_to_32_bits_dfa_mux5_229_o;
				lcd_64_to_32_bits_dfa_out_empty_1_reg0_308q <= wire_lcd_64_to_32_bits_dfa_mux4_228_o;
				lcd_64_to_32_bits_dfa_out_endofpacket_reg0_307q <= wire_lcd_64_to_32_bits_dfa_mux6_230_o;
				lcd_64_to_32_bits_dfa_out_startofpacket_reg0_306q <= wire_lcd_64_to_32_bits_dfa_b_startofpacket_223m_dataout;
			END IF;
		END IF;
	END PROCESS;
	PROCESS (clk, reset_n)
	BEGIN
		IF (reset_n = '0') THEN
				lcd_64_to_32_bits_dfa_out_valid_reg0_273q <= '0';
				lcd_64_to_32_bits_dfa_state_register_0_271q <= '0';
				lcd_64_to_32_bits_dfa_state_register_1_145q <= '0';
				lcd_64_to_32_bits_dfa_state_register_2_144q <= '0';
		ELSIF (clk = '1' AND clk'event) THEN
				lcd_64_to_32_bits_dfa_out_valid_reg0_273q <= wire_lcd_64_to_32_bits_dfa_out_valid_reg0_420m_dataout;
				lcd_64_to_32_bits_dfa_state_register_0_271q <= wire_lcd_64_to_32_bits_dfa_mux3_227_o;
				lcd_64_to_32_bits_dfa_state_register_1_145q <= wire_lcd_64_to_32_bits_dfa_mux2_226_o;
				lcd_64_to_32_bits_dfa_state_register_2_144q <= wire_lcd_64_to_32_bits_dfa_mux1_225_o;
		END IF;
	END PROCESS;
	wire_nl_w_lg_lcd_64_to_32_bits_dfa_out_valid_reg0_273q82w(0) <= NOT lcd_64_to_32_bits_dfa_out_valid_reg0_273q;
	PROCESS (clk, reset_n)
	BEGIN
		IF (reset_n = '0') THEN
				lcd_64_to_32_bits_dfa_a_data0_0_82q <= '0';
				lcd_64_to_32_bits_dfa_a_data0_1_81q <= '0';
				lcd_64_to_32_bits_dfa_a_data0_2_80q <= '0';
				lcd_64_to_32_bits_dfa_a_data0_3_79q <= '0';
				lcd_64_to_32_bits_dfa_a_data0_4_78q <= '0';
				lcd_64_to_32_bits_dfa_a_data0_5_77q <= '0';
				lcd_64_to_32_bits_dfa_a_data0_6_76q <= '0';
				lcd_64_to_32_bits_dfa_a_data0_7_75q <= '0';
				lcd_64_to_32_bits_dfa_a_data1_0_90q <= '0';
				lcd_64_to_32_bits_dfa_a_data1_1_89q <= '0';
				lcd_64_to_32_bits_dfa_a_data1_2_88q <= '0';
				lcd_64_to_32_bits_dfa_a_data1_3_87q <= '0';
				lcd_64_to_32_bits_dfa_a_data1_4_86q <= '0';
				lcd_64_to_32_bits_dfa_a_data1_5_85q <= '0';
				lcd_64_to_32_bits_dfa_a_data1_6_84q <= '0';
				lcd_64_to_32_bits_dfa_a_data1_7_83q <= '0';
				lcd_64_to_32_bits_dfa_a_data2_0_98q <= '0';
				lcd_64_to_32_bits_dfa_a_data2_1_97q <= '0';
				lcd_64_to_32_bits_dfa_a_data2_2_96q <= '0';
				lcd_64_to_32_bits_dfa_a_data2_3_95q <= '0';
				lcd_64_to_32_bits_dfa_a_data2_4_94q <= '0';
				lcd_64_to_32_bits_dfa_a_data2_5_93q <= '0';
				lcd_64_to_32_bits_dfa_a_data2_6_92q <= '0';
				lcd_64_to_32_bits_dfa_a_data2_7_91q <= '0';
				lcd_64_to_32_bits_dfa_a_data3_0_106q <= '0';
				lcd_64_to_32_bits_dfa_a_data3_1_105q <= '0';
				lcd_64_to_32_bits_dfa_a_data3_2_104q <= '0';
				lcd_64_to_32_bits_dfa_a_data3_3_103q <= '0';
				lcd_64_to_32_bits_dfa_a_data3_4_102q <= '0';
				lcd_64_to_32_bits_dfa_a_data3_5_101q <= '0';
				lcd_64_to_32_bits_dfa_a_data3_6_100q <= '0';
				lcd_64_to_32_bits_dfa_a_data3_7_99q <= '0';
				lcd_64_to_32_bits_dfa_a_data4_0_114q <= '0';
				lcd_64_to_32_bits_dfa_a_data4_1_113q <= '0';
				lcd_64_to_32_bits_dfa_a_data4_2_112q <= '0';
				lcd_64_to_32_bits_dfa_a_data4_3_111q <= '0';
				lcd_64_to_32_bits_dfa_a_data4_4_110q <= '0';
				lcd_64_to_32_bits_dfa_a_data4_5_109q <= '0';
				lcd_64_to_32_bits_dfa_a_data4_6_108q <= '0';
				lcd_64_to_32_bits_dfa_a_data4_7_107q <= '0';
				lcd_64_to_32_bits_dfa_a_data5_0_122q <= '0';
				lcd_64_to_32_bits_dfa_a_data5_1_121q <= '0';
				lcd_64_to_32_bits_dfa_a_data5_2_120q <= '0';
				lcd_64_to_32_bits_dfa_a_data5_3_119q <= '0';
				lcd_64_to_32_bits_dfa_a_data5_4_118q <= '0';
				lcd_64_to_32_bits_dfa_a_data5_5_117q <= '0';
				lcd_64_to_32_bits_dfa_a_data5_6_116q <= '0';
				lcd_64_to_32_bits_dfa_a_data5_7_115q <= '0';
				lcd_64_to_32_bits_dfa_a_data6_0_130q <= '0';
				lcd_64_to_32_bits_dfa_a_data6_1_129q <= '0';
				lcd_64_to_32_bits_dfa_a_data6_2_128q <= '0';
				lcd_64_to_32_bits_dfa_a_data6_3_127q <= '0';
				lcd_64_to_32_bits_dfa_a_data6_4_126q <= '0';
				lcd_64_to_32_bits_dfa_a_data6_5_125q <= '0';
				lcd_64_to_32_bits_dfa_a_data6_6_124q <= '0';
				lcd_64_to_32_bits_dfa_a_data6_7_123q <= '0';
				lcd_64_to_32_bits_dfa_a_data7_0_138q <= '0';
				lcd_64_to_32_bits_dfa_a_data7_1_137q <= '0';
				lcd_64_to_32_bits_dfa_a_data7_2_136q <= '0';
				lcd_64_to_32_bits_dfa_a_data7_3_135q <= '0';
				lcd_64_to_32_bits_dfa_a_data7_4_134q <= '0';
				lcd_64_to_32_bits_dfa_a_data7_5_133q <= '0';
				lcd_64_to_32_bits_dfa_a_data7_6_132q <= '0';
				lcd_64_to_32_bits_dfa_a_data7_7_131q <= '0';
				lcd_64_to_32_bits_dfa_a_empty_0_143q <= '0';
				lcd_64_to_32_bits_dfa_a_empty_1_142q <= '0';
				lcd_64_to_32_bits_dfa_a_empty_2_141q <= '0';
				lcd_64_to_32_bits_dfa_a_endofpacket_140q <= '0';
				lcd_64_to_32_bits_dfa_a_startofpacket_139q <= '0';
				lcd_64_to_32_bits_dfa_a_valid_74q <= '0';
		ELSIF (clk = '1' AND clk'event) THEN
			IF (s_wire_lcd_64_to_32_bits_dfa_in_ready_232_dataout = '1') THEN
				lcd_64_to_32_bits_dfa_a_data0_0_82q <= in_data(56);
				lcd_64_to_32_bits_dfa_a_data0_1_81q <= in_data(57);
				lcd_64_to_32_bits_dfa_a_data0_2_80q <= in_data(58);
				lcd_64_to_32_bits_dfa_a_data0_3_79q <= in_data(59);
				lcd_64_to_32_bits_dfa_a_data0_4_78q <= in_data(60);
				lcd_64_to_32_bits_dfa_a_data0_5_77q <= in_data(61);
				lcd_64_to_32_bits_dfa_a_data0_6_76q <= in_data(62);
				lcd_64_to_32_bits_dfa_a_data0_7_75q <= in_data(63);
				lcd_64_to_32_bits_dfa_a_data1_0_90q <= in_data(48);
				lcd_64_to_32_bits_dfa_a_data1_1_89q <= in_data(49);
				lcd_64_to_32_bits_dfa_a_data1_2_88q <= in_data(50);
				lcd_64_to_32_bits_dfa_a_data1_3_87q <= in_data(51);
				lcd_64_to_32_bits_dfa_a_data1_4_86q <= in_data(52);
				lcd_64_to_32_bits_dfa_a_data1_5_85q <= in_data(53);
				lcd_64_to_32_bits_dfa_a_data1_6_84q <= in_data(54);
				lcd_64_to_32_bits_dfa_a_data1_7_83q <= in_data(55);
				lcd_64_to_32_bits_dfa_a_data2_0_98q <= in_data(40);
				lcd_64_to_32_bits_dfa_a_data2_1_97q <= in_data(41);
				lcd_64_to_32_bits_dfa_a_data2_2_96q <= in_data(42);
				lcd_64_to_32_bits_dfa_a_data2_3_95q <= in_data(43);
				lcd_64_to_32_bits_dfa_a_data2_4_94q <= in_data(44);
				lcd_64_to_32_bits_dfa_a_data2_5_93q <= in_data(45);
				lcd_64_to_32_bits_dfa_a_data2_6_92q <= in_data(46);
				lcd_64_to_32_bits_dfa_a_data2_7_91q <= in_data(47);
				lcd_64_to_32_bits_dfa_a_data3_0_106q <= in_data(32);
				lcd_64_to_32_bits_dfa_a_data3_1_105q <= in_data(33);
				lcd_64_to_32_bits_dfa_a_data3_2_104q <= in_data(34);
				lcd_64_to_32_bits_dfa_a_data3_3_103q <= in_data(35);
				lcd_64_to_32_bits_dfa_a_data3_4_102q <= in_data(36);
				lcd_64_to_32_bits_dfa_a_data3_5_101q <= in_data(37);
				lcd_64_to_32_bits_dfa_a_data3_6_100q <= in_data(38);
				lcd_64_to_32_bits_dfa_a_data3_7_99q <= in_data(39);
				lcd_64_to_32_bits_dfa_a_data4_0_114q <= in_data(24);
				lcd_64_to_32_bits_dfa_a_data4_1_113q <= in_data(25);
				lcd_64_to_32_bits_dfa_a_data4_2_112q <= in_data(26);
				lcd_64_to_32_bits_dfa_a_data4_3_111q <= in_data(27);
				lcd_64_to_32_bits_dfa_a_data4_4_110q <= in_data(28);
				lcd_64_to_32_bits_dfa_a_data4_5_109q <= in_data(29);
				lcd_64_to_32_bits_dfa_a_data4_6_108q <= in_data(30);
				lcd_64_to_32_bits_dfa_a_data4_7_107q <= in_data(31);
				lcd_64_to_32_bits_dfa_a_data5_0_122q <= in_data(16);
				lcd_64_to_32_bits_dfa_a_data5_1_121q <= in_data(17);
				lcd_64_to_32_bits_dfa_a_data5_2_120q <= in_data(18);
				lcd_64_to_32_bits_dfa_a_data5_3_119q <= in_data(19);
				lcd_64_to_32_bits_dfa_a_data5_4_118q <= in_data(20);
				lcd_64_to_32_bits_dfa_a_data5_5_117q <= in_data(21);
				lcd_64_to_32_bits_dfa_a_data5_6_116q <= in_data(22);
				lcd_64_to_32_bits_dfa_a_data5_7_115q <= in_data(23);
				lcd_64_to_32_bits_dfa_a_data6_0_130q <= in_data(8);
				lcd_64_to_32_bits_dfa_a_data6_1_129q <= in_data(9);
				lcd_64_to_32_bits_dfa_a_data6_2_128q <= in_data(10);
				lcd_64_to_32_bits_dfa_a_data6_3_127q <= in_data(11);
				lcd_64_to_32_bits_dfa_a_data6_4_126q <= in_data(12);
				lcd_64_to_32_bits_dfa_a_data6_5_125q <= in_data(13);
				lcd_64_to_32_bits_dfa_a_data6_6_124q <= in_data(14);
				lcd_64_to_32_bits_dfa_a_data6_7_123q <= in_data(15);
				lcd_64_to_32_bits_dfa_a_data7_0_138q <= in_data(0);
				lcd_64_to_32_bits_dfa_a_data7_1_137q <= in_data(1);
				lcd_64_to_32_bits_dfa_a_data7_2_136q <= in_data(2);
				lcd_64_to_32_bits_dfa_a_data7_3_135q <= in_data(3);
				lcd_64_to_32_bits_dfa_a_data7_4_134q <= in_data(4);
				lcd_64_to_32_bits_dfa_a_data7_5_133q <= in_data(5);
				lcd_64_to_32_bits_dfa_a_data7_6_132q <= in_data(6);
				lcd_64_to_32_bits_dfa_a_data7_7_131q <= in_data(7);
				lcd_64_to_32_bits_dfa_a_empty_0_143q <= wire_lcd_64_to_32_bits_dfa_a_empty_3m_dataout;
				lcd_64_to_32_bits_dfa_a_empty_1_142q <= wire_lcd_64_to_32_bits_dfa_a_empty_2m_dataout;
				lcd_64_to_32_bits_dfa_a_empty_2_141q <= wire_lcd_64_to_32_bits_dfa_a_empty_1m_dataout;
				lcd_64_to_32_bits_dfa_a_endofpacket_140q <= in_endofpacket;
				lcd_64_to_32_bits_dfa_a_startofpacket_139q <= in_startofpacket;
				lcd_64_to_32_bits_dfa_a_valid_74q <= in_valid;
			END IF;
		END IF;
	END PROCESS;
	wire_nO_w_lg_lcd_64_to_32_bits_dfa_a_valid_74q199w(0) <= NOT lcd_64_to_32_bits_dfa_a_valid_74q;
	wire_lcd_64_to_32_bits_dfa_a_empty_1m_dataout <= in_empty(2) AND in_endofpacket;
	wire_lcd_64_to_32_bits_dfa_a_empty_2m_dataout <= in_empty(1) AND in_endofpacket;
	wire_lcd_64_to_32_bits_dfa_a_empty_3m_dataout <= in_empty(0) AND in_endofpacket;
	wire_lcd_64_to_32_bits_dfa_a_ready_163m_dataout <= s_wire_lcd_64_to_32_bits_dfa_always4_155_dataout AND lcd_64_to_32_bits_dfa_a_valid_74q;
	wire_lcd_64_to_32_bits_dfa_a_ready_169m_dataout <= wire_lcd_64_to_32_bits_dfa_a_ready_163m_dataout AND s_wire_lcd_64_to_32_bits_dfa_always4_171_dataout;
	wire_lcd_64_to_32_bits_dfa_b_data_0_222m_dataout <= lcd_64_to_32_bits_dfa_a_data7_0_138q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data3_0_106q;
	wire_lcd_64_to_32_bits_dfa_b_data_10_212m_dataout <= lcd_64_to_32_bits_dfa_a_data6_2_128q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data2_2_96q;
	wire_lcd_64_to_32_bits_dfa_b_data_11_211m_dataout <= lcd_64_to_32_bits_dfa_a_data6_3_127q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data2_3_95q;
	wire_lcd_64_to_32_bits_dfa_b_data_12_210m_dataout <= lcd_64_to_32_bits_dfa_a_data6_4_126q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data2_4_94q;
	wire_lcd_64_to_32_bits_dfa_b_data_13_209m_dataout <= lcd_64_to_32_bits_dfa_a_data6_5_125q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data2_5_93q;
	wire_lcd_64_to_32_bits_dfa_b_data_14_208m_dataout <= lcd_64_to_32_bits_dfa_a_data6_6_124q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data2_6_92q;
	wire_lcd_64_to_32_bits_dfa_b_data_15_207m_dataout <= lcd_64_to_32_bits_dfa_a_data6_7_123q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data2_7_91q;
	wire_lcd_64_to_32_bits_dfa_b_data_16_206m_dataout <= lcd_64_to_32_bits_dfa_a_data5_0_122q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data1_0_90q;
	wire_lcd_64_to_32_bits_dfa_b_data_17_205m_dataout <= lcd_64_to_32_bits_dfa_a_data5_1_121q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data1_1_89q;
	wire_lcd_64_to_32_bits_dfa_b_data_18_204m_dataout <= lcd_64_to_32_bits_dfa_a_data5_2_120q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data1_2_88q;
	wire_lcd_64_to_32_bits_dfa_b_data_19_203m_dataout <= lcd_64_to_32_bits_dfa_a_data5_3_119q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data1_3_87q;
	wire_lcd_64_to_32_bits_dfa_b_data_1_221m_dataout <= lcd_64_to_32_bits_dfa_a_data7_1_137q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data3_1_105q;
	wire_lcd_64_to_32_bits_dfa_b_data_20_202m_dataout <= lcd_64_to_32_bits_dfa_a_data5_4_118q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data1_4_86q;
	wire_lcd_64_to_32_bits_dfa_b_data_21_201m_dataout <= lcd_64_to_32_bits_dfa_a_data5_5_117q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data1_5_85q;
	wire_lcd_64_to_32_bits_dfa_b_data_22_200m_dataout <= lcd_64_to_32_bits_dfa_a_data5_6_116q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data1_6_84q;
	wire_lcd_64_to_32_bits_dfa_b_data_23_199m_dataout <= lcd_64_to_32_bits_dfa_a_data5_7_115q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data1_7_83q;
	wire_lcd_64_to_32_bits_dfa_b_data_24_198m_dataout <= lcd_64_to_32_bits_dfa_a_data4_0_114q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data0_0_82q;
	wire_lcd_64_to_32_bits_dfa_b_data_25_197m_dataout <= lcd_64_to_32_bits_dfa_a_data4_1_113q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data0_1_81q;
	wire_lcd_64_to_32_bits_dfa_b_data_26_196m_dataout <= lcd_64_to_32_bits_dfa_a_data4_2_112q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data0_2_80q;
	wire_lcd_64_to_32_bits_dfa_b_data_27_195m_dataout <= lcd_64_to_32_bits_dfa_a_data4_3_111q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data0_3_79q;
	wire_lcd_64_to_32_bits_dfa_b_data_28_194m_dataout <= lcd_64_to_32_bits_dfa_a_data4_4_110q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data0_4_78q;
	wire_lcd_64_to_32_bits_dfa_b_data_29_193m_dataout <= lcd_64_to_32_bits_dfa_a_data4_5_109q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data0_5_77q;
	wire_lcd_64_to_32_bits_dfa_b_data_2_220m_dataout <= lcd_64_to_32_bits_dfa_a_data7_2_136q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data3_2_104q;
	wire_lcd_64_to_32_bits_dfa_b_data_30_192m_dataout <= lcd_64_to_32_bits_dfa_a_data4_6_108q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data0_6_76q;
	wire_lcd_64_to_32_bits_dfa_b_data_31_191m_dataout <= lcd_64_to_32_bits_dfa_a_data4_7_107q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data0_7_75q;
	wire_lcd_64_to_32_bits_dfa_b_data_3_219m_dataout <= lcd_64_to_32_bits_dfa_a_data7_3_135q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data3_3_103q;
	wire_lcd_64_to_32_bits_dfa_b_data_4_218m_dataout <= lcd_64_to_32_bits_dfa_a_data7_4_134q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data3_4_102q;
	wire_lcd_64_to_32_bits_dfa_b_data_5_217m_dataout <= lcd_64_to_32_bits_dfa_a_data7_5_133q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data3_5_101q;
	wire_lcd_64_to_32_bits_dfa_b_data_6_216m_dataout <= lcd_64_to_32_bits_dfa_a_data7_6_132q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data3_6_100q;
	wire_lcd_64_to_32_bits_dfa_b_data_7_215m_dataout <= lcd_64_to_32_bits_dfa_a_data7_7_131q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data3_7_99q;
	wire_lcd_64_to_32_bits_dfa_b_data_8_214m_dataout <= lcd_64_to_32_bits_dfa_a_data6_0_130q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data2_0_98q;
	wire_lcd_64_to_32_bits_dfa_b_data_9_213m_dataout <= lcd_64_to_32_bits_dfa_a_data6_1_129q WHEN s_wire_lcd_64_to_32_bits_dfa_wideor0_190_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_a_data2_1_97q;
	wire_lcd_64_to_32_bits_dfa_b_empty_156m_dataout <= lcd_64_to_32_bits_dfa_a_empty_1_142q AND s_wire_lcd_64_to_32_bits_dfa_always4_155_dataout;
	wire_lcd_64_to_32_bits_dfa_b_empty_157m_dataout <= lcd_64_to_32_bits_dfa_a_empty_0_143q AND s_wire_lcd_64_to_32_bits_dfa_always4_155_dataout;
	wire_lcd_64_to_32_bits_dfa_b_empty_161m_dataout <= wire_lcd_64_to_32_bits_dfa_b_empty_156m_dataout AND lcd_64_to_32_bits_dfa_a_valid_74q;
	wire_lcd_64_to_32_bits_dfa_b_empty_162m_dataout <= wire_lcd_64_to_32_bits_dfa_b_empty_157m_dataout AND lcd_64_to_32_bits_dfa_a_valid_74q;
	wire_lcd_64_to_32_bits_dfa_b_empty_167m_dataout <= wire_lcd_64_to_32_bits_dfa_b_empty_161m_dataout AND s_wire_lcd_64_to_32_bits_dfa_always4_171_dataout;
	wire_lcd_64_to_32_bits_dfa_b_empty_168m_dataout <= wire_lcd_64_to_32_bits_dfa_b_empty_162m_dataout AND s_wire_lcd_64_to_32_bits_dfa_always4_171_dataout;
	wire_lcd_64_to_32_bits_dfa_b_empty_174m_dataout <= lcd_64_to_32_bits_dfa_a_empty_1_142q AND s_wire_lcd_64_to_32_bits_dfa_always4_173_dataout;
	wire_lcd_64_to_32_bits_dfa_b_empty_175m_dataout <= lcd_64_to_32_bits_dfa_a_empty_0_143q AND s_wire_lcd_64_to_32_bits_dfa_always4_173_dataout;
	wire_lcd_64_to_32_bits_dfa_b_empty_179m_dataout <= wire_lcd_64_to_32_bits_dfa_b_empty_174m_dataout AND lcd_64_to_32_bits_dfa_a_valid_74q;
	wire_lcd_64_to_32_bits_dfa_b_empty_180m_dataout <= wire_lcd_64_to_32_bits_dfa_b_empty_175m_dataout AND lcd_64_to_32_bits_dfa_a_valid_74q;
	wire_lcd_64_to_32_bits_dfa_b_empty_186m_dataout <= wire_lcd_64_to_32_bits_dfa_b_empty_179m_dataout AND s_wire_lcd_64_to_32_bits_dfa_always4_171_dataout;
	wire_lcd_64_to_32_bits_dfa_b_empty_187m_dataout <= wire_lcd_64_to_32_bits_dfa_b_empty_180m_dataout AND s_wire_lcd_64_to_32_bits_dfa_always4_171_dataout;
	wire_lcd_64_to_32_bits_dfa_b_endofpacket_149m_dataout <= s_wire_lcd_64_to_32_bits_dfa_always4_173_dataout AND lcd_64_to_32_bits_dfa_a_valid_74q;
	wire_lcd_64_to_32_bits_dfa_b_endofpacket_153m_dataout <= wire_lcd_64_to_32_bits_dfa_b_endofpacket_149m_dataout AND s_wire_lcd_64_to_32_bits_dfa_always4_171_dataout;
	wire_lcd_64_to_32_bits_dfa_b_endofpacket_181m_dataout <= s_wire_lcd_64_to_32_bits_dfa_always4_173_dataout AND lcd_64_to_32_bits_dfa_a_valid_74q;
	wire_lcd_64_to_32_bits_dfa_b_endofpacket_188m_dataout <= wire_lcd_64_to_32_bits_dfa_b_endofpacket_181m_dataout AND s_wire_lcd_64_to_32_bits_dfa_always4_171_dataout;
	wire_lcd_64_to_32_bits_dfa_b_startofpacket_223m_dataout <= lcd_64_to_32_bits_dfa_a_startofpacket_139q AND wire_lcd_64_to_32_bits_dfa_decoder0_189_o(0);
	wire_lcd_64_to_32_bits_dfa_b_valid_182m_dataout <= lcd_64_to_32_bits_dfa_a_valid_74q AND s_wire_lcd_64_to_32_bits_dfa_always4_171_dataout;
	wire_lcd_64_to_32_bits_dfa_new_state_147m_dataout <= wire_w68w(0) WHEN lcd_64_to_32_bits_dfa_a_valid_74q = '1'  ELSE lcd_64_to_32_bits_dfa_state_register_2_144q;
	wire_lcd_64_to_32_bits_dfa_new_state_148m_dataout <= wire_w68w(0) WHEN lcd_64_to_32_bits_dfa_a_valid_74q = '1'  ELSE lcd_64_to_32_bits_dfa_state_register_1_145q;
	wire_lcd_64_to_32_bits_dfa_new_state_151m_dataout <= wire_lcd_64_to_32_bits_dfa_new_state_147m_dataout WHEN s_wire_lcd_64_to_32_bits_dfa_always4_171_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_state_register_2_144q;
	wire_lcd_64_to_32_bits_dfa_new_state_152m_dataout <= wire_lcd_64_to_32_bits_dfa_new_state_148m_dataout WHEN s_wire_lcd_64_to_32_bits_dfa_always4_171_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_state_register_1_145q;
	wire_lcd_64_to_32_bits_dfa_new_state_158m_dataout <= wire_w81w(0) WHEN lcd_64_to_32_bits_dfa_a_valid_74q = '1'  ELSE lcd_64_to_32_bits_dfa_state_register_2_144q;
	wire_lcd_64_to_32_bits_dfa_new_state_159m_dataout <= wire_w81w(0) WHEN lcd_64_to_32_bits_dfa_a_valid_74q = '1'  ELSE lcd_64_to_32_bits_dfa_state_register_1_145q;
	wire_lcd_64_to_32_bits_dfa_new_state_160m_dataout <= wire_w81w(0) WHEN lcd_64_to_32_bits_dfa_a_valid_74q = '1'  ELSE lcd_64_to_32_bits_dfa_state_register_0_271q;
	wire_lcd_64_to_32_bits_dfa_new_state_164m_dataout <= wire_lcd_64_to_32_bits_dfa_new_state_158m_dataout WHEN s_wire_lcd_64_to_32_bits_dfa_always4_171_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_state_register_2_144q;
	wire_lcd_64_to_32_bits_dfa_new_state_165m_dataout <= wire_lcd_64_to_32_bits_dfa_new_state_159m_dataout WHEN s_wire_lcd_64_to_32_bits_dfa_always4_171_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_state_register_1_145q;
	wire_lcd_64_to_32_bits_dfa_new_state_166m_dataout <= wire_lcd_64_to_32_bits_dfa_new_state_160m_dataout WHEN s_wire_lcd_64_to_32_bits_dfa_always4_171_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_state_register_0_271q;
	wire_lcd_64_to_32_bits_dfa_new_state_176m_dataout <= lcd_64_to_32_bits_dfa_state_register_2_144q AND NOT(lcd_64_to_32_bits_dfa_a_valid_74q);
	wire_lcd_64_to_32_bits_dfa_new_state_177m_dataout <= lcd_64_to_32_bits_dfa_state_register_1_145q AND NOT(lcd_64_to_32_bits_dfa_a_valid_74q);
	wire_lcd_64_to_32_bits_dfa_new_state_178m_dataout <= lcd_64_to_32_bits_dfa_state_register_0_271q AND NOT(lcd_64_to_32_bits_dfa_a_valid_74q);
	wire_lcd_64_to_32_bits_dfa_new_state_183m_dataout <= wire_lcd_64_to_32_bits_dfa_new_state_176m_dataout WHEN s_wire_lcd_64_to_32_bits_dfa_always4_171_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_state_register_2_144q;
	wire_lcd_64_to_32_bits_dfa_new_state_184m_dataout <= wire_lcd_64_to_32_bits_dfa_new_state_177m_dataout WHEN s_wire_lcd_64_to_32_bits_dfa_always4_171_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_state_register_1_145q;
	wire_lcd_64_to_32_bits_dfa_new_state_185m_dataout <= wire_lcd_64_to_32_bits_dfa_new_state_178m_dataout WHEN s_wire_lcd_64_to_32_bits_dfa_always4_171_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_state_register_0_271q;
	wire_lcd_64_to_32_bits_dfa_out_valid_reg0_420m_dataout <= wire_lcd_64_to_32_bits_dfa_b_valid_182m_dataout WHEN s_wire_lcd_64_to_32_bits_dfa_always4_171_dataout = '1'  ELSE lcd_64_to_32_bits_dfa_out_valid_reg0_273q;
	wire_lcd_64_to_32_bits_dfa_decoder0_189_i <= ( lcd_64_to_32_bits_dfa_state_register_2_144q & lcd_64_to_32_bits_dfa_state_register_1_145q & lcd_64_to_32_bits_dfa_state_register_0_271q);
	lcd_64_to_32_bits_dfa_decoder0_189 :  oper_decoder
	  GENERIC MAP (
		width_i => 3,
		width_o => 8
	  )
	  PORT MAP ( 
		i => wire_lcd_64_to_32_bits_dfa_decoder0_189_i,
		o => wire_lcd_64_to_32_bits_dfa_decoder0_189_o
	  );
	wire_lcd_64_to_32_bits_dfa_lessthan0_154_a <= ( "1" & "0" & "0");
	wire_lcd_64_to_32_bits_dfa_lessthan0_154_b <= ( lcd_64_to_32_bits_dfa_a_empty_2_141q & lcd_64_to_32_bits_dfa_a_empty_1_142q & lcd_64_to_32_bits_dfa_a_empty_0_143q);
	lcd_64_to_32_bits_dfa_lessthan0_154 :  oper_less_than
	  GENERIC MAP (
		sgate_representation => 0,
		width_a => 3,
		width_b => 3
	  )
	  PORT MAP ( 
		a => wire_lcd_64_to_32_bits_dfa_lessthan0_154_a,
		b => wire_lcd_64_to_32_bits_dfa_lessthan0_154_b,
		cin => wire_vcc,
		o => wire_lcd_64_to_32_bits_dfa_lessthan0_154_o
	  );
	wire_lcd_64_to_32_bits_dfa_lessthan1_172_a <= ( "0" & "0" & "0");
	wire_lcd_64_to_32_bits_dfa_lessthan1_172_b <= ( lcd_64_to_32_bits_dfa_a_empty_2_141q & lcd_64_to_32_bits_dfa_a_empty_1_142q & lcd_64_to_32_bits_dfa_a_empty_0_143q);
	lcd_64_to_32_bits_dfa_lessthan1_172 :  oper_less_than
	  GENERIC MAP (
		sgate_representation => 0,
		width_a => 3,
		width_b => 3
	  )
	  PORT MAP ( 
		a => wire_lcd_64_to_32_bits_dfa_lessthan1_172_a,
		b => wire_lcd_64_to_32_bits_dfa_lessthan1_172_b,
		cin => wire_vcc,
		o => wire_lcd_64_to_32_bits_dfa_lessthan1_172_o
	  );
	wire_lcd_64_to_32_bits_dfa_mux0_224_data <= ( s_wire_lcd_64_to_32_bits_dfa_always4_171_dataout & wire_lcd_64_to_32_bits_dfa_a_ready_169m_dataout & s_wire_lcd_64_to_32_bits_dfa_always4_171_dataout & wire_lcd_64_to_32_bits_dfa_a_ready_169m_dataout & s_wire_lcd_64_to_32_bits_dfa_always4_171_dataout & wire_lcd_64_to_32_bits_dfa_a_ready_169m_dataout & s_wire_lcd_64_to_32_bits_dfa_always4_171_dataout & wire_lcd_64_to_32_bits_dfa_a_ready_169m_dataout);
	wire_lcd_64_to_32_bits_dfa_mux0_224_sel <= ( lcd_64_to_32_bits_dfa_state_register_2_144q & lcd_64_to_32_bits_dfa_state_register_1_145q & lcd_64_to_32_bits_dfa_state_register_0_271q);
	lcd_64_to_32_bits_dfa_mux0_224 :  oper_mux
	  GENERIC MAP (
		width_data => 8,
		width_sel => 3
	  )
	  PORT MAP ( 
		data => wire_lcd_64_to_32_bits_dfa_mux0_224_data,
		o => wire_lcd_64_to_32_bits_dfa_mux0_224_o,
		sel => wire_lcd_64_to_32_bits_dfa_mux0_224_sel
	  );
	wire_lcd_64_to_32_bits_dfa_mux1_225_data <= ( wire_lcd_64_to_32_bits_dfa_new_state_183m_dataout & wire_lcd_64_to_32_bits_dfa_new_state_164m_dataout & wire_lcd_64_to_32_bits_dfa_new_state_151m_dataout & wire_lcd_64_to_32_bits_dfa_new_state_164m_dataout & wire_lcd_64_to_32_bits_dfa_new_state_151m_dataout & wire_lcd_64_to_32_bits_dfa_new_state_183m_dataout & wire_lcd_64_to_32_bits_dfa_new_state_183m_dataout & wire_lcd_64_to_32_bits_dfa_new_state_183m_dataout);
	wire_lcd_64_to_32_bits_dfa_mux1_225_sel <= ( lcd_64_to_32_bits_dfa_state_register_2_144q & lcd_64_to_32_bits_dfa_state_register_1_145q & lcd_64_to_32_bits_dfa_state_register_0_271q);
	lcd_64_to_32_bits_dfa_mux1_225 :  oper_mux
	  GENERIC MAP (
		width_data => 8,
		width_sel => 3
	  )
	  PORT MAP ( 
		data => wire_lcd_64_to_32_bits_dfa_mux1_225_data,
		o => wire_lcd_64_to_32_bits_dfa_mux1_225_o,
		sel => wire_lcd_64_to_32_bits_dfa_mux1_225_sel
	  );
	wire_lcd_64_to_32_bits_dfa_mux2_226_data <= ( wire_lcd_64_to_32_bits_dfa_new_state_184m_dataout & wire_lcd_64_to_32_bits_dfa_new_state_165m_dataout & wire_lcd_64_to_32_bits_dfa_new_state_152m_dataout & wire_lcd_64_to_32_bits_dfa_new_state_184m_dataout & wire_lcd_64_to_32_bits_dfa_new_state_184m_dataout & wire_lcd_64_to_32_bits_dfa_new_state_165m_dataout & wire_lcd_64_to_32_bits_dfa_new_state_152m_dataout & wire_lcd_64_to_32_bits_dfa_new_state_184m_dataout);
	wire_lcd_64_to_32_bits_dfa_mux2_226_sel <= ( lcd_64_to_32_bits_dfa_state_register_2_144q & lcd_64_to_32_bits_dfa_state_register_1_145q & lcd_64_to_32_bits_dfa_state_register_0_271q);
	lcd_64_to_32_bits_dfa_mux2_226 :  oper_mux
	  GENERIC MAP (
		width_data => 8,
		width_sel => 3
	  )
	  PORT MAP ( 
		data => wire_lcd_64_to_32_bits_dfa_mux2_226_data,
		o => wire_lcd_64_to_32_bits_dfa_mux2_226_o,
		sel => wire_lcd_64_to_32_bits_dfa_mux2_226_sel
	  );
	wire_lcd_64_to_32_bits_dfa_mux3_227_data <= ( wire_lcd_64_to_32_bits_dfa_new_state_185m_dataout & wire_lcd_64_to_32_bits_dfa_new_state_166m_dataout & wire_lcd_64_to_32_bits_dfa_new_state_185m_dataout & wire_lcd_64_to_32_bits_dfa_new_state_166m_dataout & wire_lcd_64_to_32_bits_dfa_new_state_185m_dataout & wire_lcd_64_to_32_bits_dfa_new_state_166m_dataout & wire_lcd_64_to_32_bits_dfa_new_state_185m_dataout & wire_lcd_64_to_32_bits_dfa_new_state_166m_dataout);
	wire_lcd_64_to_32_bits_dfa_mux3_227_sel <= ( lcd_64_to_32_bits_dfa_state_register_2_144q & lcd_64_to_32_bits_dfa_state_register_1_145q & lcd_64_to_32_bits_dfa_state_register_0_271q);
	lcd_64_to_32_bits_dfa_mux3_227 :  oper_mux
	  GENERIC MAP (
		width_data => 8,
		width_sel => 3
	  )
	  PORT MAP ( 
		data => wire_lcd_64_to_32_bits_dfa_mux3_227_data,
		o => wire_lcd_64_to_32_bits_dfa_mux3_227_o,
		sel => wire_lcd_64_to_32_bits_dfa_mux3_227_sel
	  );
	wire_lcd_64_to_32_bits_dfa_mux4_228_data <= ( wire_lcd_64_to_32_bits_dfa_b_empty_186m_dataout & wire_lcd_64_to_32_bits_dfa_b_empty_167m_dataout & wire_lcd_64_to_32_bits_dfa_b_empty_186m_dataout & wire_lcd_64_to_32_bits_dfa_b_empty_167m_dataout & wire_lcd_64_to_32_bits_dfa_b_empty_186m_dataout & wire_lcd_64_to_32_bits_dfa_b_empty_167m_dataout & wire_lcd_64_to_32_bits_dfa_b_empty_186m_dataout & wire_lcd_64_to_32_bits_dfa_b_empty_167m_dataout);
	wire_lcd_64_to_32_bits_dfa_mux4_228_sel <= ( lcd_64_to_32_bits_dfa_state_register_2_144q & lcd_64_to_32_bits_dfa_state_register_1_145q & lcd_64_to_32_bits_dfa_state_register_0_271q);
	lcd_64_to_32_bits_dfa_mux4_228 :  oper_mux
	  GENERIC MAP (
		width_data => 8,
		width_sel => 3
	  )
	  PORT MAP ( 
		data => wire_lcd_64_to_32_bits_dfa_mux4_228_data,
		o => wire_lcd_64_to_32_bits_dfa_mux4_228_o,
		sel => wire_lcd_64_to_32_bits_dfa_mux4_228_sel
	  );
	wire_lcd_64_to_32_bits_dfa_mux5_229_data <= ( wire_lcd_64_to_32_bits_dfa_b_empty_187m_dataout & wire_lcd_64_to_32_bits_dfa_b_empty_168m_dataout & wire_lcd_64_to_32_bits_dfa_b_empty_187m_dataout & wire_lcd_64_to_32_bits_dfa_b_empty_168m_dataout & wire_lcd_64_to_32_bits_dfa_b_empty_187m_dataout & wire_lcd_64_to_32_bits_dfa_b_empty_168m_dataout & wire_lcd_64_to_32_bits_dfa_b_empty_187m_dataout & wire_lcd_64_to_32_bits_dfa_b_empty_168m_dataout);
	wire_lcd_64_to_32_bits_dfa_mux5_229_sel <= ( lcd_64_to_32_bits_dfa_state_register_2_144q & lcd_64_to_32_bits_dfa_state_register_1_145q & lcd_64_to_32_bits_dfa_state_register_0_271q);
	lcd_64_to_32_bits_dfa_mux5_229 :  oper_mux
	  GENERIC MAP (
		width_data => 8,
		width_sel => 3
	  )
	  PORT MAP ( 
		data => wire_lcd_64_to_32_bits_dfa_mux5_229_data,
		o => wire_lcd_64_to_32_bits_dfa_mux5_229_o,
		sel => wire_lcd_64_to_32_bits_dfa_mux5_229_sel
	  );
	wire_lcd_64_to_32_bits_dfa_mux6_230_data <= ( wire_lcd_64_to_32_bits_dfa_b_endofpacket_188m_dataout & wire_lcd_64_to_32_bits_dfa_a_ready_169m_dataout & wire_lcd_64_to_32_bits_dfa_b_endofpacket_153m_dataout & wire_lcd_64_to_32_bits_dfa_a_ready_169m_dataout & wire_lcd_64_to_32_bits_dfa_b_endofpacket_153m_dataout & wire_lcd_64_to_32_bits_dfa_a_ready_169m_dataout & wire_lcd_64_to_32_bits_dfa_b_endofpacket_153m_dataout & wire_lcd_64_to_32_bits_dfa_a_ready_169m_dataout);
	wire_lcd_64_to_32_bits_dfa_mux6_230_sel <= ( lcd_64_to_32_bits_dfa_state_register_2_144q & lcd_64_to_32_bits_dfa_state_register_1_145q & lcd_64_to_32_bits_dfa_state_register_0_271q);
	lcd_64_to_32_bits_dfa_mux6_230 :  oper_mux
	  GENERIC MAP (
		width_data => 8,
		width_sel => 3
	  )
	  PORT MAP ( 
		data => wire_lcd_64_to_32_bits_dfa_mux6_230_data,
		o => wire_lcd_64_to_32_bits_dfa_mux6_230_o,
		sel => wire_lcd_64_to_32_bits_dfa_mux6_230_sel
	  );

 END RTL; --lcd_64_to_32_bits_dfa
--synopsys translate_on
--VALID FILE
