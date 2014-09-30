LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;
USE ieee.std_logic_signed.all;
USE work.my_functions.all;

ENTITY adder IS
GENERIC (n: INTEGER := 8);
PORT ( 
		clk: in std_logic;
		a, b: IN std_logic_vector(n-1 DOWNTO 0);
		
		add: OUT std_logic_vector(n-1 DOWNTO 0)
); 
END adder;

ARCHITECTURE RTL OF adder IS


BEGIN
	
process(clk)
variable result: std_logic_vector(n-1 downto 0);
begin
	--if(clk'event and clk='1') then
	result:= a + b;
	if(a(a'left)=b(b'left))and(result(result'left)/=a(a'left))then
	  result:= (result'left => a(a'left), others=>not a(a'left) );
   end if;
	--add <= a + b;
	add <= result;
	--end if;
end process;	
END rtl;
 