-- fft_pipeline_avalon_0.vhd

-- This file was auto-generated as part of a SOPC Builder generate operation.
-- If you edit it your changes will probably be lost.

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity fft_pipeline_avalon_0 is
	port (
		clk     : in  std_logic                     := '0';             --          clock.clk
		wr_data : in  std_logic_vector(31 downto 0) := (others => '0'); -- avalon_slave_0.writedata
		cs      : in  std_logic                     := '0';             --               .chipselect
		wr      : in  std_logic                     := '0';             --               .write
		rd      : in  std_logic                     := '0';             --               .read
		addr    : in  std_logic_vector(11 downto 0) := (others => '0'); --               .address
		rd_data : out std_logic_vector(31 downto 0);                    --               .readdata
		clr_n   : in  std_logic                     := '0';             --     reset_sink.reset
		counter : out std_logic_vector(9 downto 0);                     --    conduit_end.export
		tx_out  : out std_logic;                                        --               .export
		rx_in   : in  std_logic                     := '0'              --               .export
	);
end entity fft_pipeline_avalon_0;

architecture rtl of fft_pipeline_avalon_0 is
	component fft_pipeline is
		port (
			clk     : in  std_logic                     := 'X';             -- clk
			wr_data : in  std_logic_vector(31 downto 0) := (others => 'X'); -- writedata
			cs      : in  std_logic                     := 'X';             -- chipselect
			wr      : in  std_logic                     := 'X';             -- write
			rd      : in  std_logic                     := 'X';             -- read
			addr    : in  std_logic_vector(11 downto 0) := (others => 'X'); -- address
			rd_data : out std_logic_vector(31 downto 0);                    -- readdata
			clr_n   : in  std_logic                     := 'X';             -- reset
			counter : out std_logic_vector(9 downto 0);                     -- export
			tx_out  : out std_logic;                                        -- export
			rx_in   : in  std_logic                     := 'X'              -- export
		);
	end component fft_pipeline;

begin

	fft_pipeline_avalon_0 : component fft_pipeline
		port map (
			clk     => clk,     --          clock.clk
			wr_data => wr_data, -- avalon_slave_0.writedata
			cs      => cs,      --               .chipselect
			wr      => wr,      --               .write
			rd      => rd,      --               .read
			addr    => addr,    --               .address
			rd_data => rd_data, --               .readdata
			clr_n   => clr_n,   --     reset_sink.reset
			counter => counter, --    conduit_end.export
			tx_out  => tx_out,  --               .export
			rx_in   => rx_in    --               .export
		);

end architecture rtl; -- of fft_pipeline_avalon_0
