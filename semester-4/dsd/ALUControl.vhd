library ieee;
use ieee.std_logic_1164.all;

entity ALUControl is
    port(
        ALUOp: in std_logic_vector(1 downto 0);
        Funct: in std_logic_vector(5 downto 0);
        ALUcontrol: out std_logic_vector(3 downto 0)
    );
end ALUControl;

architecture dataflow of ALUControl is
begin
    process(ALUOp, Funct)
    begin
        case ALUOp is
            when "00" => ALUControl <= "0010";
            when "01" => ALUControl <= "0110";
            when "10" =>
                case Funct is
                    when "100000" => ALUControl <= "0010";
                    when "100010" => ALUControl <= "0110";
                    when others => ALUControl <= "0000";
                end case;
            when others => ALUControl <= "0000";
        end case;
    end process;
end dataflow;