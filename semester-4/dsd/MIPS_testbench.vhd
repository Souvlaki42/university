library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity MIPS_tb is
end MIPS_tb;

architecture dataflow of MIPS_tb is
    component MIPS
        port(clk, reset: in std_logic);
    end component;
    signal clk: std_logic := '0';
    signal reset: std_logic;
begin
    uut: MIPS port map(clk => clk, reset => reset);

    clk <= not clk after 2.5 ns;

    process
    begin
        reset <= '1';
        wait for 4 ns;
        reset <= '0';
        wait for 500 ns;
        wait;
    end process;
end dataflow;
