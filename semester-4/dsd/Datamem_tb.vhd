library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Datamem_tb is
end Datamem_tb;

architecture dataflow of Datamem_tb is
    component Datamem
        port(clk, MemRead, MemWrite: in std_logic;
             Address: in std_logic_vector(31 downto 0);
             WriteData: in std_logic_vector(31 downto 0);
             ReadData: out std_logic_vector(31 downto 0));
    end component;
    signal clk, MemRead, MemWrite: std_logic := '0';
    signal Address, WriteData, ReadData: std_logic_vector(31 downto 0);
begin
    uut: Datamem port map(clk => clk, MemRead => MemRead, MemWrite => MemWrite,
          Address => Address, WriteData => WriteData, ReadData => ReadData);

    clk <= not clk after 5 ns;

    process
    begin
        MemWrite <= '1'; Address <= X"00000002"; WriteData <= X"00000009";
        wait for 10 ns;

        MemWrite <= '1'; Address <= X"00000003"; WriteData <= X"00000004";
        wait for 10 ns;

        MemWrite <= '0'; MemRead <= '1'; Address <= X"00000002";
        wait for 10 ns;

        wait;
    end process;
end dataflow;
