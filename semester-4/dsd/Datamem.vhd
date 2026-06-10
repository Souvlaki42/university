library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Datamem is
    port(
        clk, MemRead, MemWrite: in std_logic;
        Address: in std_logic_vector(31 downto 0);
        WriteData: in std_logic_vector(31 downto 0);
        ReadData: out std_logic_vector(31 downto 0)
    );
end Datamem;

architecture dataflow of Datamem is
    type mem_array is array(0 to 15) of std_logic_vector(31 downto 0);
    signal mem: mem_array := (others => (others => '0'));
begin
    process(clk)
    begin
        if rising_edge(clk) then
            if MemWrite = '1' then
                mem(to_integer(unsigned(Address(3 downto 0)))) <= WriteData;
            end if;
        end if;
    end process;
    ReadData <= mem(to_integer(unsigned(Address(3 downto 0)))) when MemRead = '1' else (others => '0');
end dataflow;
