CC = gcc
CFLAGS = -Wall -Wextra -g
OBJS = main.o parser.o ast.o tac.o lexer.o

TARGET = parser_demo

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

main.o: main.c parser.h ast.h tac.h
parser.o: parser.c parser.h ast.h lexer.h token.h
ast.o: ast.c ast.h
tac.o: tac.c tac.h ast.h
lexer.o: lexer.c lexer.h token.h

run: $(TARGET)
	./$(TARGET) "a=a+3*4;"

clean:
	rm -f $(OBJS) $(TARGET)
