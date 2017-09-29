
CC=gcc -O3 -Werror -Wextra -Wall -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Waggregate-return -Wswitch-default -Wswitch-enum -Wconversion -Wunreachable-code -Winit-self -Wformat-nonliteral -Wno-unused-parameter -Wno-unused-but-set-parameter -Wno-unused-result -std=c11 -fms-extensions -ggdb3

SRCDIR= src

MAIN_SOURCE=src/main.c
MAIN_PROGRAM=$(MAIN_SOURCE:.c=.o)
OBJS=$(patsubst %.c, %.o, $(filter-out $(MAIN_SOURCE), $(wildcard src/*.c)))

hashmap: $(OBJS) main.o
	$(CC) -o $@ $^ $(INC)

%.o : $(SRCDIR)/%.c
	$(CC) -c $^ -o $@ $(INC)


.PHONY : memcheck
memcheck : hashmap 
	valgrind --leak-check=full --track-origins=yes -v ./$<

.PHONY : all
all : hashmap

.PHONY : clean
clean :
	rm -f main.o
	rm -f hashmap
	rm -f src/*.o
