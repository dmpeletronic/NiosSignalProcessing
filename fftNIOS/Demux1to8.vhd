LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY Demux1to8 IS
	PORT (
		sel : in STD_LOGIC_VECTOR(3 DOWNTO 0);
		c : in STD_LOGIC;
		res : out STD_LOGIC_VECTOR(8 DOWNTO 0)
	);
END ENTITY;

ARCHITECTURE Demux_comp OF Demux1to8 IS
BEGIN

PROCESS (sel, c)
begin
	res<=(others=>'0');
	IF (sel="0000") THEN
	res(0) <= c;
	ELSIF (sel="0001") THEN
	res(1) <= c;
	ELSIF (sel="0010") THEN
	res(2) <= c;
	ELSIF (sel="0011") THEN
	res(3) <= c;
	ELSIF (sel="0100") THEN
	res(4) <= c;
	ELSIF (sel="0101") THEN
	res(5) <= c;
	ELSIF (sel="0110") THEN
	res(6) <= c;
	ELSIF (sel="0111") THEN
	res(7) <= c;
	ELSIF (sel="1000") THEN
	res(8) <= c;	
	ELSE
	res <= (others=>'0');
	END IF;
END PROCESS;
END Demux_comp;