// sample.c - Scanner test input

int sum = 0;

int main() {
    int a = 10, b = 20;
    sum = a + b * (a - 5);

    if (sum > 30) {
        return sum;
    } else {
        while (a > 0) {
            a = a - 1;
        }
    }
    return 0;
}
