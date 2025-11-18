CC = gcc
LEX = flex
YACC = bison
CFLAGS = -Wall -Wextra -O2

GENS = lex.yy.c parser.tab.c parser.tab.h
SRCS = ast.c main.c
OBJS = $(GENS) $(SRCS)
TARGET = calc_ast

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

parser.tab.c parser.tab.h: parser.y
	$(YACC) -d parser.y

lex.yy.c: scanner.l
	$(LEX) scanner.l

clean:
	rm -f $(TARGET) $(GENS)
