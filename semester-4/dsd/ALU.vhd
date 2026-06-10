library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ALU is
    port(
        A, B: in std_logic_vector(31 downto 0);
        ALUcontrol: in std_logic_vector(3 downto 0);
        ALUresult: out std_logic_vector(31 downto 0);
        Zero: out std_logic
    );
end ALU;

architecture dataflow of ALU is
    signal result: std_logic_vector(31 downto 0);
begin
    process(A, B, ALUcontrol)
    begin
        case ALUcontrol is
            when "0010" => result <= std_logic_vector(signed(A) + signed(B));
            when "0110" => result <= std_logic_vector(signed(A) - signed(B));
            when others => result <= (others => '0');
        end case;
    end process;
    ALUresult <= result;
    Zero <= '1' when result = X"00000000" else '0';
end dataflow;
