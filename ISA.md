# NTU ISA description

instruction | description | opcode | operand_bit_size
--|--|--|--
JMP | Unconditional Jump| E | 12
ADDI | add immediate mode data to ACC | D | 12
MOVEI | move immediate mode data to ACC | C | 12
BZ | branch if ACC is zero | FE | 8