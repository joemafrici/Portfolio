#************************************************
# Makefile for calculator
# Author: Joe Mafrici
#
CC = gcc
CFLAGS = -g -Wall -Werror -O0 -std=c17 -D_XOPEN_SOURCE=700
all: calc

debug: calc.l calc.y
	bison --debug --verbose -Wcounterexamples -d calc.y
	flex -I calc.l
	gcc $(CFLAGS) -o calc calc.tab.c lex.yy.c -lfl

calc: calc.l calc.y
	bison -d calc.y
	flex -I calc.l
	gcc $(CFLAGS) -o $@ calc.tab.c lex.yy.c -lfl

clean:
	rm -rf *.out
	rm -rf *.yy.c
	rm -rf *.tab.c
	rm -rf *.tab.h
	rm -rf calc
	rm -rf *.output
