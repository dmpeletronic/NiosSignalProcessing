LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;
USE ieee.std_logic_signed.all;

ENTITY multiplyInt IS
GENERIC (n: INTEGER := 8);
PORT ( 
		a, b: IN std_logic_vector(n-1 DOWNTO 0);
		
		mult: OUT integer 
); 
END multiplyInt;

ARCHITECTURE RTL OF multiplyInt IS

--signal m: std_logic_vector((n*2-1) DOWNTO 0);

BEGIN
	
mult <= conv_integer(SIGNED(a)) * conv_integer(SIGNED(b));
	
--mult  <= conv_integer(SIGNED(m));	

END rtl;
 