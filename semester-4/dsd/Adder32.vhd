library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Adder32 is
    port(
        A, B: in std_logic_vector(31 downto 0);
        Result: out std_logic_vector(31 downto 0)
    );
end Adder32;

architecture dataflow of Adder32 is
begin
    Result <= std_logic_vector(signed(A) + signed(B));
end dataflow;
