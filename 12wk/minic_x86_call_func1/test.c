// 함수 호출 지원 테스트용 MiniC 코드
// 이 코드는 다음과 같은 C 함수와 함께 링크해서 사용할 수 있습니다:
//
//   // support.c
//   int add(int a, int b) {
//       return a + b;
//   }
//
// 사용 방법 예시:
//   ./minic_x86 test.c
//   gcc -no-pie out.s support.c -o prog
//   ./prog   (입력: 10 20  → 출력: 30)
//
// MiniC 소스:

int x;
int y;
int s;

scanf(&x);
scanf(&y);

s = add(x, y);
printf(s);
