int sum(int a, int b) { return a + b; }
float g(int x) { return x + 0.5; }
void v() { return; }

int main() {
  int x = 0;
  float f = 3.0;
  x = f;           // float→int 축소 경고
  y = 1;           // 미선언 사용
  int y = 10, z = 1.2; // 1.2는 float→int 축소 경고
  if (x < y) x = x + y;
  return sum(x, y, 42); // 인자 수 불일치
}
