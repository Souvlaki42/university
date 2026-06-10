library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Adder32_tb is
end Adder32_tb;

architecture dataflow of Adder32_tb is
    component Adder32
        port(A, B: in std_logic_vector(31 downto 0);
             Result: out std_logic_vector(31 downto 0));
    end component;
    signal A, B, Result: std_logic_vector(31 downto 0);
begin
    uut: Adder32 port map(A => A, B => B, Result => Result);

    process
    begin
        A <= X"CCCCCCCC"; B <= X"BBBBBBBB"; wait for 10 ns;
        A <= X"BBBBBBBB"; B <= X"55555556"; wait for 10 ns;
        wait;
    end process;
end dataflow;
