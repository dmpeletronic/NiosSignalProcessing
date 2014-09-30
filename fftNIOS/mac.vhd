------- Main code: -----------------------
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;
USE work.my_functions.all;
 ------------------------------------------
ENTITY mac IS
PORT ( 
		a, b: IN SIGNED(3 DOWNTO 0);
		clk, rst: IN STD_LOGIC;
		acc: OUT SIGNED(7 DOWNTO 0)); 
END mac;
------------------------------------------
ARCHITECTURE rtl OF mac IS
SIGNAL prod, reg: SIGNED(7 DOWNTO 0);
BEGIN
 PROCESS (rst, clk)
		VARIABLE sum: SIGNED(7 DOWNTO 0);
 BEGIN
		prod <= a * b;
		IF (rst='1') THEN
			reg <= (OTHERS=>'0');
		ELSIF (clk'EVENT AND clk='1') THEN
			sum := add_truncate (prod, reg, 8);
			reg <= sum;
		END IF;
		acc <= reg;
 END PROCESS;
END rtl;