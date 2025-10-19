#include <stdio.h>

int add(int a, int b) {
    // small difference: extra variable and comment
    int result = a + b;
    return result;
}

int main() {
    int x = 5, y = 3;
    printf("Sum of %d and %d is %d\n", x, y, add(x, y));
    return 0;
}
