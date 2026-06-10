library ieee;
use ieee.std_logic_1164.all;

entity Control_tb is
end Control_tb;

architecture dataflow of Control_tb is
    component Control
        port(Opcode: in std_logic_vector(5 downto 0);
             RegDst, ALUSrc, MemtoReg, RegWrite, MemRead, MemWrite, Branch: out std_logic;
             ALUOp: out std_logic_vector(1 downto 0));
    end component;
    signal Opcode: std_logic_vector(5 downto 0);
    signal RegDst, ALUSrc, MemtoReg, RegWrite, MemRead, MemWrite, Branch: std_logic;
    signal ALUOp: std_logic_vector(1 downto 0);
begin
    uut: Control port map(Opcode => Opcode, RegDst => RegDst, ALUSrc => ALUSrc,
          MemtoReg => MemtoReg, RegWrite => RegWrite, MemRead => MemRead,
          MemWrite => MemWrite, Branch => Branch, ALUOp => ALUOp);

    process
    begin
        Opcode <= "001000"; wait for 10 ns;
        Opcode <= "101011"; wait for 10 ns;
        Opcode <= "000101"; wait for 10 ns;
        wait;
    end process;
end dataflow;
