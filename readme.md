# NTU assembler

**IMPORTANT**: if you wish to use this please make sure that the opcode for the instructions in the ISA.csv file are correct for your processor and modify them if necessary

assembler for NTU processor built in ceder logic| this project will output a .cdm file with all the necessary data ready to be loaded into the processor RAM

All instructions are in the ISA.csv file in the following format:

instruction | opcode | operand_bit_size
--|--|--
JMP|E|12
ADDI|D|12
MOVEI|C|12
BZ|FE|8

where:
- instruction is the assembly instruction
- opcode is the machine code for the instruction
- operand_bit_size is the size of the operand, (may be removed in the future to be computed at runtime)
