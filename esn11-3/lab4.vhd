LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;

entity lab4 is
port(
            reset          : in  std_logic ;
            clk                : in  std_logic  ;  
				button	 : in  std_logic  ;
				SEG1   : out std_logic_vector(7 downto 0);        --  seg1.export
				SEG2   : out std_logic_vector(7 downto 0);        --  seg2.export
				SEG3   : out std_logic_vector(7 downto 0);         --  seg3.export
				SEG4   : out std_logic_vector(7 downto 0);        --  seg4.export
				SEG0   : out std_logic_vector(7 downto 0);         --  seg0.export
				opencores_i2c_0_export_0_scl_pad_io		: inout std_logic;
				opencores_i2c_0_export_0_sda_pad_io		: inout std_logic
				);

end entity lab4;



architecture rtl of lab4 is

	component labi2c is
		port (
			clk_clk                             : in    std_logic                    := 'X'; -- clk
			opencores_i2c_0_export_0_scl_pad_io : inout std_logic                    := 'X'; -- scl_pad_io
			opencores_i2c_0_export_0_sda_pad_io : inout std_logic                    := 'X'; -- sda_pad_io
			reset_reset_n                       : in    std_logic                    := 'X'; -- reset_n
			button_export                       : in    std_logic                    := 'X'; -- export
			seg0_export                         : out   std_logic_vector(3 downto 0);        -- export
			seg1_export                         : out   std_logic_vector(3 downto 0);        -- export
			seg2_export                         : out   std_logic_vector(3 downto 0);        -- export
			seg3_export                         : out   std_logic_vector(3 downto 0);        -- export
			seg4_export                         : out   std_logic_vector(3 downto 0)        -- export
		);
	end component labi2c;
	
		component BCD7SEG is
		port (
			input : in std_logic_vector(3 downto 0) := (others => 'X'); 
			output : out std_logic_vector(7 downto 0)
		);
	end component BCD7SEG;
	
signal segment0 : std_logic_vector(3 downto 0);	
signal segment1 : std_logic_vector(3 downto 0);
signal segment2 : std_logic_vector(3 downto 0);
signal segment3 : std_logic_vector(3 downto 0);
signal segment4 : std_logic_vector(3 downto 0);

begin

	u0 : component labi2c
		port map (
			clk_clk       => clk,       --   clk.clk
			reset_reset_n => reset, -- reset.reset_n
			button_export => button,  -- button.export
			opencores_i2c_0_export_0_scl_pad_io => opencores_i2c_0_export_0_scl_pad_io, -- opencores_i2c_0_export_0.scl_pad_io
			opencores_i2c_0_export_0_sda_pad_io => opencores_i2c_0_export_0_sda_pad_io, --  .sda_pad_io
			seg1_export   => segment1,    --  seg1.export
			seg2_export   => segment2,   --  seg2.export
			seg3_export   => segment3,    --  seg3.export
			seg4_export   => segment4,    --  seg4.export
			seg0_export   => segment0    --  seg0.export
		);
		
	u1 : component BCD7SEG
		port map (
			input => segment0,
			output => SEG0
		);

	u2 : component BCD7SEG
		port map (
			input => segment1,
			output => SEG1
		);
		
	u3 : component BCD7SEG
		port map (
			input => segment2,
			output => SEG2
		);
	u4 : component BCD7SEG
		port map (
			input => segment3,
			output => SEG3
		);
	
	u5 : component BCD7SEG
		port map (
			input => segment4,
			output => SEG4
		);
		
 END ARCHITECTURE ;
