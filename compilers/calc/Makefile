#************************************************
# Makefile starter
# Author: Joe Mafrici
#
CC = gcc
CFLAGS = -g -Wall -Werror -O0 -std=c17 -D_XOPEN_SOURCE=700
EXEC = calc
all: $(EXEC)

debug: $(EXEC).l $(EXEC).y
	bison --debug --verbose -Wcounterexamples -d $(word, 2 $^)
	flex -I $<
	$(CC) $(CFLAGS) -o $(EXEC) $(EXEC).tab.c lex.yy.c -lfl
$(EXEC): $(EXEC).l $(EXEC).y
	bison -d $(word 2, $^)
	flex -I $<
	$(CC) $(CFLAGS) -o $@ $(EXEC).tab.c lex.yy.c -lfl
clean:
	rm -rf lex.yy.c
	rm -rf *.tab.c
	rm -rf *.tab.h
	rm -rf $(EXEC)
	rm -rf *.output
