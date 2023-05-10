library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity transmitter_tb is
end transmitter_tb;

architecture testbench of transmitter_tb is

  -- Component declaration for the transmitter
  component transmitter is
    port (
      clk_enable   : in  std_logic;
      reset : in  std_logic;
      start : in  std_logic;
      data  : in  std_logic_vector(7 downto 0);
      tx    : out std_logic
      );
  end component;

  component receiver is
	port (
       reset          	: in  std_logic; 
        clk_enable  	: in  std_logic; 
        received_data   : in  std_logic;
        receiver_output : out std_logic_vector(7 downto 0); 
        output_valid    : out std_logic; 
        reqtosend   	: out std_logic   
    );
	 end component;

  -- Signal declarations
  signal clk_enable_sig: std_logic:='0';
  signal reset_signal : std_logic;
  signal start_signal : std_logic;
  signal data_signal, data_out_signal  : std_logic_vector(7 downto 0);
  signal tx_signal    : std_logic;
  signal req2send_sig, output_valid_signal  : std_logic;
    -- Instantiate the transmitter
  begin

  dut : transmitter
    port map (
      clk_enable   => clk_enable_sig,
      reset => reset_signal,
      start => req2send_sig,
      data  => data_signal,
      tx    => tx_signal);
  
  rut: receiver
     port map (   
      clk_enable=>clk_enable_sig,
      reset =>  reset_signal,    
      received_data=> tx_signal,
      receiver_output=> data_out_signal,
      output_valid =>output_valid_signal,
      reqtosend=> req2send_sig  );

 
 clk_genble: process
    begin
        while true loop
            clk_enable_sig <= not clk_enable_sig;
            wait for 40 ns;
        end loop;
  end process;

 process
  begin
    data_signal<= "11010101";
    start_signal<='0';
    wait for 160 ns;
    start_signal<='1';
    wait for 2000 ns;
 end process;

end testbench;
