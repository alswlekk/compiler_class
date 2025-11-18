# 실행 파일 이름
TARGET = calc

# flex/bison 소스
LEX_SRC = scanner.l
YACC_SRC = parser.y

# 생성 파일
LEX_C = lex.yy.c
YACC_C = parser.tab.c
YACC_H = parser.tab.h

CC = cc
CFLAGS = -Wall -g
LIBS = -lfl   # macOS 환경에서는 -ll 이어야 할 수도 있음

.PHONY: all clean

all: $(TARGET)

# 최종 실행 파일
$(TARGET): $(YACC_C) $(LEX_C)
	$(CC) $(CFLAGS) -o $@ $(YACC_C) $(LEX_C) $(LIBS)

# bison: parser.y → parser.tab.c / parser.tab.h
$(YACC_C) $(YACC_H): $(YACC_SRC)
	bison -d $(YACC_SRC)

# flex: scanner.l → lex.yy.c
$(LEX_C): $(LEX_SRC) $(YACC_H)
	flex $(LEX_SRC)

# 청소
clean:
	rm -f $(TARGET) $(LEX_C) $(YACC_C) $(YACC_H)
