library ieee;
use ieee.std_logic_1164.all;

entity Signextension is
    port(
        Input: in std_logic_vector(15 downto 0);
        Output: out std_logic_vector(31 downto 0)
    );
end Signextension;

architecture dataflow of Signextension is
begin
    Output <= (31 downto 16 => Input(15)) & Input;
end dataflow;
