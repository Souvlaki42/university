library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity PC is
    port(
        clk, reset: in std_logic;
        PCin: in std_logic_vector(31 downto 0);
        PCout: out std_logic_vector(31 downto 0)
    );
end PC;

architecture dataflow of PC is
    signal pc_reg: std_logic_vector(31 downto 0) := (others => '0');
begin
    process(clk, reset)
    begin
        if reset = '1' then
            pc_reg <= (others => '0');
        elsif rising_edge(clk) then
            pc_reg <= PCin;
        end if;
    end process;
    PCout <= pc_reg;
end dataflow;
