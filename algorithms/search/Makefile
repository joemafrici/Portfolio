#************************************************
# Makefile for sorts
# Author: Joe Mafrici
#
EXECS = tester
CC = gcc
CFLAGS = -g -Wall -Werror -O0 -std=c17
OBJS = test_runner.o \
	   search.o \
	   ../sort/sorts.o \

all: $(EXECS)


tester:  $(OBJS)
	$(CC) -o tester $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $? -o $@

.cpp.o:
	g++ $(CFLAGS) -c $? -o $@

clean:
	rm -rf $(OBJS)
	rm -rf $(EXECS)
	rm -rf *.txt

.PHONY: clean
