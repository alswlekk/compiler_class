CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude -Ibuild

BUILD_DIR = build

OBJS = \
	$(BUILD_DIR)/lexer.o \
	$(BUILD_DIR)/parser.tab.o \
	$(BUILD_DIR)/ast.o \
	$(BUILD_DIR)/codegen_x86.o \
	$(BUILD_DIR)/main.o

all: minic_x86

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

minic_x86: $(BUILD_DIR) $(OBJS)
	$(CC) -o $@ $(OBJS) -lfl

$(BUILD_DIR)/parser.tab.c $(BUILD_DIR)/parser.tab.h: parser/parser.y | $(BUILD_DIR)
	bison -d -o $(BUILD_DIR)/parser.tab.c parser/parser.y

$(BUILD_DIR)/lexer.c: parser/lexer.l $(BUILD_DIR)/parser.tab.h | $(BUILD_DIR)
	flex -o $(BUILD_DIR)/lexer.c parser/lexer.l

$(BUILD_DIR)/lexer.o: $(BUILD_DIR)/lexer.c $(BUILD_DIR)/parser.tab.h include/ast.h
	$(CC) $(CFLAGS) -c $(BUILD_DIR)/lexer.c -o $@

$(BUILD_DIR)/parser.tab.o: $(BUILD_DIR)/parser.tab.c include/ast.h
	$(CC) $(CFLAGS) -c $(BUILD_DIR)/parser.tab.c -o $@

$(BUILD_DIR)/ast.o: src/ast.c include/ast.h
	$(CC) $(CFLAGS) -c src/ast.c -o $@

$(BUILD_DIR)/codegen_x86.o: src/codegen_x86.c include/ast.h include/codegen_x86.h
	$(CC) $(CFLAGS) -c src/codegen_x86.c -o $@

$(BUILD_DIR)/main.o: src/main.c include/ast.h include/codegen_x86.h
	$(CC) $(CFLAGS) -c src/main.c -o $@

# 사용자가 out.s를 만든 뒤(= minic_x86 실행해서 저장한 뒤),
#   make prog
# 를 치면 x86-64 실행 파일 prog를 만든다.
prog: out.s
	$(CC) -no-pie out.s -o prog

clean:
	rm -rf $(BUILD_DIR) minic_x86

.PHONY: all clean
