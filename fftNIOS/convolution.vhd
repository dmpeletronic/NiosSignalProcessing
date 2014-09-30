LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;
USE ieee.std_logic_signed.all;
USE work.my_functions.all;
USE work.tipos.all;

ENTITY convolution IS
PORT	(
		sel: in std_logic_vector(3 downto 0);
		pixel: in std_logic_vector(7 downto 0);
		clk, rst: in std_logic;
		out_pixel32: out std_logic_vector(31 downto 0);
		out_pixel8: out std_logic_vector(7 downto 0)
		);
END ENTITY;

ARCHITECTURE structure OF convolution IS

COMPONENT sobel IS
generic (n: integer := 8);
PORT (
		--filter: IN matriz9x9;
		px: IN matriz9x9;
		clk, rst: IN STD_LOGIC;
		result: OUT std_logic_vector(n-1 DOWNTO 0)
		); 
END COMPONENT;
COMPONENT sobelV IS
generic (n: integer := 8);
PORT (
		--filter: IN matriz9x9;
		px: IN matriz9x9;
		clk, rst: IN STD_LOGIC;
		result: OUT std_logic_vector(n-1 DOWNTO 0)
		); 
END COMPONENT;

COMPONENT reg IS GENERIC (n: integer:=8);
PORT (
		d: in std_logic_vector(n-1 downto 0);
		clk, rst, en: in std_logic;
		q: out std_logic_vector(n-1 downto 0)
		);
END COMPONENT;

COMPONENT Demux1to8 IS
	PORT (
		sel : in STD_LOGIC_VECTOR(3 DOWNTO 0);
		c : in STD_LOGIC;
		res : out STD_LOGIC_VECTOR(8 DOWNTO 0)
	);
END COMPONENT;

COMPONENT adder IS
GENERIC (n: INTEGER := 8);
PORT ( 
	clk: in std_logic;
		a, b: IN std_logic_vector(n-1 DOWNTO 0);
		
		add: OUT std_logic_vector(n-1 DOWNTO 0)
); 
END COMPONENT;

--CONSTANT fH: matriz9x9:= (
--("00000001","00000010","00000001"),
--("00000000","00000000","00000000"),
--("11111111","11111110","11111111")
--);



--CONSTANT fV: matriz9x9:= (
--("00000001","00000000","11111111"),
--("00000010","00000000","11111110"),
--("00000001","00000000","11111111")
--);

signal d: std_logic:='1';
signal enable: std_logic_vector(8 downto 0);
signal p0,p1,p2,p3,p4,p5,p6,p7,p8: std_logic_vector(7 downto 0);
signal matrizPixel: matriz9x9;
signal resultado8: std_logic_vector(7 downto 0);
signal resultado16: std_logic_vector(15 downto 0);
signal resultadoH, resultadoV, res: std_logic_vector(7 downto 0):= (others=>'0');
signal resultado32, r, r32: std_logic_vector(31 downto 0);

BEGIN

d0: demux1to8 port map(sel, d, enable);
r0: reg port map (pixel, clk, rst, enable(0), p0);
r1: reg port map (pixel, clk, rst, enable(1), p1);
r2: reg port map (pixel, clk, rst, enable(2), p2);
r3: reg port map (pixel, clk, rst, enable(3), p3);
r4: reg port map (pixel, clk, rst, enable(4), p4);
r5: reg port map (pixel, clk, rst, enable(5), p5);
r6: reg port map (pixel, clk, rst, enable(6), p6);
r7: reg port map (pixel, clk, rst, enable(7), p7);
r8: reg port map (pixel, clk, rst, enable(8), p8);

matrizPixel(0)(0) <= p0;
matrizPixel(0)(1) <= p1;
matrizPixel(0)(2) <= p2;
matrizPixel(1)(0) <= p3;
matrizPixel(1)(1) <= p4;
matrizPixel(1)(2) <= p5;
matrizPixel(2)(0) <= p6;
matrizPixel(2)(1) <= p7;
matrizPixel(2)(2) <= p8;

s0: sobel port map(matrizPixel, clk, rst, resultadoH);
s1: sobelV port map(matrizPixel, clk, rst, resultadoV);
add: adder generic map(n=>8) port map(clk, resultadoH, resultadoV, res);
--r <= conv_std_logic_vector(res, 32);
rr: reg generic map(n=>8) port map(res, clk, rst, '1', resultado8);


--resultado8 <= resultado16 (7 downto 0);
resultado32(7 downto 0)  <= resultado8 (7 downto 0);
resultado32(15 downto 8) <= resultado8 (7 downto 0);
resultado32(23 downto 16)<= resultado8 (7 downto 0);

out_pixel8 <= resultado8;
out_pixel32 <= resultado32;


END structure;
		