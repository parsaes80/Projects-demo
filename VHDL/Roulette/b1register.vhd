library ieee;
use ieee.std_logic_1164.all;



entity b1register is 
port (	data_in :in STD_LOGIC;
		resetb : in STD_LOGIC;
		slow_clock : in STD_LOGIC;
		saved_data: out STD_LOGIC);
	end entity;
		
architecture latch of b1register is

begin

process (slow_clock, resetb)
    begin
        if resetb = '0' then
            saved_data <= '0'; -- Asynchronous reset
        elsif rising_edge(slow_clock) then
            saved_data <= data_in;
        end if;
    end process;

end architecture;