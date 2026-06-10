library ieee;
use ieee.std_logic_1164.all;

entity Mux32bit2to1_tb is
end Mux32bit2to1_tb;

architecture dataflow of Mux32bit2to1_tb is
    component Mux32bit2to1
        port(Input0, Input1: in std_logic_vector(31 downto 0);
             Sel: in std_logic;
             Output: out std_logic_vector(31 downto 0));
    end component;
    signal Input0, Input1, Output: std_logic_vector(31 downto 0);
    signal Sel: std_logic;
begin
    uut: Mux32bit2to1 port map(Input0 => Input0, Input1 => Input1, Sel => Sel, Output => Output);

    process
    begin
        Input0 <= X"CCCCCCCC"; Input1 <= X"BBBBBBBB"; Sel <= '1'; wait for 10 ns;
        Input0 <= X"CCCCCCCC"; Input1 <= X"BBBBBBBB"; Sel <= '0'; wait for 10 ns;
        wait;
    end process;
end dataflow;
