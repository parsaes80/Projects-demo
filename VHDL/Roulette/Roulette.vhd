LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.NUMERIC_STD.ALL;
 
LIBRARY WORK;
USE WORK.ALL;

ENTITY roulette IS
	PORT(   CLOCK_50 : IN STD_LOGIC; -- the fast clock for spinning wheel
		KEY : IN STD_LOGIC_VECTOR(3 downto 0);  -- includes slow_clock and reset
		SW : IN STD_LOGIC_VECTOR(17 downto 0);
		LEDG : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);  -- ledg
		HEX7 : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);  -- digit 7
		HEX6 : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);  -- digit 6
		HEX5 : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);  -- digit 5
		HEX4 : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);  -- digit 4
		HEX3 : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);  -- digit 3
		HEX2 : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);  -- digit 2
		HEX1 : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);  -- digit 1
		HEX0 : OUT STD_LOGIC_VECTOR(6 DOWNTO 0)   -- digit 0
	);
END roulette;


ARCHITECTURE structural OF roulette IS
component b1register is 
	port (	data_in :in STD_LOGIC;
		resetb : in STD_LOGIC;
		slow_clock : in STD_LOGIC;
		saved_data: out STD_LOGIC);
	end component;

	component b2register is 
	port (data_in :in std_logic_vector(1 downto 0);
		resetb : in STD_LOGIC;
		slow_clock : in STD_LOGIC;
		saved_data: out std_logic_vector(1 downto 0));
	end component;

	component b3register is 
	port (data_in :in std_logic_vector(2 downto 0);
		resetb : in STD_LOGIC;
		slow_clock : in STD_LOGIC;
		saved_data: out std_logic_vector(2 downto 0));
		end component;

	component b6register is 
 	port (data_in :in std_logic_vector(5 downto 0);
		resetb : in STD_LOGIC;
		slow_clock : in STD_LOGIC;
		saved_data: out std_logic_vector(5 downto 0));
	end component;

	component b12register is 
	port (data_in :in std_logic_vector(11 downto 0);
		resetb : in STD_LOGIC;
		slow_clock : in STD_LOGIC;
		saved_data: out std_logic_vector(11 downto 0));
		end component;

	component win IS
	PORT(spin_result_latched : in unsigned(5 downto 0);  -- result of the spin (the winning number)
             bet1_value : in unsigned(5 downto 0); -- value for bet 1
             bet2_colour : in std_logic;  -- colour for bet 2
             bet3_dozen : in unsigned(1 downto 0);  -- dozen for bet 3
             bet1_wins : out std_logic;  -- whether bet 1 is a winner
             bet2_wins : out std_logic;  -- whether bet 2 is a winner
             bet3_wins : out std_logic); -- whether bet 3 is a winner
	END component;	

	component new_balance IS
    PORT(money : in unsigned(11 downto 0);  -- Current balance before this spin
       value1 : in unsigned(2 downto 0);  -- Value of bet 1
       value2 : in unsigned(2 downto 0);  -- Value of bet 2
       value3 : in unsigned(2 downto 0);  -- Value of bet 3
       bet1_wins : in std_logic;  -- True if bet 1 is a winner
       bet2_wins : in std_logic;  -- True if bet 2 is a winner
       bet3_wins : in std_logic;  -- True if bet 3 is a winner
       new_money : out STD_LOGIC_VECTOR(11 downto 0));  -- balance after adding winning
                                                -- bets and subtracting losing bets
	end component;

	component Debounce_Switch is
	port (
	i_Clk : in std_logic;
	i_Switch : in std_logic;
	o_Switch : out std_logic
	);
	end component;
										
	
	component digit7seg IS
	PORT(
          digit : IN  UNSIGNED(3 DOWNTO 0);  -- number 0 to 0xF
          seg7 : OUT STD_LOGIC_VECTOR(6 DOWNTO 0)  -- one per segment
	);

	END component;
	signal win_spin,win_bet : std_logic_vector(5 downto 0);
	signal reg_spin : UNSIGNED(5 downto 0);
	signal win_clr, win1,win2,win3: std_logic;
	signal win_dzn : std_logic_vector(1 downto 0);
	signal bet1_amount,bet2_amount,bet3_amount : STD_LOGIC_VECTOR(2 downto 0);
	signal newcash, cash: std_logic_vector(11 downto 0);
	--signal KEY(1), KEY(0): std_logic;
	
 begin
	


	--dbclk: Debounce_Switch port map (CLOCK_50, KEY(0),KEY(0) );

	--dbrst: Debounce_Switch port map (CLOCK_50,KEY(1),KEY(1) );

	ball: spinwheel port map(CLOCK_50,not KEY(1),reg_spin );

	spinreg: b6register port map(std_logic_vector(reg_spin),not KEY(1),not KEY(0),win_spin);
	
	betreg: b6register port map(SW(8 downto 3),not KEY(1),not KEY(0),win_bet);

	clrreg: b1register port map(SW(12),not KEY(1),not KEY(0),win_clr);

	dznreg: b2register port map(SW(17 downto 16),not KEY(1),not KEY(0),win_dzn);

	seg16: digit7seg port map( UNSIGNED ("00" & win_spin(5 downto 4)), HEX7);

	seg15: digit7seg port map( UNSIGNED(win_spin(3 downto 0)), HEX6);

	winblk: win port map(UNSIGNED(win_spin),UNSIGNED(win_bet),win_clr,UNSIGNED(win_dzn),win1,win2,win3 );

	bet1reg :b3register port map (SW(2 downto 0), not KEY(1) , not KEY(0) , bet1_amount);

	bet2reg :b3register port map (SW(11 downto 9), not KEY(1) , not KEY(0) , bet2_amount);

	bet3reg :b3register port map (SW(15 downto 13), not KEY(1) , not KEY(0) , bet3_amount);

	moneyreg: b12register port map(newcash, not KEY(1) , not KEY(0) , cash );

	calc :new_balance port map (UNSIGNED(cash),UNSIGNED(bet1_amount),UNSIGNED(bet2_amount),UNSIGNED(bet3_amount),win1,win2,win3,newcash);
	
	 seg12: digit7seg port map( UNSIGNED(newcash(11 downto 8)), HEX2);

	 seg13: digit7seg port map(UNSIGNED( newcash(7 downto 4)), HEX1);

	 seg14: digit7seg port map(UNSIGNED( newcash (3 downto 0)), HEX0);
	 
	 LEDG(0) <=win1;  
	 
	 LEDG(1) <=win2;
	 
	 LEDG(2) <=win3;
	 
	 LEDG(3) <='0';

	 HEX3<= "1111111";

	 HEX4<= "1111111";

	 HEX5<= "1111111";
	 
	
	 
END ARCHITECTURE;
