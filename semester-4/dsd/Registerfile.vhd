library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity RegisterFile is
    port(
        clk, reset, RegWrite: in std_logic;
        ReadReg1, ReadReg2, WriteReg: in std_logic_vector(4 downto 0);
        WriteData: in std_logic_vector(31 downto 0);
        ReadData1, ReadData2: out std_logic_vector(31 downto 0)
    );
end RegisterFile;

architecture dataflow of RegisterFile is
    type reg_array is array(0 to 15) of std_logic_vector(31 downto 0);
    signal regs: reg_array := (others => (others => '0'));
begin
    process(clk, reset)
    begin
        if reset = '1' then
            regs <= (others => (others => '0'));
        elsif rising_edge(clk) then
            if RegWrite = '1' and to_integer(unsigned(WriteReg(3 downto 0))) /= 0 then
                regs(to_integer(unsigned(WriteReg(3 downto 0)))) <= WriteData;
            end if;
        end if;
    end process;
    ReadData1 <= regs(to_integer(unsigned(ReadReg1(3 downto 0))));
    ReadData2 <= regs(to_integer(unsigned(ReadReg2(3 downto 0))));
end dataflow;
