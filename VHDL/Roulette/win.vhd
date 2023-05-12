LIBRARY IEEE;

USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.NUMERIC_STD.ALL;
 
LIBRARY WORK;
USE WORK.ALL;

--------------------------------------------------------------
--
--  This block determines
--  whether each of the 3 bets is a winner.  As described in the lab
--  handout, the first bet is a "straight-up" bet, teh second bet is 
--  a colour bet, and the third bet is a "dozen" bet.

---------------------------------------------------------------

ENTITY win IS
	PORT(spin_result_latched : in unsigned(5 downto 0);  -- result of the spin (the winning number)
             bet1_value : in unsigned(5 downto 0); -- value for bet 1
             bet2_colour : in std_logic;  -- colour for bet 2
             bet3_dozen : in unsigned(1 downto 0);  -- dozen for bet 3
             bet1_wins : out std_logic;  -- whether bet 1 is a winner
             bet2_wins : out std_logic;  -- whether bet 2 is a winner
             bet3_wins : out std_logic); -- whether bet 3 is a winner
END win;


ARCHITECTURE behavioural OF win IS
BEGIN
--  Your code goes here

process (spin_result_latched,bet1_value,bet2_colour,bet3_dozen)
BEGIN
    if spin_result_latched = bet1_value then
        bet1_wins<='1';
    else 
	bet1_wins<='0';
    end if;
end process;

process (spin_result_latched,bet1_value,bet2_colour,bet3_dozen)
variable x : integer range 0 to 37 ;
BEGIN
x := to_integer(spin_result_latched);
case x is    
   when 1 | 3 | 5 | 7 | 9 | 12 | 14 | 16 | 18 | 19 | 21 | 23 | 25 | 27 | 30 | 32 | 34 | 36  =>
    
    if bet2_colour = '1' then
        bet2_wins<='1';
    else 
        bet2_wins<='0';
    end if;
  when 0 =>
    bet2_wins <= '0';
  when others =>
    if bet2_colour = '0' then
        bet2_wins<='1';
    else 
        bet2_wins<='0';
    end if;
end case;
end process;


process (spin_result_latched,bet1_value,bet2_colour,bet3_dozen)
BEGIN
if spin_result_latched = 0 then
    bet3_wins <='0';
elsif spin_result_latched<13 then 

    if bet3_dozen=0 then    
        bet3_wins<='1';
    else
        bet3_wins<='0';
    end if;

elsif (spin_result_latched>12) and (spin_result_latched<25) then
    if bet3_dozen=1 then    
        bet3_wins<='1';
    else
        bet3_wins<='0';
    end if;

else 
    if bet3_dozen=2 then    
        bet3_wins<='1';
    else
        bet3_wins<='0';
    end if; 
end if;

end process;


END behavioural;
