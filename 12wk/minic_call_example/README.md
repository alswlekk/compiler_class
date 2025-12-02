# MiniC 함수 호출 예제 프로젝트 (2개 인자)

이 프로젝트는 `int` 타입만 있는 간단한 MiniC 언어로,

```c
int add(int a, int b)
```

처럼 **2개 인자를 받는 함수 호출**을 파싱하고, 간단한 3-address style IR로 출력하는 예제입니다.

## 빌드 방법

```bash
make
```

- `flex`, `bison`, `gcc` 가 설치되어 있어야 합니다.

## 실행 예시

```bash
./minic test/add2.minic
```

대략 다음과 비슷한 IR이 출력됩니다.

```text
func add(a, b)
{
  ; var s
  t0 = a
  t1 = b
  t2 = t0 + t1
  s = t2
  return s
}

func main()
{
  ; var x
  ; var y
  ; var result
  t3 = 3
  x = t3
  t4 = 4
  y = t4
  t5 = x
  t6 = y
  param t5
  param t6
  t7 = call add, 2
  result = t7
  return result
}
```

(실제 출력은 구현에 따라 조금 다를 수 있습니다.)

## 파일 구조

- `src/lexer.l` : Flex 기반 MiniC lexer
- `src/parser.y` : Bison 기반 MiniC parser (함수 정의/호출 지원)
- `include/ast.h`, `src/ast.c` : AST 자료구조 및 생성 함수
- `include/ir.h`, `src/ir.c` : 간단한 IR 생성 및 출력
- `src/main.c` : `yyparse()`를 호출하고 IR 출력
- `test/add2.minic` : 2개 인자를 받는 `add(a, b)` 예제 프로그램
