library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Registerfile_tb is
end Registerfile_tb;

architecture dataflow of Registerfile_tb is
    component RegisterFile
        port(clk, reset, RegWrite: in std_logic;
             ReadReg1, ReadReg2, WriteReg: in std_logic_vector(4 downto 0);
             WriteData: in std_logic_vector(31 downto 0);
             ReadData1, ReadData2: out std_logic_vector(31 downto 0));
    end component;
    signal clk, reset, RegWrite: std_logic := '0';
    signal ReadReg1, ReadReg2, WriteReg: std_logic_vector(4 downto 0);
    signal WriteData, ReadData1, ReadData2: std_logic_vector(31 downto 0);
begin
    uut: RegisterFile port map(clk => clk, reset => reset, RegWrite => RegWrite,
          ReadReg1 => ReadReg1, ReadReg2 => ReadReg2, WriteReg => WriteReg,
          WriteData => WriteData, ReadData1 => ReadData1, ReadData2 => ReadData2);

    clk <= not clk after 5 ns;

    process
    begin
        reset <= '1'; wait for 10 ns; reset <= '0'; wait for 10 ns;

        RegWrite <= '1'; WriteReg <= "00100"; WriteData <= X"00000006";
        wait for 10 ns;

        RegWrite <= '1'; WriteReg <= "00101"; WriteData <= X"00000009";
        wait for 10 ns;

        RegWrite <= '1'; WriteReg <= "00110"; WriteData <= X"00000003";
        wait for 10 ns;

        RegWrite <= '0'; ReadReg1 <= "00100"; ReadReg2 <= "00101";
        wait for 10 ns;

        wait;
    end process;
end dataflow;
