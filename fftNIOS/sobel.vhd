------- Main code: -----------------------
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;
USE ieee.std_logic_signed.all;
USE work.my_functions.all;
USE work.tipos.all;


 ------------------------------------------
ENTITY sobel IS
generic (n: integer := 8);
PORT ( 
		--filter: IN matriz9x9;
		px: IN matriz9x9;
		clk, rst: IN STD_LOGIC;
		result: OUT std_logic_vector(n-1 DOWNTO 0)
		); 
END sobel;

ARCHITECTURE rtl OF sobel IS

COMPONENT adder IS
GENERIC (n: INTEGER := 8);
PORT ( 
	clk: in std_logic;
		a, b: IN std_logic_vector(n-1 DOWNTO 0);
		
		add: OUT std_logic_vector(n-1 DOWNTO 0)
); 
END COMPONENT;

COMPONENT multiply IS
GENERIC (n: INTEGER := 8);
PORT ( 
		a, b: IN std_logic_vector(n-1 DOWNTO 0);
		
		mult: OUT std_logic_vector((n*2-1) DOWNTO 0)
); 
END COMPONENT;

COMPONENT multiplyInt IS
GENERIC (n: INTEGER := 8);
PORT ( 
		a, b: IN std_logic_vector(n-1 DOWNTO 0);
		
		mult: OUT integer 
); 
END COMPONENT;

COMPONENT adderInt IS
GENERIC (n: INTEGER := 8);
PORT ( 
		clk: in std_logic;
		a, b: IN integer;
		
		add: OUT integer
); 
END COMPONENT;



CONSTANT fH: matriz9x9:= (
("00000001","00000010","00000001"),
("00000000","00000000","00000000"),
("11111111","11111110","11111111")
);
	
	
	
signal saidaSobelH: matriz9x9;
signal mul11,mul12,mul13,mul21,mul22,mul23,mul31,mul32,mul33: integer;-- std_logic_vector (2*n-1 downto 0);
signal sum1,sum2,sum3,sum4,sum5,sum6,sum7,sum8,sum9: integer; -- std_logic_vector (2*n-1 downto 0);
signal resultado: std_logic_vector(4*n-1 downto 0);
--signal fH: matriz9x9;
BEGIN

--fH <= filter;

m11: multiplyInt port map( px(0)(0), fH(0)(0),  mul11 );
m12: multiplyInt port map( px(0)(1), fH(0)(1),  mul12 );
m13: multiplyInt port map( px(0)(2), fH(0)(2),  mul13 );
m21: multiplyInt port map( px(1)(0), fH(1)(0),  mul21 );
m22: multiplyInt port map( px(1)(1), fH(1)(1),  mul22 );
m23: multiplyInt port map( px(1)(2), fH(1)(2),  mul23 );
m31: multiplyInt port map( px(2)(0), fH(2)(0),  mul31 );
m32: multiplyInt port map( px(2)(1), fH(2)(1),  mul32 );
m33: multiplyInt port map( px(2)(2), fH(2)(2),  mul33 );

add0: adderInt generic map (n=>16) port map (clk, mul11, mul12, sum1);
add1: adderInt generic map (n=>16) port map (clk, sum1, mul13, sum2);
add2: adderInt generic map (n=>16) port map (clk, sum2, mul21, sum3);
add3: adderInt generic map (n=>16) port map (clk, sum3, mul22, sum4);
add4: adderInt generic map (n=>16) port map (clk, sum4, mul23, sum5);
add5: adderInt generic map (n=>16) port map (clk, sum5, mul31, sum6);
add6: adderInt generic map (n=>16) port map (clk, sum6, mul32, sum7);
add7: adderInt generic map (n=>16) port map (clk, sum7, mul33, sum8);

resultado <= conv_std_logic_vector(sum8, 32);

process (rst, clk)
begin
	if(rst = '0') then
		result <= (others =>'0');
	elsif (clk'event and clk='1') then
		if(resultado>255)then
			result<= (others=>'1');			
		elsif(resultado < 0) then
			result <= (others =>'0');
		else
			result <= resultado(7 downto 0);
		end if;
	end if;
end process;

END rtl;