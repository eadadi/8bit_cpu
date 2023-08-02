# An implementation of 8 bit cpu

This repository contains:
	- an 8 bit implementation
	- an assembly compiler
	- 2 assemble example programs

## Description
The core has 256bytes memory, used to contain the program,
the program stack and constants.

For simplicity, I did not implement the inner components such as ALU,
and in some operations I loosely used undefined registers.
On future progress this could be improved.

Memory layout:
1. Program: 0-127
1. Stack: 128-199
1. Constants: 200-254
1. Exit: 255

## Current registers:
	PP: Program pointer (i.e. program counter)
	SP: Stack pointer	
	In: Current instruction
	R0: General purpose register
	R1: General purpose register

## Current supported opcodes are:
	NOP: Do nothing
	ROUT: Read from outstream to R0
	WOUT: Write from R0 to outstream (until R0 = 0)
	JMP: Advance PP to given argument
	LB: Read next byte to R0, then set R1 to the memory value at offset R0
	WB: Read next byte to R0, then set memory offset R0 to R1
	ADDI: Add a constant to R0. The constant is the consequent byte.
	SUBI: Decrement a constant from R0. The constant is the consequent byte.
	ADD: Sum R0 and R1 to R0
	SUB: Sub R1 from R0 to R0
	MV_R1: Move R0 to R1
	MV_R0: Move R1 to R0
	SIZ: Skip next instruction if R0 is zero
	SINZ: Skip next instruction if R0 is not zero
	PUSH: Push R0 to stack and advance SP
	POP: Pop last stack value to R0 and dec SP
	EXIT: Exit


## An example for the assembly code
```asm
 	LB, 127
	MV_R0
	SINZ
	JMP, 255
	WOUT
	STR_START
	Hello World!
	WOUT
	SEQ_START
	num:10
	num:0
	SEQ_END
	MV_R0
	SUBI, 1
	MV_R1
	WB, 127
	JMP, 0
	.127:2
	.255:255
```
*Explanation:* Load the value at byte 127 to R1, keep it at R0. Then, if it is zero goto byte 255 (exit).
Otherwise, output "Hello World!", decrement R0, move it to R1 and store it back at byte 127

### To run the example:
1. Convert the assembly file to machine code using 
```python
python3 asm_compiler.py multiple_hello_world.asm
```
2. Compile the cpu code using
```bash
make clean all
```
3. Run the machine code (default to *prog*) using
```bash
./main prog
```

