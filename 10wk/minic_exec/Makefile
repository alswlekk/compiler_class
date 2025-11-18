CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude -Ibuild
BISON = bison
FLEX = flex

BUILD_DIR = build
SRC_DIR = src
PARSER_DIR = parser

OBJS = $(BUILD_DIR)/parser.tab.o \
       $(BUILD_DIR)/lex.yy.o \
       $(SRC_DIR)/ast.o \
       $(SRC_DIR)/ir.o \
       $(SRC_DIR)/codegen.o \
       $(SRC_DIR)/symtab.o \
       $(SRC_DIR)/eval.o \
       $(SRC_DIR)/main.o

TARGET = mini_compiler

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/parser.tab.c $(BUILD_DIR)/parser.tab.h: $(PARSER_DIR)/parser.y | $(BUILD_DIR)
	$(BISON) -d -o $(BUILD_DIR)/parser.tab.c $(PARSER_DIR)/parser.y

$(BUILD_DIR)/lex.yy.c: $(PARSER_DIR)/scanner.l $(BUILD_DIR)/parser.tab.h | $(BUILD_DIR)
	$(FLEX) -o $(BUILD_DIR)/lex.yy.c $(PARSER_DIR)/scanner.l

$(BUILD_DIR)/parser.tab.o: $(BUILD_DIR)/parser.tab.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/lex.yy.o: $(BUILD_DIR)/lex.yy.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(SRC_DIR)/*.o

.PHONY: all clean
