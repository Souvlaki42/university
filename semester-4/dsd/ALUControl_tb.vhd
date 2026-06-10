library ieee;
use ieee.std_logic_1164.all;

entity ALUcontrol_tb is
end ALUcontrol_tb;

architecture dataflow of ALUcontrol_tb is
    component ALUcontrol
        port(ALUOp: in std_logic_vector(1 downto 0);
             Funct: in std_logic_vector(5 downto 0);
             ALUcontrol: out std_logic_vector(3 downto 0));
    end component;
    signal ALUOp: std_logic_vector(1 downto 0);
    signal Funct: std_logic_vector(5 downto 0);
    signal ALUcontrol_out: std_logic_vector(3 downto 0);
begin
    uut: ALUcontrol port map(ALUOp => ALUOp, Funct => Funct, ALUcontrol => ALUcontrol_out);

    process
    begin
        Funct <= "100000"; ALUOp <= "10"; wait for 10 ns;
        Funct <= "100010"; ALUOp <= "10"; wait for 10 ns;
        Funct <= "111111"; ALUOp <= "00"; wait for 10 ns;
        Funct <= "111111"; ALUOp <= "01"; wait for 10 ns;
        wait;
    end process;
end dataflow;
