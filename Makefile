
CC=gcc -fprofile-arcs -ftest-coverage -O0 -g -ftrapv -Werror -Wextra -Wall -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Waggregate-return -Wswitch-default -Wswitch-enum -Wconversion -Wunreachable-code -Winit-self -Wformat-nonliteral -Wno-unused-parameter -Wno-unused-but-set-parameter -Wno-unused-variable -std=c11 -fms-extensions -ggdb3
LDFLAGS=-lcunit

SRCDIR= src
TESTDIR= test
INC=-I$(SRCDIR) -I$(TESTDIR) -I$(HOME)/include

MAIN_SOURCE=src/ooc_program.c
MAIN_PROGRAM=$(MAIN_SOURCE:.c=.o)
OBJS=$(patsubst %.c, %.o, $(filter-out $(MAIN_SOURCE), $(wildcard src/*.c)))
TESTS=$(patsubst %.c, %.o, $(wildcard test/*.c))

ooc: $(OBJS) ooc_program.o
	$(CC) -o $@ $^ $(INC)

ooc-tests: $(TESTS) $(OBJS)
	$(CC) -o $@ $^ $(INC) $(LDFLAGS)

%.o : $(SRCDIR)/%.c
	$(CC) -c $^ -o $@ $(INC)
%.o : $(TESTDIR)/%.c
	$(CC) -c $^ -o $@ $(INC)

.PHONY : xunit-report
xunit-report :
	xsltproc -novalid cunit-to-junit.xsl CUnitAutomated-Results.xml > TestResults.xml

#.PHONY : test
#test : ooc-tests
#	./$<

.PHONY : test
test : ooc-tests
	valgrind --leak-check=full --track-origins=yes --log-file="logfile.out" -v ./$<
	cat logfile.out

.PHONY : all
all : ooc test

.PHONY : clean
clean :
	rm -f ooc
	rm -f ooc-tests
	rm -f *.gcda
	rm -f *.gcno
	rm -f src/*.gcda
	rm -f src/*.gcno
	rm -f src/*.o
	rm -f test/*.gcda
	rm -f test/*.gcno
	rm -f test/*.o
	rm -f CUnit*.xml
	rm -f TestResults.xml
	rm -f logfile.out
	rm -f *.o
	rm -f *~
	rm -f src/*~
	rm -f test/*~
