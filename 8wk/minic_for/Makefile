# 여러분 환경에 맞춰 FLEX/BISON 커맨드 이름 확인 (flex, bison)
CC      := gcc
CFLAGS  := -O2 -g -Wall
LEX     := flex
YACC    := bison

# 여러분이 지난주 만든 lexer
LEXER   := lexer.l
PARSER  := parser.y

all: cparser

lex.yy.c: $(LEXER)
	$(LEX) -o $@ $<

parser.c parser.h: $(PARSER)
	$(YACC) -d -o parser.c $<

cparser: parser.c lex.yy.c ast.c main.c
	$(CC) $(CFLAGS) -o $@ parser.c lex.yy.c ast.c main.c

clean:
	rm -f cparser parser.c parser.h lex.yy.c *.o
