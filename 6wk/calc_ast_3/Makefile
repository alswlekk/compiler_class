# ==== Portable Makefile for calc_ast (Linux & macOS) =========================
# Files: parser.y, scanner.l, ast.c, ast.h, main.c
# Output: ./calc_ast
#
# macOS(Homebrew)에서 구버전 /usr/bin/bison 문제를 피하기 위해
# brew의 bison/flex가 있으면 자동으로 사용합니다.
# ============================================================================

# ---- toolchain --------------------------------------------------------------
CC       ?= cc
CFLAGS   ?= -Wall -Wextra -O2
CPPFLAGS ?=
LDFLAGS  ?=
LDLIBS   ?= -lm -lfl        # flex 러ntime (libfl) + math

# ---- OS detection & Homebrew bison/flex ------------------------------------
UNAME_S := $(shell uname -s)

# 기본값
BISON ?= bison
FLEX  ?= flex

# macOS라면 brew 경로 우선 사용 (있을 때만)
ifeq ($(UNAME_S),Darwin)
BREW_PREFIX := $(shell command -v brew >/dev/null 2>&1 && brew --prefix)
ifneq ($(BREW_PREFIX),)
  # Use Homebrew-installed bison/flex
  BISON := $(BREW_PREFIX)/opt/bison/bin/bison
  FLEX  := $(BREW_PREFIX)/opt/flex/bin/flex
  # flex 헤더/라이브러리 경로
  CPPFLAGS += -I$(BREW_PREFIX)/opt/flex/include
  LDFLAGS  += -L$(BREW_PREFIX)/opt/flex/lib
endif
endif

# ---- targets ----------------------------------------------------------------
APP = calc_ast

SRC_C = ast.c main.c
OBJ   = lex.yy.o parser.tab.o $(SRC_C:.c=.o)

.PHONY: all clean distclean versions run

all: $(APP)

# 최종 바이너리
$(APP): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

# bison: parser.y -> parser.tab.c / parser.tab.h
parser.tab.c parser.tab.h: parser.y
	$(BISON) -Wall -Wcounterexamples -d -o parser.tab.c $<

# flex: scanner.l -> lex.yy.c  (parser.tab.h가 먼저 필요)
lex.yy.c: scanner.l parser.tab.h
	$(FLEX) -o $@ $<

# C 컴파일 규칙
%.o: %.c ast.h parser.tab.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# flex/bison 산출물도 오브젝트로
lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

parser.tab.o: parser.tab.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# 편의: 버전 확인
versions:
	@echo "CC     = $(shell $(CC) --version | head -n1)"
	@echo "BISON  = $(shell $(BISON) --version | head -n1)"
	@echo "FLEX   = $(shell $(FLEX) --version  | head -n1)"
	@echo "OS     = $(UNAME_S)"
	@echo "BREW   = $(BREW_PREFIX)"

# 실행 헬퍼
run: $(APP)
	./$(APP)

# 정리
clean:
	$(RM) $(OBJ) lex.yy.c parser.tab.c parser.tab.h

distclean: clean
	$(RM) $(APP)
