--******************************************************************************
--                                                                             *
--                  Copyright (C) 2012 Danilo Pagano									 *
--                                                                             *
-- Este modulo implementa a FFT atraves de um pipeline utilizando como entrada *
-- um vetor de dados ordenados armazenado em uma memoria RAM e como saida um   *
-- bloco de memoria ram que armazena os dados provenientes do pipeline. 		 *
-- Os dados entram e saem do modulo atraves de uma interface avalon, onde a 	 *
-- escrita eh direcionada para a memoria de entrada e sa leitura sai da memoria*
-- de saida.																						 *
--                                                                             *
-- Module Name: avalon_pwm                  File Name: avalon_pwm.vhd          *
--                                                                             *
-- Module Function: This file contains avalon_pwm code for nios labs.          *
--                                                                             *
-- REVISION HISTORY:                                                           *
--  Revision 1.0    12/07/2009 - Initial release                               *
--******************************************************************************

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
use work.tipos.all;
use work.componentes.all;

entity fft_pipeline is
port (
--Interface signals
	clk : in std_logic;
	wr_data : in std_logic_vector (31 downto 0);
	cs : in std_logic;
	wr : in std_logic;
	rd: in std_logic;
	addr : in std_logic_vector (11 downto 0);
	clr_n : in std_logic; --Foi atribuido ao reset normal
	rd_data : out std_logic_vector (31 downto 0);
--FFT signals	
	counter: out std_logic_vector (9 downto 0);
	tx_out : out std_logic;
	rx_in: in std_logic
	);
end fft_pipeline;

architecture rtl of fft_pipeline is

COMPONENT dualportRAM IS
	PORT
	(
		clock		: IN STD_LOGIC  := '1';
		data		: IN STD_LOGIC_VECTOR (17 DOWNTO 0);
		rdaddress		: IN STD_LOGIC_VECTOR (9 DOWNTO 0);
		wraddress		: IN STD_LOGIC_VECTOR (9 DOWNTO 0);
		wren		: IN STD_LOGIC  := '0';
		q		: OUT STD_LOGIC_VECTOR (17 DOWNTO 0)
	);
END COMPONENT;


--Sinais de controle do modulo
signal control_register: std_logic_vector(31 downto 0);

--Sinais para a memoria ram dual port;
signal addr_dualportram_wr, addr_dualportram_rd: std_logic_vector (9 downto 0);
signal dado_in_ram, dado_out_ram: std_logic_vector (17 downto 0);
signal wren_ram: std_logic;

--Sinais para o controller
signal start: std_logic;

--sinais para o banco de memorias ram 
signal addr_ram12, addr_ram34	:  STD_LOGIC_VECTOR (9 DOWNTO 0);
signal in_ram1, in_ram2, in_ram3, in_ram4, in_ram5: STD_LOGIC_VECTOR (17 DOWNTO 0);
signal out_ram1, out_ram2, out_ram3, out_ram4, out_ram5: std_logic_vector(17 downto 0);
signal wen12, wen34: std_logic;

--sinais para o pipeline
signal fft_en_in, clk_pipeline, fft_clr, fft_en: std_logic;
signal cpxIN0, cpxIN1, cpxOUT0, cpxOUT1: complex;

--sinais para o memory reader
signal finished: std_logic;
signal addr_ram_read: std_logic_vector(9 downto 0);

--sinais para a saida de dados uart
signal dado_enviar: std_logic_vector(31 downto 0);
signal sel_mux: std_logic_vector(2 downto 0);
signal saida_mux: std_logic_vector( 17 downto 0);
signal send, sent: std_logic;

--Sinal de controle do fim do processamento at o inicio do proximo
signal em_espera: std_logic:='1';
signal inicio: std_logic:='0';

begin

--Implementacao do controle do estado de espera do sistema
status: process(clk, inicio, finished)
			begin
				if(rising_edge(clk))then
					if(em_espera = '1' and inicio = '1') then
						em_espera <= '0';
					elsif(em_espera = '0' and finished = '1') then
						em_espera <= '1';
					end if;
				end if;
			end process status;
			  
--Implementacao do comando de escrita no registrador de controle
control: process(clk, clr_n)
			begin
				if clr_n = '1' then
					control_register <= (others=>'0');
				elsif(rising_edge(clk))then
					control_register(1) <= em_espera;
					control_register(0) <= '0';
					if(cs = '1' and wr = '1') then
							if(addr = "100000000000") then --Se o endereco for do registrador de controle, atribua o dado 
								control_register(0) <= wr_data(0);															
							end if;
					end if;
				end if;
			end process control;		
			
inicio <= control_register(0);			

--Implementacao da dual port ram
addr_dualportram_wr <= addr(9 downto 0);
dado_in_ram <= wr_data(17 downto 0);
wren_ram <= wr and cs;			
u0: dualportRAM PORT MAP (	clk, dado_in_ram, addr_dualportram_rd, addr_dualportram_wr, wren_ram, dado_out_ram); 
cpxIN0.r <= dado_out_ram;
cpxIN0.i <= (others=>'0');
cpxIN1.i <= (others=>'0');
cpxIN1.r <= (others=>'0');

--Implementacao do pipeline
u1: fft_pipeline_8s port map (clk_pipeline, fft_en, fft_clr, cpxIN0, cpxIN1, cpxOUT0, cpxOUT1, fft_en_in, counter(9 downto 0) );		
	
addr_ram_read (8 downto 0) <= addr(8 downto 0);
sel_mux (1 downto 0) <= addr(10 downto 9);
	
--Implementacao das memorias de saida dual prt
u2:  ram1dual_real PORT MAP	(clk, cpxOUT0.r, addr_ram_read(8 downto 0), addr_ram12(8 downto 0), wen12, out_ram1);
u3:  ram1dual_imag PORT MAP	(clk, cpxOUT0.i, addr_ram_read(8 downto 0), addr_ram12(8 downto 0), wen12, out_ram2);
u4:  ram2dual_real PORT MAP	(clk, cpxOUT1.r, addr_ram_read(8 downto 0), addr_ram34(8 downto 0), wen34, out_ram3);
u5:  ram2dual_imag PORT MAP	(clk, cpxOUT1.i, addr_ram_read(8 downto 0), addr_ram34(8 downto 0), wen34, out_ram4);
--Implementacao do mux seletor da saida
u7:  mux4_1 PORT MAP (out_ram1, out_ram2, out_ram3, out_ram4, out_ram5, sel_mux, saida_mux);						  
     dado_enviar (17 downto 0) <= saida_mux;  
	  dado_enviar (31 downto 18) <= (others=>saida_mux(17));
--Implementacao do comando de leitura
rd_data <= control_register when (addr (11)='1'and rd='1') else --Se for o endereco de controle, envie o controlregister
			  dado_enviar;
			  			  
--Implementacao do controlador
u10: fft_pipeline_controller2 generic map(stages=>8) port map(   
													clk, inicio, 
													--Sinais para a memoria ROM
													addr_dualportram_rd,
													--Sinais para o pipeline
													fft_en_in, 
													clk_pipeline, 
													fft_clr, 
													fft_en,
													--Sinais para o banco de memorias
													addr_ram12,
													wen12,
													addr_ram34,
													wen34,
													--Sinais para o memory reader
													finished
													);

tx_out<=finished;			  
			  
	
end rtl;
