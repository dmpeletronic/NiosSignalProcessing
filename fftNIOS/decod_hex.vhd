LIBRARY ieee;
Use ieee.std_logic_1164.all;
--Entidade que recebe um dado de 4 bits e retorna o codigo em 77 segmentos
ENTITY decod_hex IS
	PORT (	
			entrada	: IN STD_LOGIC_VECTOR(3 DOWNTO 0);
			saida	: OUT STD_LOGIC_VECTOR(6 DOWNTO 0)
		);
END ENTITY;

ARCHITECTURE comportamento OF decod_hex IS
BEGIN
	saida <= 
			 "1000000" WHEN (entrada = "0000") else --0
			 "1111001" WHEN (entrada = "0001") else --1
			 "0100100" WHEN (entrada = "0010") else --2
			 "0110000" WHEN (entrada = "0011") else --3 
			 "0011001" WHEN (entrada = "0100") else --4
			 "0010010" WHEN (entrada = "0101") else --5
			 "0000010" WHEN (entrada = "0110") else --6
			 "1111000" WHEN (entrada = "0111") else --7
			 "0000000" WHEN (entrada = "1000") else --8
			 "0010000" WHEN (entrada = "1001") else --9
			 "0001000" WHEN (entrada = "1010") else --a
			 "0000011" WHEN (entrada = "1011") else --b
			 "1000110" WHEN (entrada = "1100") else --c
			 "0100001" WHEN (entrada = "1101") else --d
			 "0000110" WHEN (entrada = "1110") else --e
			 "0001110" WHEN (entrada = "1111");     --f
END comportamento;