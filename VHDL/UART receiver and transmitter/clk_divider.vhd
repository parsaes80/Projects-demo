library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


entity clk_divider is

	port(
		clk	: in std_logic;
		reset	: in std_logic;
		enable: in std_logic;	
		clkout: out std_logic
	 );
	 
end entity;


architecture behaviour of clk_divider is 

 signal counter : unsigned (3 downto 0):="0000";
 signal counter_tick : std_logic :='0';
 
begin 

	process(clk)
	
	begin
	
		if (rising_edge(clk)) then
			if (reset='1') then
			  counter<="0000";
			 elsif(enable='1') then 
					if(counter=15) then
						counter<="0000";
					else
						counter<=counter+1;
					end if;
				end if;
			end if;
	 end process;
	
	counter_tick<='1' when counter=1;
	
	process(clk)
	
	begin 
	
		if (rising_edge(clk)) then
			clkout<=(counter_tick and enable);
		end if;
	end process;
	
	
end behaviour;


