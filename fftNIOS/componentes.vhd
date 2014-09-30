---------------COMPONENTES----------------
Library IEEE ;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_SIGNED.ALL;
use work.tipos.all;
------------------------------------------

PACKAGE componentes IS

component fft_pipeline_8s IS PORT (
		clk, en, clr: IN std_logic;
		cpxIN0, cpxIN1: IN complex;
		cpxOUT0, cpxOUT1: out complex;
		enOUT: out std_logic;
		counter: out std_logic_vector( 9 downto 0)
		);
END component;

component mirror_ramdual IS
	PORT
	(
		clock		: IN STD_LOGIC  := '1';
		data		: IN STD_LOGIC_VECTOR (17 DOWNTO 0);
		rdaddress		: IN STD_LOGIC_VECTOR (9 DOWNTO 0);
		wraddress		: IN STD_LOGIC_VECTOR (9 DOWNTO 0);
		wren		: IN STD_LOGIC  := '0';
		q		: OUT STD_LOGIC_VECTOR (17 DOWNTO 0)
	);
END component;

component mirror_rom IS
	PORT
	(
		address		: IN STD_LOGIC_VECTOR (9 DOWNTO 0);
		clock		: IN STD_LOGIC  := '1';
		q		: OUT STD_LOGIC_VECTOR (17 DOWNTO 0)
	);
END component;

component ram2dual_imag IS
	PORT
	(
		clock		: IN STD_LOGIC  := '1';
		data		: IN STD_LOGIC_VECTOR (17 DOWNTO 0);
		rdaddress		: IN STD_LOGIC_VECTOR (8 DOWNTO 0);
		wraddress		: IN STD_LOGIC_VECTOR (8 DOWNTO 0);
		wren		: IN STD_LOGIC  := '0';
		q		: OUT STD_LOGIC_VECTOR (17 DOWNTO 0)
	);
END component;

component ram2dual_real IS
	PORT
	(
		clock		: IN STD_LOGIC  := '1';
		data		: IN STD_LOGIC_VECTOR (17 DOWNTO 0);
		rdaddress		: IN STD_LOGIC_VECTOR (8 DOWNTO 0);
		wraddress		: IN STD_LOGIC_VECTOR (8 DOWNTO 0);
		wren		: IN STD_LOGIC  := '0';
		q		: OUT STD_LOGIC_VECTOR (17 DOWNTO 0)
	);
END component;

component ram1dual_imag IS
	PORT
	(
		clock		: IN STD_LOGIC  := '1';
		data		: IN STD_LOGIC_VECTOR (17 DOWNTO 0);
		rdaddress		: IN STD_LOGIC_VECTOR (8 DOWNTO 0);
		wraddress		: IN STD_LOGIC_VECTOR (8 DOWNTO 0);
		wren		: IN STD_LOGIC  := '0';
		q		: OUT STD_LOGIC_VECTOR (17 DOWNTO 0)
	);
END component;

component ram1dual_real IS
	PORT
	(
		clock		: IN STD_LOGIC  := '1';
		data		: IN STD_LOGIC_VECTOR (17 DOWNTO 0);
		rdaddress		: IN STD_LOGIC_VECTOR (8 DOWNTO 0);
		wraddress		: IN STD_LOGIC_VECTOR (8 DOWNTO 0);
		wren		: IN STD_LOGIC  := '0';
		q		: OUT STD_LOGIC_VECTOR (17 DOWNTO 0)
	);
END component;

component memory_reader is
generic(stages: integer:=10);
port (   
		clock, start: in std_logic;
		--Sinais para as memoria RAM		
		addr_ram_ex: out std_logic_vector ( 9 downto 0);				
		--Sinais para o mux de saida de dados
		sel_mux: out std_logic_vector( 2 downto 0);
		--Sinais para o controlador UART
		send: out std_logic;
		sent: in std_logic						
);
end component;

component uart_controller is 
port(		
		Clk_50, reset: in std_logic;
		dado: in std_logic_vector( 31 downto 0);
		send: in std_logic;
		sent: out std_logic:='1';		
		UART_Txd: out std_logic;
		UART_Rxd: in std_logic
		);
end component;

component fft_pipeline_controller2 is
generic(stages: integer:=10);
port (   
		clock, start: in std_logic;
		--Sinais para a memoria ROM
		addr_rom: out std_logic_vector (9 downto 0);
		--Sinais para o pipeline
		fft_en_in: in std_logic;
		clk_pipeline, fft_clr, fft_en: out std_logic;
		--Sinais para o banco de memorias
		addr_ram12: out std_logic_vector ( 9 downto 0);
		wen_ram12: out std_logic;
		addr_ram34: out std_logic_vector ( 9 downto 0);
		wen_ram34: out std_logic;
		--Sinais para o memory reader
		finished: out std_logic					
);
end component;

component fft_pipeline_controller is
port (   
		clock, start: in std_logic;
		--Sinais para a memoria ROM
		addr_rom: out std_logic_vector (9 downto 0);
		--Sinais para o pipeline
		fft_en_in: in std_logic;
		clk_pipeline, fft_clr, fft_en: out std_logic;
		--Sinais para o banco de memorias
		addr_ram12: out std_logic_vector ( 9 downto 0);
		wen_ram12: out std_logic;
		addr_ram34: out std_logic_vector ( 9 downto 0);
		wen_ram34: out std_logic;
		--Sinais para o mux de saida de dados
		sel_mux: out std_logic_vector( 1 downto 0);
		--Sinais para o controlador UART
		send: out std_logic;
		sent: in std_logic						
);
end component;

COMPONENT mux4_1 IS
	PORT
	(
		data0x		: IN STD_LOGIC_VECTOR (17 DOWNTO 0);
		data1x		: IN STD_LOGIC_VECTOR (17 DOWNTO 0);
		data2x		: IN STD_LOGIC_VECTOR (17 DOWNTO 0);
		data3x		: IN STD_LOGIC_VECTOR (17 DOWNTO 0);
		data4x		: IN STD_LOGIC_VECTOR (17 DOWNTO 0);
		sel		: IN STD_LOGIC_VECTOR (2 DOWNTO 0);
		result		: OUT STD_LOGIC_VECTOR (17 DOWNTO 0)
	);
END COMPONENT;

COMPONENT fft_pipeline_10s IS PORT (
		clk, en, clr: IN std_logic;
		cpxIN0, cpxIN1: IN complex;
		cpxOUT0, cpxOUT1: out complex;
		enOUT: out std_logic;
		counter: out std_logic_vector( 9 downto 0)
		);
END COMPONENT;

COMPONENT fft_pipeline_3s IS PORT (
		clk, en, clr: IN std_logic;
		cpxIN0, cpxIN1: IN complex;
		cpxOUT0, cpxOUT1: out complex;
		enOUT: out std_logic;
		counter: out std_logic_vector( 9 downto 0)
		);
END COMPONENT;

COMPONENT ram1_real IS
	PORT
	(
		address		: IN STD_LOGIC_VECTOR (9 DOWNTO 0);
		clock		: IN STD_LOGIC  := '1';
		data		: IN STD_LOGIC_VECTOR (17 DOWNTO 0);
		wren		: IN STD_LOGIC ;
		q		: OUT STD_LOGIC_VECTOR (17 DOWNTO 0)
	);
END COMPONENT;
COMPONENT ram3_real IS
	PORT
	(
		address		: IN STD_LOGIC_VECTOR (9 DOWNTO 0);
		clock		: IN STD_LOGIC  := '1';
		data		: IN STD_LOGIC_VECTOR (17 DOWNTO 0);
		wren		: IN STD_LOGIC ;
		q		: OUT STD_LOGIC_VECTOR (17 DOWNTO 0)
	);
END COMPONENT;
COMPONENT ram2_imag IS
	PORT
	(
		address		: IN STD_LOGIC_VECTOR (9 DOWNTO 0);
		clock		: IN STD_LOGIC  := '1';
		data		: IN STD_LOGIC_VECTOR (17 DOWNTO 0);
		wren		: IN STD_LOGIC ;
		q		: OUT STD_LOGIC_VECTOR (17 DOWNTO 0)
	);
END COMPONENT;
COMPONENT ram4_imag IS
	PORT
	(
		address		: IN STD_LOGIC_VECTOR (9 DOWNTO 0);
		clock		: IN STD_LOGIC  := '1';
		data		: IN STD_LOGIC_VECTOR (17 DOWNTO 0);
		wren		: IN STD_LOGIC ;
		q		: OUT STD_LOGIC_VECTOR (17 DOWNTO 0)
	);
END COMPONENT;

COMPONENT fft_rom IS
	PORT
	(
		address		: IN STD_LOGIC_VECTOR (9 DOWNTO 0);
		clock		: IN STD_LOGIC  := '1';
		q		: OUT STD_LOGIC_VECTOR (17 DOWNTO 0)
	);
END COMPONENT;

component w_generator is
generic (stage: integer:= 4);  
port(   clock, en, clr: in std_logic; 	
		  w: out complex
        );
end component;

component fft_pipeline_stage_w is
generic (stage: integer:= 4
);
port(   clock, en, clr: in std_logic; 
		  din0, din1 : in complex;		--std_logic_vector(8 downto 0);--  		 
		  dout0, dout1: out complex	:=(others=>(others=>'0'));	 --std_logic_vector(8 downto 0) --         
       -- s1, s2: out complex;
		 -- w_out: out complex;
		  en_out: out std_logic:='0' --saida do enable
		  );
end component;

component fft_pipeline_stage is
generic (stage: integer:= 4);
port(   clock: in std_logic; 
		  din0, din1 : in complex;		--std_logic_vector(8 downto 0);--  
		  w: in complex;
		  dout0, dout1: out complex	:=(others=>(others=>'0'))	 --std_logic_vector(8 downto 0) --         
        );
end component;

component regcomplex is
port(   clock, clr: in std_logic; 
		  data_in: in complex;		--std_logic_vector(8 downto 0);--  
		  data_out: out complex	:=(others=>(others=>'0'))	 --std_logic_vector(8 downto 0) --         
        );
end component;

component staged_mux is
generic (stage: integer:= 2
			
			);
port(   clock, en, clr: in std_logic; 
		  a, b: in complex;		--std_logic_vector(8 downto 0);--  
		  data_out: out complex	:=(others=>(others=>'0'))	 --std_logic_vector(8 downto 0) --    
		 
        );
end component;



component bit_fifo_N is
generic (size: integer:= 4);
port(   clock, en, clr: in std_logic; 
		  data_in: in std_logic;
		 -- w_en: out std_logic; 
		  data_out: out std_logic
        );
end component;

component fifo_N is
generic (size: integer:= 4);
port(   clock, en, clr: in std_logic; 
		  data_in: in complex;		  
		  data_out: out complex	:=(others=>(others=>'0'))	          
        );
end component;

component controleFFT is
port(   clk, start : in std_logic;
		  --RAM de dados
		  endereco_ram: out std_logic_vector(4 downto 0):="00000";
		  rw: out std_logic:='0';
		  --Registrador de entrada de dados
		  sel_reg_in: out std_logic_vector(2 downto 0):="000"; 
		  en_reg_in: out std_logic:='0';
		  --Seletor do mux
		  sel_mux: out std_logic_vector(1 downto 0):="00";
		  --Habilita registrador entrada e saida de dados na fft
		  en_reg_in_fft, en_reg_out_fft: out std_logic:='0';
		  --Seletor de W
		  sel_w: out std_logic_vector(1 downto 0):="00";
		  --Debug do estado
		  estado: out std_logic_vector(3 downto 0):="0000"		
        );
end component;

COMPONENT recDIF8 is
port(   x : in comp_array8; --input signals in time domain
		  w : in comp_array4;
        y : out comp_array8  --output signals in frequency domain
        );
end COMPONENT;

component reg8complex is
port(   en: std_logic;
		  clock: in std_logic; 
		  data_in: in comp_array8;		  
        data_out : out comp_array8  
        );
end component;

component muxDIF is
port(   sel : in std_logic_vector(1 downto 0);
		  x: in comp_array8;
		  x2: in comp_array8;
		  y: out comp_array8        
        );
end component;


component muxWDIF is
port(   sel : in std_logic_vector(1 downto 0);		  
        w : out comp_array4  --output signals in frequency domain
        );
end component;

COMPONENT ram_dados IS
	PORT
	(
		address		: IN STD_LOGIC_VECTOR (4 DOWNTO 0);
		clock		: IN STD_LOGIC  := '1';
		data		: IN STD_LOGIC_VECTOR (8 DOWNTO 0);
		wren		: IN STD_LOGIC ;
		q		: OUT STD_LOGIC_VECTOR (8 DOWNTO 0)
	);
END COMPONENT;

COMPONENT data_in_regs16 is
port(   sel : in std_logic_vector(3 downto 0); 
		  data: in std_logic_vector(8 downto 0);
		  clock: in std_logic;
        y : out comp_array16  
        );
end COMPONENT;

COMPONENT data_out_regs16 is
port(   sel : in std_logic_vector(3 downto 0); 
		  data: in comp_array16;
		  clock: in std_logic;
        y : out complex
        );
end COMPONENT;

COMPONENT data_out_regs is
port(   sel : in std_logic_vector(2 downto 0); 
		  data: in comp_array8;
		  clock: in std_logic;
        y : out complex
        );
end COMPONENT;

COMPONENT data_in_regs is
port(   sel : in std_logic_vector(2 downto 0); 
		  data: in std_logic_vector(8 downto 0);
		  clock, en: in std_logic;
        y : out comp_array8  
        );
end COMPONENT;

COMPONENT multCPX IS 
GENERIC (n: integer := 9);
PORT (
		x, y: IN COMPLEX;
		z: OUT COMPLEX
		);
END COMPONENT;

COMPONENT subCPX IS 
GENERIC (n: integer := 9);
PORT (
		x, y: IN COMPLEX;
		z: OUT COMPLEX
		);
END COMPONENT;

COMPONENT somaCPX IS 
GENERIC (n: integer := 9);
PORT (
		x, y: IN COMPLEX;
		z: OUT COMPLEX
		);
END COMPONENT;

COMPONENT fftDIF8 is
port(   x : in comp_array8; --input signals in time domain
        y : out comp_array8  --output signals in frequency domain
        );
end COMPONENT;

COMPONENT fft8 is
port(   x : in comp_array8; --input signals in time domain
        y : out comp_array8  --output signals in frequency domain
        );
end COMPONENT;

COMPONENT fft16 is
port(   x : in comp_array16; --input signals in time domain
        y : out comp_array16  --output signals in frequency domain
        );
end component;


COMPONENT decod_hex IS
	PORT (	
			entrada	: IN STD_LOGIC_VECTOR(3 DOWNTO 0);
			saida	: OUT STD_LOGIC_VECTOR(6 DOWNTO 0)
		);
END COMPONENT;

COMPONENT butterflyDIF is 
   port(
      s1,s2 : in complex;     --inputs
      w :in complex;      		-- twiddle
      g1,g2 :out complex      -- outputs
   );
end COMPONENT;

COMPONENT butterfly is 
   port(
      s1,s2 : in complex;     --inputs
      w :in complex;      		-- twiddle
      g1,g2 :out complex      -- outputs
   );
end COMPONENT;

END componentes;