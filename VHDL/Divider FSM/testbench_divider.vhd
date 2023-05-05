library ieee;
use ieee.std_logic_1164.all;

entity testbench_divider is
end entity;

architecture sim of testbench_divider is

  -- Component declaration for the divider entity
  component divider is
    port (
      clk       : in  std_logic;
      dividend  : in  std_logic_vector(3 downto 0);
      divisor   : in  std_logic_vector(3 downto 0);
      rst       : in  std_logic;
      quotient  : out std_logic_vector(3 downto 0);
      remainder : out std_logic_vector(3 downto 0)
    );
  end component;

  -- Testbench signals
  signal clk       : std_logic ;
  signal dividend  : std_logic_vector(3 downto 0);
  signal divisor   : std_logic_vector(3 downto 0);
  signal rst       : std_logic;
  signal quotient  : std_logic_vector(3 downto 0);
  signal remainder : std_logic_vector(3 downto 0);

begin

  -- Instantiate the divider entity
  dut : divider
    port map (
      clk       => clk,
      dividend  => dividend,
      divisor   => divisor,
      rst       => rst,
      quotient  => quotient,
      remainder => remainder
    );

clkp: process
  constant clk_off_period :TIME:= 5 ns;
  constant clk_on_period:TIME:= 5 ns;
    begin 
    clk<= '0';
    wait for clk_off_period;
    clk <= '1';
    wait for clk_on_period;
  end process;



  -- Stimulus process
  stim_proc : process
  begin
    -- Apply reset
    rst <= '1';
    wait for 10 ns;
    rst <= '0';

    -- Test case 1: divide 8 by 2 (expect quotient=4, remainder=0)
    dividend <= "1000";
    divisor <= "0010";
    wait for 200 ns;
    assert (quotient = "0100" and remainder = "0000")
      report "Test case 1 failed!" severity error;
	
	 rst <= '1';
    wait for 10 ns;
    rst <= '0';
	 
    -- Test case 2: divide 7 by 2 (expect quotient=3, remainder=1)
    dividend <= "0111";
    divisor <= "0010";
    wait for 200 ns;
    assert (quotient = "0011" and remainder = "0001")
      report "Test case 2 failed!" severity error;
	
	 rst <= '1';
    wait for 10 ns;
    rst <= '0';
	 
    -- Test case 3: divide 4 by 0 (expect quotient=0000, remainder=0100)
    dividend <= "0100";
    divisor <= "0000";
    wait for 200 ns;
    assert (quotient = "0000" and remainder = "0100")
      report "Test case 3 failed!" severity error;
		
	 rst <= '1';
    wait for 10 ns;
    rst <= '0';
	 
    -- Test case 4: divide 3 by 3 (expect quotient=0001, remainder=0000)
    dividend <= "0011";
    divisor <= "0011";
    wait for 200 ns;
    assert (quotient = "0001" and remainder = "0000")
      report "Test case 4 failed!" severity error;
	
	 rst <= '1';
    wait for 10 ns;
    rst <= '0';
	 
    -- Test case 5: divide 2 by 4 (expect quotient=0000, remainder=0010)
    dividend <= "0010";
    divisor <= "0100";
    wait for 200 ns;
    assert (quotient = "0000" and remainder = "0010")
      report "Test case 5 failed!" severity error; 

    report "All Tests are Done";
	end process;
	

end architecture;	