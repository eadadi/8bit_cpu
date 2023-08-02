FLAGS := -O0 -g

SRCS := $(wildcard *.c)
OBJS := $(SRCS)
OBJS := $(subst .c,.o,$(OBJS))

INC_DIRS := .
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA
INC := $(addprefix -I,$(INC_DIRS))

all: $(OBJS)
	gcc $(FLAGS) $(OBJS) $(INC) -o main


%.o : %.c
	gcc $(FLAGS) $(INC) -c $< -o $@

clean:
	rm *.o main
