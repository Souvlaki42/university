library ieee;
use ieee.std_logic_1164.all;

entity Signextension_tb is
end Signextension_tb;

architecture dataflow of Signextension_tb is
    component Signextension
        port(Input: in std_logic_vector(15 downto 0);
             Output: out std_logic_vector(31 downto 0));
    end component;
    signal Input: std_logic_vector(15 downto 0);
    signal Output: std_logic_vector(31 downto 0);
begin
    uut: Signextension port map(Input => Input, Output => Output);

    process
    begin
        Input <= X"FAAA"; wait for 10 ns;
        Input <= X"AFFF"; wait for 10 ns;
        Input <= X"5444"; wait for 10 ns;
        wait;
    end process;
end dataflow;
