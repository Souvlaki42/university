library ieee;
use ieee.std_logic_1164.all;

entity Leftshift_tb is
end Leftshift_tb;

architecture dataflow of Leftshift_tb is
    component Leftshift
        port(Input: in std_logic_vector(31 downto 0);
             Output: out std_logic_vector(31 downto 0));
    end component;
    signal Input, Output: std_logic_vector(31 downto 0);
begin
    uut: Leftshift port map(Input => Input, Output => Output);

    process
    begin
        Input <= X"0FFFFFFF"; wait for 10 ns;
        wait;
    end process;
end dataflow;
