#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <architecture.h>



//uint8_t mem[256] = { WOUT,'a','b','c','\n',0,JMP,0 };
uint8_t mem[256] = { LB, 100, MV_R0, SINZ, JMP, 255,  WOUT, 'h','e','l','l','o','!', '\n', 0, MV_R0, SUB, 1, MV_R1, WB, 100, JMP, 0, [100] = 5, [255]=EXIT};

int main(int argc, char *argv[])
{
	int fd = open(argv[1], O_CREAT, S_IRUSR);
	read(fd, mem, 256);

	while(1) {
		IN = mem[PP++]; //fetch + advance stack pointer
		switch(IN) { //decode + execute
			case WOUT:
				write_out();
				break;
			case ROUT:
				read_out();
				break;
			case JMP:
				jump();
				break;
			case LB:
				load();
				break;
			case WB:
				write_b();
				break;
			case ADDI:
				addi();
				break;
			case SUBI:
				subi();
				break;
			case MV_R1:
				move_to_r1();
				break;
			case MV_R0:
				move_to_r0();
				break;
			case SIZ:
				skip_if_r0_zero();
				break;
			case SINZ:
				skip_if_r0_not_zero();
				break;
			case PUSH:
				push();
				break;
			case POP:
				pop();
				break;
			case NOP:
				continue;
			default:
				exit(0);
		}
	}
	return 0;
}
