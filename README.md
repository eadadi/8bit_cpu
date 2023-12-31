# 8 Bit Cpu
This project has 8 bit cpu implementation alongisde an assembly compiler,
and few code examples.

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

## Available Registers:
	PP: Program pointer (i.e. program counter)
	SP: Stack pointer	
	In: Current instruction
	R0: General purpose register
	R1: General purpose register

## Available Opcodes:
	NOP: Do nothing
	ROUT: Read from outstream to R0
	WOUT: Write from R0 to outstream (until R0 = 0)
	JMP: Advance PP to given argument
	LB: Read next byte to R0, then set R1 to the memory value at offset R0
	WB: Read next byte to R0, then set memory offset R0 to R1
	ADDI: Add a constant to R0. The constant is the consequent byte
	SUBI: Decrement a constant from R0. The constant is the consequent byte
	ADD: Sum R0 and R1 to R0
	SUB: Sub R1 from R0 to R0
	MV_R1: Move R0 to R1
	MV_R0: Move R1 to R0
	SIZ: Skip next instruction if R0 is zero
	SINZ: Skip next instruction if R0 is not zero
	PUSH: Push R0 to stack and advance SP
	POP: Pop last stack value to R0 and dec SP
	CALL: Push PP to stack (override R0), and set PP to R1
	RET: Pop last stack value, and set PP to it
	EXIT: Exit


## Example
```asm
 	LB, 127
	MV_R0
	SINZ
	EXIT
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
```
*Explanation:*  The value at memory address 127 hold the number of reptitions. The program is to load this value, and compare it to zero. If it is zero, exit the program. Otherwise, print the string, pirnt a new line character, decrement the remaining number of prints and store it at memory address 127.

### Running the example:
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

