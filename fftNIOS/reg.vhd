LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY reg IS GENERIC (n: integer:=8);
PORT (
		d: in std_logic_vector(n-1 downto 0);
		clk, rst, en: in std_logic;
		q: out std_logic_vector(n-1 downto 0)
		);
END reg;

ARCHITECTURE seq OF reg IS
BEGIN

PROCESS (rst, clk)
BEGIN
	IF(rst='0')THEN
		q<=(others=>'0');
	ELSIF(en='1') THEN
		IF(clk'event and clk='1') THEN
			q<= d;
		END IF;
	END IF;	
END PROCESS;

END seq;
			