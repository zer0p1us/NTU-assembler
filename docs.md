# Documentation

## ISA documentations

Abbreviations | Description
--|--
ACC | Accumulator
PC | Program Counter
ADREG | Address Register
SP | Stack pointer

Term | Meaning
--|--
Immediate | the operand is the data, as apposed to the memory address of the data


**4 Bit instructions with 12 Bit Operands**

instruction | description | opcode **(4 bit Hex)** | operand **(12 bit Hex)**
--|--|--|--
JMP | Unconditional jump to memory | E | Absolute memory address
ADDI | Add immediate mode data to ACC | D | Immediate value
MOVEI | Move immediate mode data to ACC | C | Immediate value
MOVE | Move memory content to ACC | B | Absolute memory location
STORE | Store ACC on memory location | A | Absolute memory location
LDA | Load immediate value into ADREG | 9 | Immediate value
LDSP | Load immediate value into SP | 8 | Immediate value


**8 Bit instructions with 8 Bit Operands**

instruction | description | opcode **(8 bit Hex)** | operand **(8 bit Hex)**
--|--|--|--
BZ | Branch if ACC is zero | FE | Value to add to PC to jump relative to current position
BNZ | Branch if ACC isn't zero | FD | Value to add to PC to jump relative to current position


**12 Bit instructions with 4 Bit Operands**

instruction | description | opcode **(12 bit Hex)** | operand **(4 bit Hex)**
--|--|--|--
 |  |  |


**16 Bit instructions with No Operands**

instruction | description | opcode **(16 bit Hex)**
--|--|--
STA | Store value at ACC at memory address in ADREG | FFFF
STA+ | Store value at ACC at memory address in ADREG and increment it | FFFE
MOVE(A) | Move value at memory address present in ADREG to the ACC | FFFD
MOVE(A)+ | Move value at memory address present in ADREG to the ACC, and increment ADREG | FFFC


## Signal Documentation
