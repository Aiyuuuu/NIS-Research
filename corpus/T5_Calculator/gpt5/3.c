/* simple_calculator.c
   A beginner-friendly basic calculator.
   Compile: gcc -std=c11 -Wall -Wextra -o simple_calculator simple_calculator.c
*/

#include <stdio.h>

int main(void) {
    double a, b;
    char op;

    /* Prompt for the first number */
    printf("Enter the first number: ");
    if (scanf("%lf", &a) != 1) {
        fprintf(stderr, "Invalid input for the first number.\n");
        return 1;
    }

    /* Prompt for the operator */
    printf("Enter an operator (+, -, *, /): ");
    /* the leading space in " %c" skips any leftover whitespace/newline */
    if (scanf(" %c", &op) != 1) {
        fprintf(stderr, "Invalid input for the operator.\n");
        return 1;
    }

    /* Prompt for the second number */
    printf("Enter the second number: ");
    if (scanf("%lf", &b) != 1) {
        fprintf(stderr, "Invalid input for the second number.\n");
        return 1;
    }

    /* Perform the calculation and print result (with division-by-zero check) */
    switch (op) {
        case '+':
            printf("%.6g %c %.6g = %.6g\n", a, op, b, a + b);
            break;
        case '-':
            printf("%.6g %c %.6g = %.6g\n", a, op, b, a - b);
            break;
        case '*':
            printf("%.6g %c %.6g = %.6g\n", a, op, b, a * b);
            break;
        case '/':
            if (b == 0.0) {
                fprintf(stderr, "Error: Division by zero is not allowed.\n");
                return 1;
            }
            printf("%.6g %c %.6g = %.6g\n", a, op, b, a / b);
            break;
        default:
            fprintf(stderr, "Error: Unsupported operator '%c'. Use +, -, * or /.\n", op);
            return 1;
    }

    return 0;
}

