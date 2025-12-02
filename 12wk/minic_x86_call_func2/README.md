# MiniC x86 함수 호출 예제 (2개 인자)

- `parser/lexer.l`, `parser/parser.y` 로 분리.
- `int add(int a, int b)` 같은 **2개 인자 함수 호출**을 파싱해서
- 바로 x86-64 SysV 어셈블리를 출력하는 간단 컴파일러입니다.

## 빌드

```bash
make
```

`flex`, `bison`, `gcc` 필요.

## 사용법

```bash
./minic_x86 test/add2.minic > out.s
gcc -no-pie -o out out.s
./out
echo $?
```

마지막 `echo $?` 로 프로그램 반환값(여기서는 `3 + 4 = 7`)을 확인할 수 있습니다.

## 폴더 구조

- `parser/lexer.l` : Flex lexer
- `parser/parser.y` : Bison parser (함수/호출, 2개 인자 이상도 문법상 지원)
- `include/ast.h` : AST 정의
- `include/codegen_x86.h` : x86 코드 생성기 인터페이스
- `src/ast.c` : AST 생성 함수
- `src/codegen_x86.c` : 매우 단순한 x86-64 코드 생성기
- `src/main.c` : 엔트리, `yyparse()` → `gen_x86_program()`
- `test/add2.minic` : 2개 인자를 받는 `add(a, b)` 예제
