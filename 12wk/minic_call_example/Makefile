CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude -Ibuild

BUILD_DIR = build

OBJS = \
	$(BUILD_DIR)/lexer.o \
	$(BUILD_DIR)/parser.tab.o \
	$(BUILD_DIR)/main.o \
	$(BUILD_DIR)/ast.o \
	$(BUILD_DIR)/ir.o

all: minic

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

minic: $(BUILD_DIR) $(OBJS)
	$(CC) -o $@ $(OBJS) -lfl

$(BUILD_DIR)/parser.tab.c $(BUILD_DIR)/parser.tab.h: src/parser.y | $(BUILD_DIR)
	bison -d -o $(BUILD_DIR)/parser.tab.c src/parser.y

$(BUILD_DIR)/lexer.c: src/lexer.l | $(BUILD_DIR)
	flex -o $(BUILD_DIR)/lexer.c src/lexer.l

$(BUILD_DIR)/lexer.o: $(BUILD_DIR)/lexer.c $(BUILD_DIR)/parser.tab.h include/ast.h
	$(CC) $(CFLAGS) -c $(BUILD_DIR)/lexer.c -o $@

$(BUILD_DIR)/parser.tab.o: $(BUILD_DIR)/parser.tab.c include/ast.h
	$(CC) $(CFLAGS) -c $(BUILD_DIR)/parser.tab.c -o $@

$(BUILD_DIR)/main.o: src/main.c include/ast.h include/ir.h
	$(CC) $(CFLAGS) -c src/main.c -o $@

$(BUILD_DIR)/ast.o: src/ast.c include/ast.h
	$(CC) $(CFLAGS) -c src/ast.c -o $@

$(BUILD_DIR)/ir.o: src/ir.c include/ast.h include/ir.h
	$(CC) $(CFLAGS) -c src/ir.c -o $@

clean:
	rm -rf $(BUILD_DIR) minic

.PHONY: all clean
