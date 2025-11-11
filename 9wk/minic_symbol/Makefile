CFLAGS  := -O2 -g -Wall -Wextra
OBJS    := parser.o lex.yy.o ast.o symbol_table.o sema.o main.o

all: cparser

parser.o: parser.c parser.h ast.h
lex.yy.o: lex.yy.c parser.h ast.h
ast.o: ast.c ast.h
symbol_table.o: symbol_table.c symbol_table.h
sema.o: sema.c sema.h symbol_table.h ast.h
main.o: main.c ast.h sema.h

cparser: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

parser.c parser.h: parser.y
	bison -d -o parser.c $<

lex.yy.c: lexer.l parser.h
	flex -o $@ $<

clean:
	rm -f cparser *.o parser.c parser.h lex.yy.c