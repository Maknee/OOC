# Copyright 2014-2015 The University of Edinburgh.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
# implied. See the License for the specific language governing
# permissions and limitations under the License.

CC=gcc -fprofile-arcs -ftest-coverage -O0 -g -ftrapv -Werror -Wextra -Wall -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Waggregate-return -Wswitch-default -Wswitch-enum -Wconversion -Wunreachable-code -Winit-self -Wformat-nonliteral -Wno-unused-parameter -Wno-unused-but-set-parameter -std=c11 -fms-extensions
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

.PHONY : test
test : ooc-tests
	./$<

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
	rm -f *.o
	rm -f *~
	rm -f src/*~
	rm -f test/*~
