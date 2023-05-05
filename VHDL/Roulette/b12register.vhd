library ieee;
use ieee.std_logic_1164.all;

entity b12register is 
port (data_in :in std_logic_vector(11 downto 0);
		resetb : in STD_LOGIC;
		slow_clock : in STD_LOGIC;
		saved_data: out std_logic_vector(11 downto 0));
		end entity;
		
architecture latch of b12register is

begin

process (slow_clock,resetb)
begin
if resetb= '1' then 
	saved_data<= "000000100000"; --32
	elsif rising_edge (slow_clock) then 
		saved_data<=data_in;
	
	end if;
end process;

end architecture;