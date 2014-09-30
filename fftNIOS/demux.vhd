LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY demux IS GENERIC (n: integer:=4)
PORT (
		sel: in std_logic_vector(n-1 downto 0);
		d: in std_logic;
		q: out std_logic_vector( (n*n)-1 downto 0)
		);
END demux;

ARCHITECTURE comb OF demux IS
BEGIN

	q<= ((n*n-1)=>d, others=>'0');

END comb;
			