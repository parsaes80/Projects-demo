library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity receiver is

    port (
       
        reset          	: in  std_logic; 
        clk_enable  	: in  std_logic; 
        received_data   : in  std_logic;
        receiver_output : out std_logic_vector(7 downto 0); 
        output_valid    : out std_logic; 
        reqtosend   	: out std_logic  
    );
end entity;

architecture rtl of receiver is

     signal data_reg     : std_logic_vector(7 downto 0);	
	 signal   parity : std_logic;
     signal counter      : integer range 0 to 10:=0;
	 type state_type is (init_state, start_bit_state, data_bits_state, parity_bit_state, stop_bit_state1, stop_bit_state2, done_state);
     signal state : state_type;
    

begin

--state machine prcoess


    process (received_data, clk_enable)
    variable ones, i: integer range 0 to 8;
    begin
    
 

    if (reset = '1') then
        state <= init_state;

    elsif (rising_edge(clk_enable)) then
        case state is

            when init_state =>
                reqtosend<='1';

                if (received_data = '0') then
                    state <= start_bit_state;
                else
                    state <= init_state;
                end if;
						
						
            
				
			when start_bit_state => --waiting for 

                reqtosend<='0';
                data_reg(counter) <= received_data;
                counter<= counter+1;
                state <= data_bits_state;
                

            when data_bits_state =>

               
                  data_reg(counter) <= received_data;
                  counter<= counter+1;

                  if counter = 7 then --cheak if all data bits are done 
                            state <= parity_bit_state;
                     else
                            state <= data_bits_state;
                     end if;
                					

            when parity_bit_state =>
					counter <= 0; 
					parity <= received_data;
					state <= stop_bit_state1;
					

            when stop_bit_state1 => 
                
               state <= stop_bit_state2;
               			
            when stop_bit_state2 =>  --error  cheaking with the parity
                ones:= 0;
                for i in 0 to  7 loop 
                    if data_reg(i) = '1' then 
                        ones := ones +1;
                    end if;
				end loop;
                
                if (ones mod 2) = 0 then
                   
                    state <= done_state;
                else
                    state <= init_state;
                  
                end if;

            when done_state => 
                output_valid<='1';
                state <= done_state;
					 receiver_output<= data_reg;

            when others =>
				state<=init_state;
				
				
        end case;
    end if;
    end process;

 end rtl;