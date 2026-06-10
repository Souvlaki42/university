library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Imem_tb is
end Imem_tb;

architecture dataflow of Imem_tb is
    component Imem
        port(clk: in std_logic;
             Address: in std_logic_vector(31 downto 0);
             ReadData: out std_logic_vector(31 downto 0);
             MemWrite: in std_logic;
             WriteAddr: in std_logic_vector(31 downto 0);
             WriteData: in std_logic_vector(31 downto 0));
    end component;
    signal clk: std_logic := '0';
    signal Address, ReadData: std_logic_vector(31 downto 0);
    signal MemWrite: std_logic := '0';
    signal WriteAddr, WriteData: std_logic_vector(31 downto 0);
begin
    uut: Imem port map(clk => clk, Address => Address, ReadData => ReadData,
          MemWrite => MemWrite, WriteAddr => WriteAddr, WriteData => WriteData);

    clk <= not clk after 5 ns;

    process
    begin
        MemWrite <= '1';
        WriteAddr <= X"00000000"; WriteData <= X"20000000"; wait for 10 ns;
        WriteAddr <= X"00000001"; WriteData <= X"20040000"; wait for 10 ns;
        WriteAddr <= X"00000002"; WriteData <= X"20030001"; wait for 10 ns;
        WriteAddr <= X"00000003"; WriteData <= X"20050003"; wait for 10 ns;
        WriteAddr <= X"00000004"; WriteData <= X"AC830000"; wait for 10 ns;
        WriteAddr <= X"00000005"; WriteData <= X"20630001"; wait for 10 ns;
        WriteAddr <= X"00000006"; WriteData <= X"20840001"; wait for 10 ns;
        WriteAddr <= X"00000007"; WriteData <= X"20A5FFFF"; wait for 10 ns;
        WriteAddr <= X"00000008"; WriteData <= X"14A0FFFB"; wait for 10 ns;

        MemWrite <= '0'; Address <= X"00000004";
        wait for 10 ns;

        wait;
    end process;
end dataflow;
