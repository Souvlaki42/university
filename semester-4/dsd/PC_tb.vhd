library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity PC_tb is
end PC_tb;

architecture dataflow of PC_tb is
    component PC
        port(clk, reset: in std_logic;
             PCin: in std_logic_vector(31 downto 0);
             PCout: out std_logic_vector(31 downto 0));
    end component;
    signal clk, reset: std_logic := '0';
    signal PCin, PCout: std_logic_vector(31 downto 0);
begin
    uut: PC port map(clk => clk, reset => reset, PCin => PCin, PCout => PCout);

    clk <= not clk after 5 ns;

    process
    begin
        reset <= '1'; wait for 10 ns; reset <= '0'; wait for 10 ns;

        PCin <= X"AAAACCCC"; wait for 10 ns;
        PCin <= X"FFFFBBBB"; wait for 10 ns;

        wait;
    end process;
end dataflow;
