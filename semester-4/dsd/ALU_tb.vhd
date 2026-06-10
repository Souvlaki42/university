library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ALU_tb is
end ALU_tb;

architecture dataflow of ALU_tb is
    component ALU
        port(A, B: in std_logic_vector(31 downto 0);
             ALUcontrol: in std_logic_vector(3 downto 0);
             ALUresult: out std_logic_vector(31 downto 0);
             Zero: out std_logic);
    end component;
    signal A, B, ALUresult: std_logic_vector(31 downto 0);
    signal ALUcontrol: std_logic_vector(3 downto 0);
    signal Zero: std_logic;
begin
    uut: ALU port map(A => A, B => B, ALUcontrol => ALUcontrol, ALUresult => ALUresult, Zero => Zero);

    process
    begin
        A <= X"00000007"; B <= X"FFFFFFFD"; ALUcontrol <= "0010";
        wait for 10 ns;

        A <= X"00000006"; B <= X"FFFFFFFA"; ALUcontrol <= "0010";
        wait for 10 ns;

        A <= X"00000005"; B <= X"00000008"; ALUcontrol <= "0110";
        wait for 10 ns;

        wait;
    end process;
end dataflow;
