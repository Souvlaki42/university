library ieee;
use ieee.std_logic_1164.all;

entity Mux5bit2to1 is
    port(
        Input0, Input1: in std_logic_vector(4 downto 0);
        Sel: in std_logic;
        Output: out std_logic_vector(4 downto 0)
    );
end Mux5bit2to1;

architecture dataflow of Mux5bit2to1 is
begin
    Output <= Input0 when Sel = '0' else Input1;
end dataflow;
