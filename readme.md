# NTU assembler

**IMPORTANT**: if you wish to use this please make sure that the opcode for the instructions in the ISA.csv file are correct for your processor and modify them if necessary

assembler for NTU processor built in ceder logic this project will output a .cdm file with all the necessary data ready to be loaded into the processor RAM.

### how to use

Write assembly to plain text file, no specific file extension is necessary, the program will ask for the assembly file in question and output a 'machine_code.cdm' file with the assembled code ready for use in ceder logic

The Processor.cdl file is a Ceder logic processor with all the implemented instructions and can load the .cmd files

### instructions set

All instructions are in the ISA.csv file in the following format:

instruction | opcode
|--|--|
JMP|E
ADDI|D
MOVEI|C
BZ|FE

**Please see ISA.md for full documentation of supported instructions**

where:
- instruction is the assembly instruction
- opcode is the machine code for the instruction

### Assembly

the following is an example of valid assemble code, the code is not doing anything specifically, it's simply display purposes.

```
Start:
MOVEI 12 ; move immediate 12 into ACC
BNZ SUB ; branch to SUB if ACC is not zero

SUB:
ADDI -1 ; sub 1 from ACC
BNZ SUB ; if not zero go back to start of "subroutine"
BZ Start ; if ACC becomes zero go back to MOVEI
```

- the opcode followed by operand
- 0x will indicate a base 16 number and will be included as is
- lack of 0x will indicate a base 10 number
- operand uses two's complement, size depends from instructions, can very from 4, 8 or 12 bits
- if instruction is not recognised it will be prompted and the output file will have the instruction has presented
- anything followed by ';' will be treated as comments
- any unimplemented and will be prompted to the user and the program will continue onwards
- any line ending with ':' will be considered a label and relative addressing will be computer for any branching instruction that may make use if it

### CDM file format:

```
0 : C00C
1 : FD00
2 : DFFF
3 : FDFE
4 : FEFB
5 : NOP
```

- first number (base 10) indicates the memory cell of the instructions
- second number (base 16) indicates the machine code instruction, it has both opcode and operand imbedded within it
- 5th shows that error opcodes will be left as is