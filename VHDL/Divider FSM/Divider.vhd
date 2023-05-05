LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.NUMERIC_STD.ALL;

entity divider is
   port ( clk : in std_logic;
		 dividend : in std_logic_vector(3 downto 0);
       divisor : in std_logic_vector(3 downto 0);
		 rst : in std_logic;
		 quotient : out std_logic_vector(3 downto 0);
       remainder : out std_logic_vector(3 downto 0)
		 );
end entity divider;


architecture Behavioral of divider is
signal currs, nexts : std_logic_vector(3 downto 0);
signal sor, quo : UNSIGNED (3 downto 0);
signal dent, edent : UNSIGNED (3 downto 0);
signal counter : integer range -1 to 3;
begin
		
		

process(currs)
--	variable vedent: UNSIGNED (3 downto 0);
--	variable vdent: UNSIGNED (3 downto 0);
	
	begin
	
		case currs is
		
			when "0000" =>  --start case
				sor<=  UNSIGNED(divisor);
				dent <= UNSIGNED(dividend);
				edent<= "0000";
				quo<= "0000"; 
				counter <=3;
				remainder<= "0000";	    	
				nexts <= "0001";

			when "0001" => -- shift

				--if counter<0 then	
					--nexts <= "0110";
				--else
					nexts <="0010";
				--end if;

				when "0010" =>  -- compare				
				--if counter>=0 then
				edent<= shift_left(edent,1); 
  		   	edent(0) <=dent(3);
				dent<= shift_left(dent,1);
				--end if;
				if edent < sor or sor <=0 then --when 0
					nexts <= "0011";
				else 
					nexts <="0100";     --when 1
				end if;
				
		  	 when "0011" => --when 0
				quo(counter) <= '0';
				counter<= counter - 1;
				nexts <="0111";
			
			when "0100" => --when 1
				edent <= edent - sor;
				quo(counter) <= '1';
				counter<= counter - 1;
				nexts <="0111";
				
			when "0111" =>
				if counter = -1 then
					nexts <= "0110";
				else
					nexts <= "0001";
				end if;
									
			when "0110" => --done
			  -- report "The value of 'quotient' is " & integer'image(to_integer(quo));
				--report "The value of 'remainder' is " & integer'image(to_integer(dent));
				
				quotient<= std_logic_vector(quo);
				remainder<= std_logic_vector(edent);
				nexts <= "0110";
									
			when others =>
			nexts <= "0000";
			
	end case;
	
		
end process;

process (clk, rst)   --register
	begin
		if (rst = '1') then
		 currs <= "0000";
			
		elsif (rising_edge(CLK)) then		
			currs <= nexts;
		end if;						
	
	end process;
	
end Behavioral;
