#************************************************
# Makefile for calculator
# Author: Joe Mafrici
#
CC = gcc
all: calc
	flex calc.l
	$(CC) lex.yy.yac -lfl

clean:
	rm -rf *.out
	rm -rf *.yy.c
