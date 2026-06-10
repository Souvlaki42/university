library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity IMem is
    port(
        clk: in std_logic;
        Address: in std_logic_vector(31 downto 0);
        ReadData: out std_logic_vector(31 downto 0);
        MemWrite: in std_logic;
        WriteAddr: in std_logic_vector(31 downto 0);
        WriteData: in std_logic_vector(31 downto 0)
    );
end IMem;

architecture dataflow of IMem is
    type mem_array is array(0 to 15) of std_logic_vector(31 downto 0);
    signal mem: mem_array := (
        0 => X"20000000",
        1 => X"20040000",
        2 => X"20030001",
        3 => X"20050003",
        4 => X"AC830000",
        5 => X"20630001",
        6 => X"20840001",
        7 => X"20A5FFFF",
        8 => X"14A0FFFB",
        others => X"00000000"
    );
begin
    process(clk)
    begin
        if rising_edge(clk) then
            if MemWrite = '1' then
                mem(to_integer(unsigned(WriteAddr(3 downto 0)))) <= WriteData;
            end if;
        end if;
    end process;
    ReadData <= mem(to_integer(unsigned(Address(3 downto 0))));
end dataflow;