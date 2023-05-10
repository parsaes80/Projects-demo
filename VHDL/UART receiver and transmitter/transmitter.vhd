library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity transmitter is 
  port (
    clk_enable   : in  std_logic;
    reset : in  std_logic;
    start : in  std_logic;
    data  : in  std_logic_vector(7 downto 0);
    tx    : out std_logic);
end transmitter;

architecture rtl of transmitter is

signal state,counter,ones : integer range 0 to 10:=0;
signal sdata : std_logic_vector(7 downto 0);

begin 

process (clk_enable,reset) 
begin 
if reset='1' then 
	state <= 0;
	
elsif rising_edge(clk_enable) then 
       case state is 
		when 0 => --idle state
                     tx<= '1';
			sdata <= data;
                     if start ='1' then
                             state<= 1;
                             
                     end if;
								
              when 1 => --start bit
                     tx<='0';
                     state<= 2;

              when 2 => -- send data 
                     tx<= sdata(counter);
                     counter<= counter+1;
                     if  data(counter) = '1'  then  --counter number of ones for the parity bit
                            ones <= ones+1;
                     end if;

                     if counter = 7 then --cheak if all data bits are done 
                            state <= 4;
                     else
                            state <= 2;
                     end if;
                     
              when 4 => -- parity bit 
                                         
                     counter <= 0;
                     if (ones mod 2)=1 then  -- ones have to be even
                            tx<= '1';
                     else 
                            tx<= '0';
                     end if; 
                     state <= 5;

              when 5 => --stop bit 1
                     tx <= '1';
                     state <= 6;
							
              when 6 => --stop bit 2
                     tx <= '1';
                     state <= 7;
                     ones <= 0;
							
              when 7 => 
                     tx <= '1';
                     if start<='1' then
                      state <= 7; --waiting for start to become '0'
                     else 
                      state <= 0; --back to state 0
                     end if;   
							
              when others=>
                     state<=0;  
	 end case;
	end if;
end process;
end rtl;


