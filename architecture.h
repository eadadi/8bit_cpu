#include <core.h>

void read_out()
{
	fflush(ISTREAM);
	R0 = fgetc(ISTREAM);
}

void write_out()
{
	R0 = mem[PP++];
	while(R0)
	{
		fputc(R0, OSTREAM);
		R0 = mem[PP++];
	}
	fflush(OSTREAM);
}

void jump()
{
	PP = mem[PP];
}

void load()
{
	R0 = mem[PP++];
	R1 = mem[R0];
}

void write_b()
{
	R0 = mem[PP++];
	mem[R0] = R1;
}

void addi()
{
	R0 += mem[PP++];
}

void subi()
{
	R0 -= mem[PP++];
}

void add()
{
	R0 += R1;
}

void sub()
{
	R0 -= R1;
}

void move_to_r1()
{
	R1 = R0;
}

void move_to_r0()
{
	R0 = R1;
}

void skip_if_r0_zero()
{
	if(!R0)
		PP += 1;
}

void skip_if_r0_not_zero()
{
	if(R0)
		PP += 1;
}

void push()
{
	mem[SP--] = R0;
}

void pop()
{
	R0 = mem[++SP];
}

void call()
{
	R0 = PP;
	push();
	PP = R1;
}

void ret()
{
	pop();
	PP = R0;
}
