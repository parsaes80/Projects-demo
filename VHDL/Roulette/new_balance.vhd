LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.NUMERIC_STD.ALL;
 
LIBRARY WORK;
USE WORK.ALL;

--------------------------------------------------------------
--
-- This block is purely
-- combinational and calculates the
-- new balance after adding winning bets and subtracting losing bets.
--
---------------------------------------------------------------


ENTITY new_balance IS
  PORT(money : in unsigned(11 downto 0);  -- Current balance before this spin
       value1 : in unsigned(2 downto 0);  -- Value of bet 1
       value2 : in unsigned(2 downto 0);  -- Value of bet 2
       value3 : in unsigned(2 downto 0);  -- Value of bet 3
       bet1_wins : in std_logic;  -- True if bet 1 is a winner
       bet2_wins : in std_logic;  -- True if bet 2 is a winner
       bet3_wins : in std_logic;  -- True if bet 3 is a winner
       new_money : out STD_LOGIC_VECTOR(11 downto 0));  -- balance after adding winning
                                                -- bets and subtracting losing bets
END new_balance;


ARCHITECTURE behavioural OF new_balance IS

BEGIN

process(value1,value2,value3,bet1_wins,bet2_wins,bet3_wins, money)
variable balance: unsigned(11 downto 0);
begin
balance := money;
if bet1_wins='1' then 
	balance := balance + to_unsigned(35, 9) *value1;
else
  balance := balance - value1;
end if;

if bet2_wins='1' then 
	balance := balance + value2;
else
  balance := balance - value2;
end if;

if bet3_wins='1' then 
	balance := balance + to_unsigned(2, 2) *value3;
else
  balance := balance - value3; 
end if;

new_money<= STD_LOGIC_VECTOR(balance);

end process;


END;
