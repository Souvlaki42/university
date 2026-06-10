library ieee;
use ieee.std_logic_1164.all;

entity Control is
    port(
        Opcode: in std_logic_vector(5 downto 0);
        RegDst: out std_logic;
        ALUSrc: out std_logic;
        MemtoReg: out std_logic;
        RegWrite: out std_logic;
        MemRead: out std_logic;
        MemWrite: out std_logic;
        Branch: out std_logic;
        ALUOp: out std_logic_vector(1 downto 0)
    );
end Control;

architecture dataflow of Control is
begin
    process(Opcode)
    begin
        RegDst <= '0'; ALUSrc <= '0'; MemtoReg <= '0';
        RegWrite <= '0'; MemRead <= '0'; MemWrite <= '0';
        Branch <= '0'; ALUOp <= "00";
        case Opcode is
            when "000000" =>
                RegDst <= '1'; ALUSrc <= '0'; MemtoReg <= '0';
                RegWrite <= '1'; MemRead <= '0'; MemWrite <= '0';
                Branch <= '0'; ALUOp <= "10";
            when "001000" =>
                RegDst <= '0'; ALUSrc <= '1'; MemtoReg <= '0';
                RegWrite <= '1'; MemRead <= '0'; MemWrite <= '0';
                Branch <= '0'; ALUOp <= "00";
            when "100011" =>
                RegDst <= '0'; ALUSrc <= '1'; MemtoReg <= '1';
                RegWrite <= '1'; MemRead <= '1'; MemWrite <= '0';
                Branch <= '0'; ALUOp <= "00";
            when "101011" =>
                RegDst <= '0'; ALUSrc <= '1'; MemtoReg <= '0';
                RegWrite <= '0'; MemRead <= '0'; MemWrite <= '1';
                Branch <= '0'; ALUOp <= "00";
            when "000101" =>
                RegDst <= '0'; ALUSrc <= '0'; MemtoReg <= '0';
                RegWrite <= '0'; MemRead <= '0'; MemWrite <= '0';
                Branch <= '1'; ALUOp <= "01";
            when others =>
                null;
        end case;
    end process;
end dataflow;
