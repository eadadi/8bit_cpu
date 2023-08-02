#include <stdint.h>
#include <op_codes.h>

typedef uint8_t reg;
typedef uint8_t inst;
extern uint8_t mem[256];

/*
 * The machine is connected to output stream and input stream
 */
#define OSTREAM stdout
#define ISTREAM stdin

struct cpu_state {
	reg pp; //program pointer
	reg sp;
	reg in;
	reg r0;
	reg r1;
} state = { .pp=0, .sp=199, .in = 0, .r0= 0, .r1= 0 }; //initial machine state
#define PP state.pp
#define SP state.sp
#define R0 state.r0
#define R1 state.r1
#define IN state.in

/*
 * Memory structure:
 * Program:
 * 	[0 - 127]
 * Stack:
 * 	[128 - 199]
 * Constants:
 * 	[200 - 254]
 * Exit:
 * 	[255]
 */
