----------Package----------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_SIGNED.ALL;
--use work.constantes.all;
--------------------------------
PACKAGE tipos IS
	TYPE vetor16bits IS ARRAY ( NATURAL range <>) OF signed (15 downto 0) ;
	TYPE vetor32bits IS ARRAY ( NATURAL range <>) OF signed (31 downto 0) ;		

	type complex is 
		record
			r : std_logic_vector(17 downto 0);
			i : std_logic_vector(17 downto 0);
		end record;
--	type comp_array2 is array (1 downto 0) of complex;		
--	type comp_array4 is array (3 downto 0) of complex;
--	type comp_array8 is array (7 downto 0) of complex;
--	type comp_array16 is array (15 downto 0) of complex;
--	type comp_array32 is array (31 downto 0) of complex;
--	type comp_array64 is array (63 downto 0) of complex;
--	type comp_array128 is array (127 downto 0) of complex;
--	type comp_array256 is array (255 downto 0) of complex;
--	type comp_array512 is array (511 downto 0) of complex;
--	type comp_array1024 is array (1023 downto 0) of complex;
	type comp_array2 is array (0 to 1) of complex;
	type comp_array4 is array (0 to 3) of complex;
	type comp_array8 is array (0 to 7) of complex;
	type comp_array16 is array (0 to 15) of complex;
	type comp_array32 is array (0 to 31) of complex;
	type comp_array64 is array (0 to 63) of complex;
	type comp_array128 is array (0 to 127) of complex;
	type comp_array256 is array (0 to 255) of complex;
	type comp_array512 is array (0 to 511) of complex;
	type comp_array1024 is array (0 to 1023) of complex;

	function add (n1,n2 : complex) return complex;
	function sub (n1,n2 : complex) return complex;
	function mult (n1,n2 : complex) return complex;

end tipos; 
-------------------------------
package body tipos is 

--addition of complex numbers
function add (n1,n2 : complex) return complex is

variable sum : complex;

begin 
sum.r:=n1.r + n2.r;
sum.i:=n1.i + n2.i;
return sum;
end add;

--subtraction of complex numbers.
function sub (n1,n2 : complex) return complex is

variable diff : complex;

begin 
diff.r:=n1.r - n2.r;
diff.i:=n1.i - n2.i;
return diff;
end sub;

--multiplication of complex numbers.
function mult (n1,n2 : complex) return complex is

variable prod : complex;
variable r_temp, i_temp: std_logic_vector (17 downto 0);

begin 

r_temp:=(n1.r * n2.r) - (n1.i * n2.i);
i_temp:=(n1.r * n2.i) + (n1.i * n2.r);
prod.r := r_temp ( 15 downto 7 );
prod.i := i_temp ( 15 downto 7 );

return prod;
end mult;

end tipos;
