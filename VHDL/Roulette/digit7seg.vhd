LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.NUMERIC_STD.ALL;

LIBRARY WORK;
USE WORK.ALL;

-----------------------------------------------------
--
--  This block will contain a decoder to decode a 4-bit number
--  to a 7-bit vector suitable to drive a HEX dispaly
--
--  It is a purely combinational block (think Pattern 1) and
--  is similar to a block you designed in Lab 1.
--
--------------------------------------------------------

ENTITY digit7seg IS
	PORT(
          digit : IN  UNSIGNED(3 DOWNTO 0);  -- number 0 to 0xF
          seg7 : OUT STD_LOGIC_VECTOR(6 DOWNTO 0)  -- one per segment
	);
END;


ARCHITECTURE behavioral OF digit7seg IS
BEGIN
	PROCESS (digit)
	BEGIN
		CASE digit IS
			WHEN "0000" =>
				seg7 <= "1000000"; -- displays '0'
			WHEN "0001" =>
				seg7 <= "1111001"; -- displays '1'
			WHEN "0010" =>
				seg7 <= "0100100"; -- displays '2'
			WHEN "0011" =>
				seg7 <= "0110000"; -- displays '3'
			WHEN "0100" =>
				seg7 <= "0011001"; -- displays '4'
			WHEN "0101" =>
				seg7 <= "0010010"; -- displays '5'
			WHEN "0110" =>
				seg7 <= "0000010"; -- displays '6'
			WHEN "0111" =>
				seg7 <= "1111000"; -- displays '7'
			WHEN "1000" =>
				seg7 <= "0000000"; -- displays '8'
			WHEN "1001" =>
				seg7 <= "0010000"; -- displays '9'
			WHEN "1010" =>
				seg7 <= "0001000"; -- displays 'A'
			WHEN "1011" =>
				seg7 <= "0000011"; -- displays 'B'
			WHEN "1100" =>
				seg7 <= "1000110"; -- displays 'C'
			WHEN "1101" =>
				seg7 <= "0100001"; -- displays 'D'
			WHEN "1110" =>
				seg7 <= "0000110"; -- displays 'E'
			WHEN "1111" =>
				seg7 <= "0001110"; -- displays 'F'
		END CASE;
	END PROCESS;
END behavioral;
