int main() {
  int i = 0, sum = 0;
  for (int k = 0; k < 3; k = k + 1)
    sum = sum + k;

  for (i = 0; i < 5; i = i + 1) {
    sum = sum + i;
  }

  for (;;)
    break; 
  return sum;
}
