------- Main code: -----------------------
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;
USE ieee.std_logic_signed.all;
USE work.my_functions.all;
USE work.tipos.all;


 ------------------------------------------
ENTITY imageConvolution IS
generic (n: integer := 8);
PORT ( 
		isw: in std_logic_vector (17 downto 0);
		ikey: in std_logic_vector (3 downto 0);
		oledr: out std_logic_vector (17 downto 0);
		oledg: out std_logic_vector (8 downto 0);
		ohex0_d,ohex1_d,ohex2_d,ohex3_d,ohex4_d,ohex5_d,ohex6_d,ohex7_d: out std_logic_vector ( 6 downto 0);
		ohex0_dp,ohex1_dp,ohex2_dp,ohex3_dp,ohex4_dp,ohex5_dp,ohex6_dp,ohex7_dp: out std_logic 		
		); 
END imageConvolution;

ARCHITECTURE rtl OF imageConvolution IS

COMPONENT convolution IS
generic (n: integer := 8);
PORT ( 
		px: IN matriz9x9;
		clk, rst: IN STD_LOGIC;
		result: OUT std_logic_vector(2*n-1 DOWNTO 0)
		); 
END COMPONENT;
COMPONENT decod_hex IS
	PORT (	
			entrada	: IN STD_LOGIC_VECTOR(3 DOWNTO 0);
			saida	: OUT STD_LOGIC_VECTOR(6 DOWNTO 0)
		);
END COMPONENT;

signal test: matriz9x9:=(
("00001100","00100011","00000111"),
("01010000","01011100","00001100"),
("00101000","00000101","00000001")
);

signal clk, rst: std_logic;
signal res: std_logic_vector (15 downto 0);
signal resultado: std_logic_vector (15 downto 0);
begin

---test(0)(0) <= isw(7 downto 0);
--test(0)(1) <= isw(15 downto 8);

clk <= not ikey(0);
rst <= not ikey(1);
oledg(0) <= clk;
oledg(1) <= rst;

ic: convolution port map (test, clk, rst, res);

label1:	for i in 0 to resultado'LENGTH-1 generate
resultado(i) <= res(i);
end generate label1;

d0: decod_hex port map (resultado (15 downto 12), ohex3_d);
d1: decod_hex port map (resultado (11 downto 8), ohex2_d);
d2: decod_hex port map (resultado (7 downto 4), ohex1_d);
d3: decod_hex port map (resultado (3 downto 0), ohex0_d);


--apaga os pontos
ohex0_dp<='1';
ohex1_dp<='1';
ohex2_dp<='1';
ohex3_dp<='1';
ohex4_dp<='1';
ohex5_dp<='1';
ohex6_dp<='1';
ohex7_dp<='1'; 
end rtl;
