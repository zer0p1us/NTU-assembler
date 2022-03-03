# NTU assembler

**IMPORTANT**: if you wish to use this please make sure that the opcode for the instructions in the ISA.csv file are correct for your processor and modify them if necessary

assembler for NTU processor built in ceder logic this project will output a .cdm file with all the necessary data ready to be loaded into the processor RAM.

### how to use

Write assembly to plain text file, no specific file extension is necessary, the program will output a 'machine_code.cdm' file with the assembled code ready for use in cdm

### instructions set

All instructions are in the ISA.csv file in the following format:

instruction | opcode | operand_bit_size
--|--|--
JMP|E|12
ADDI|D|12
MOVEI|C|12
BZ|FE|8

**Please see ISA.md for full documentation of supported instructions**

where:
- instruction is the assembly instruction
- opcode is the machine code for the instruction
- operand_bit_size is the size of the operand, (may be removed in the future to be computed at runtime)

### Assemble

the following is an example of valid assemble code, the code is not doing anything specifically, it's simply display purposes.

```
MOVEI 12
ADDI -12
ADDI 12
BZ 0
JMP 0
```

- the opcode followed by operand
- 0x will indicate a base 16 number and will be included as is
- lack of 0x will indicate a base 10 number
- operand uses two's complement, size depends from instructions, can very from 4, 8 or 12 bits
- if instruction is not recognised it will be prompted and the output file will have the instruction has presented

### CDM file format:

```
0 : C00C
1 : DFF4
2 : D00C
3 : FE00
4 : E001
5 : E000
```

- first number (base 10) indicates the memory cell of the instructions
- second number (base 16) indicates the machine code instruction, it has both opcode and operand imbedded within it