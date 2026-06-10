library ieee;
use ieee.std_logic_1164.all;

entity Leftshift is
    port(
        Input: in std_logic_vector(31 downto 0);
        Output: out std_logic_vector(31 downto 0)
    );
end Leftshift;

architecture dataflow of Leftshift is
begin
    Output <= Input(29 downto 0) & "00";
end dataflow;
