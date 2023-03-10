#************************************************
# Makefile for wordcount
# Author: Joe Mafrici
#
CC = gcc
all: wordcount

wordcount: wordcount.l
	flex -I wordcount.l
	$(CC) $(CFLAGS) -o wordcount lex.yy.c -lfl

clean:
	rm -rf wordcount
	rm -rf *.out
	rm -rf *.yy.c
