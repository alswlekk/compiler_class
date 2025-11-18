# ===== Scanner Example Makefile =====

# 자동 .exe 확장자 (Windows_NT 환경변수로 판별)
ifeq ($(OS),Windows_NT)
  EXE := .exe
else
  EXE :=
endif

# 설정
CC      := gcc
CSTD    := -std=c11
WARN    := -Wall -Wextra -Wshadow -Wpointer-arith -Wconversion
OPT_REL := -O2
OPT_DBG := -O0 -g3
DEFS    :=
INCS    := -I.
LIBS    :=

# 타겟 이름
TARGET  := scanner$(EXE)

# 소스/오브젝트
SRCS := main.c lexer.c
OBJS := $(SRCS:.c=.o)

# 기본: release 빌드
.PHONY: all
all: release

# 릴리즈 빌드
.PHONY: release
release: CFLAGS := $(CSTD) $(WARN) $(OPT_REL) $(DEFS) $(INCS)
release: $(TARGET)

# 디버그 빌드
.PHONY: debug
debug: CFLAGS := $(CSTD) $(WARN) $(OPT_DBG) $(DEFS) $(INCS)
debug: clean $(TARGET)

# 링크
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# 컴파일 규칙
%.o: %.c token.h lexer.h
	$(CC) $(CFLAGS) -c $< -o $@

# 실행 헬퍼: 인자 전달
.PHONY: run
run: $(TARGET)
	./$(TARGET) "int sum = a1 + 23;"

# 정리
.PHONY: clean
clean:
	$(RM) $(OBJS) $(TARGET)

# 포맷(옵션): clang-format 사용 시
.PHONY: fmt
fmt:
	@command -v clang-format >/dev/null 2>&1 && clang-format -i *.c *.h || echo "clang-format 미설치"

# 의존성 (선택): GCC의 -MMD -MP 사용하려면 위 CFLAGS에 추가하고 아래 활성화
#CFLAGS += -MMD -MP
#-include $(SRCS:.c=.d)
