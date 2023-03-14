#************************************************
# Makefile starter
# Author: Joe Mafrici
#
CC = g++
CFLAGS = -g -Wall -Werror -O0 -std=c++17 -D_XOPEN_SOURCE=700
EXEC = concordance
all: $(EXEC)

debug: $(EXEC).l
	flex -I -d $<
	$(CC) $(CFLAGS) -o $(EXEC) lex.yy.c -lfl
$(EXEC): $(EXEC).l
	flex -I $<
	$(CC) $(CFLAGS) -o $@ lex.yy.c -lfl
clean:
	rm -rf lex.yy.c
	rm -rf *.tab.c
	rm -rf *.tab.h
	rm -rf $(EXEC)
	rm -rf *.output
