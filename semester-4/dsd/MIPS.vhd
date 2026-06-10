library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity MIPS is
    port(
        clk, reset: in std_logic
    );
end MIPS;

architecture dataflow of MIPS is
    component PC is
        port(clk, reset: in std_logic; PCin: in std_logic_vector(31 downto 0); PCout: out std_logic_vector(31 downto 0));
    end component;
    component Adder32 is
        port(A, B: in std_logic_vector(31 downto 0); Result: out std_logic_vector(31 downto 0));
    end component;
    component Imem is
        port(clk: in std_logic; Address: in std_logic_vector(31 downto 0); ReadData: out std_logic_vector(31 downto 0);
             MemWrite: in std_logic; WriteAddr: in std_logic_vector(31 downto 0); WriteData: in std_logic_vector(31 downto 0));
    end component;
    component Control is
        port(Opcode: in std_logic_vector(5 downto 0); RegDst, ALUSrc, MemtoReg, RegWrite, MemRead, MemWrite, Branch: out std_logic;
             ALUOp: out std_logic_vector(1 downto 0));
    end component;
    component Mux5bit2to1 is
        port(Input0, Input1: in std_logic_vector(4 downto 0); Sel: in std_logic; Output: out std_logic_vector(4 downto 0));
    end component;
    component RegisterFile is
        port(clk, reset, RegWrite: in std_logic; ReadReg1, ReadReg2, WriteReg: in std_logic_vector(4 downto 0);
             WriteData: in std_logic_vector(31 downto 0); ReadData1, ReadData2: out std_logic_vector(31 downto 0));
    end component;
    component Signextension is
        port(Input: in std_logic_vector(15 downto 0); Output: out std_logic_vector(31 downto 0));
    end component;
    component Mux32bit2to1 is
        port(Input0, Input1: in std_logic_vector(31 downto 0); Sel: in std_logic; Output: out std_logic_vector(31 downto 0));
    end component;
    component ALUcontrol is
        port(ALUOp: in std_logic_vector(1 downto 0); Funct: in std_logic_vector(5 downto 0); ALUcontrol: out std_logic_vector(3 downto 0));
    end component;
    component ALU is
        port(A, B: in std_logic_vector(31 downto 0); ALUcontrol: in std_logic_vector(3 downto 0);
             ALUresult: out std_logic_vector(31 downto 0); Zero: out std_logic);
    end component;
    component Datamem is
        port(clk, MemRead, MemWrite: in std_logic; Address: in std_logic_vector(31 downto 0);
             WriteData: in std_logic_vector(31 downto 0); ReadData: out std_logic_vector(31 downto 0));
    end component;

    signal PCin, PCout, PCplus1: std_logic_vector(31 downto 0);
    signal instruction: std_logic_vector(31 downto 0);
    signal RegDst, ALUSrc, MemtoReg, RegWrite, MemRead, MemWrite, Branch: std_logic;
    signal ALUOp: std_logic_vector(1 downto 0);
    signal WriteReg: std_logic_vector(4 downto 0);
    signal ReadData1, ReadData2, WriteData: std_logic_vector(31 downto 0);
    signal signExtImm: std_logic_vector(31 downto 0);
    signal ALUinputB, ALUresult: std_logic_vector(31 downto 0);
    signal ALUctrl: std_logic_vector(3 downto 0);
    signal Zero: std_logic;
    signal MemReadData: std_logic_vector(31 downto 0);
    signal branchTarget: std_logic_vector(31 downto 0);
    signal PCSrc: std_logic;
begin
    PC_unit: PC port map(clk => clk, reset => reset, PCin => PCin, PCout => PCout);

    Adder14: Adder32 port map(A => PCout, B => X"00000001", Result => PCplus1);

    Imem_unit: Imem port map(clk => clk, Address => PCout, ReadData => instruction,
                  MemWrite => '0', WriteAddr => (others => '0'), WriteData => (others => '0'));

    Control_unit: Control port map(Opcode => instruction(31 downto 26),
                    RegDst => RegDst, ALUSrc => ALUSrc, MemtoReg => MemtoReg,
                    RegWrite => RegWrite, MemRead => MemRead, MemWrite => MemWrite,
                    Branch => Branch, ALUOp => ALUOp);

    MUX_RegDst: Mux5bit2to1 port map(Input0 => instruction(20 downto 16), Input1 => instruction(15 downto 11),
                                     Sel => RegDst, Output => WriteReg);

    RegFile: RegisterFile port map(clk => clk, reset => reset, RegWrite => RegWrite,
              ReadReg1 => instruction(25 downto 21), ReadReg2 => instruction(20 downto 16),
              WriteReg => WriteReg, WriteData => WriteData,
              ReadData1 => ReadData1, ReadData2 => ReadData2);

    SignExt: Signextension port map(Input => instruction(15 downto 0), Output => signExtImm);

    MUX_ALUSrc: Mux32bit2to1 port map(Input0 => ReadData2, Input1 => signExtImm,
                                      Sel => ALUSrc, Output => ALUinputB);

    ALUctrl_unit: ALUcontrol port map(ALUOp => ALUOp, Funct => instruction(5 downto 0),
                                       ALUcontrol => ALUctrl);

    ALU_unit: ALU port map(A => ReadData1, B => ALUinputB, ALUcontrol => ALUctrl,
               ALUresult => ALUresult, Zero => Zero);

    DataMem_unit: Datamem port map(clk => clk, MemRead => MemRead, MemWrite => MemWrite,
                    Address => ALUresult, WriteData => ReadData2, ReadData => MemReadData);

    MUX_MemtoReg: Mux32bit2to1 port map(Input0 => ALUresult, Input1 => MemReadData,
                                        Sel => MemtoReg, Output => WriteData);

    Adder15: Adder32 port map(A => PCplus1, B => signExtImm, Result => branchTarget);

    PCSrc <= Branch and (not Zero);

    MUX_PC: Mux32bit2to1 port map(Input0 => PCplus1, Input1 => branchTarget,
                                  Sel => PCSrc, Output => PCin);
end dataflow;
