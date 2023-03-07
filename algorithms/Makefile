#************************************************
# Makefile for sorts
# Author: Joe Mafrici
#
EXECS = factorial
CC = gcc
CFLAGS = -g -Wall -Werror -O0 -std=c17
OBJS = factorial.o \

all: $(EXECS)


factorial:  $(OBJS)
	$(CC) -o factorial $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $? -o $@

.cpp.o:
	g++ $(CFLAGS) -c $? -o $@

clean:
	rm -rf $(OBJS)
	rm -rf $(EXECS)
	rm -rf *.txt

.PHONY: clean
