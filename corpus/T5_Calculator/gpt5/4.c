/* simple_calculator.c - simplified version
 * - Prompts the user to enter two operands and an operator
 * - Calls calculate() to perform + - * /
 * - Prints the result
 *
 * Compile: gcc -std=c11 -Wall -Wextra -o simple_calculator simple_calculator.c
 */

#include <stdio.h>
#include <stdlib.h>

/* calculate: perform binary operation on a and b.
 * Returns 0 on success and sets *out; returns non-zero on error.
 */
int calculate(double a, double b, char op, double *out) {
    if (!out) return -1;
    switch (op) {
        case '+': *out = a + b; return 0;
        case '-': *out = a - b; return 0;
        case '*': *out = a * b; return 0;
        case '/':
            if (b == 0.0) return 2; /* division by zero */
            *out = a / b;
            return 0;
        default:
            return 1; /* unsupported operator */
    }
}

int main(void) {
    double a, b, result;
    char op;

    puts("Simple Calculator");

    if (printf("Enter first operand: ") < 0 || scanf("%lf", &a) != 1) {
        fprintf(stderr, "Invalid input for first operand.\n");
        return EXIT_FAILURE;
    }

    if (printf("Enter operator (+ - * /): ") < 0 || scanf(" %c", &op) != 1) {
        fprintf(stderr, "Invalid input for operator.\n");
        return EXIT_FAILURE;
    }

    if (printf("Enter second operand: ") < 0 || scanf("%lf", &b) != 1) {
        fprintf(stderr, "Invalid input for second operand.\n");
        return EXIT_FAILURE;
    }

    int err = calculate(a, b, op, &result);
    if (err == 0) {
        printf("Result: %g\n", result);
        return EXIT_SUCCESS;
    }

    if (err == 2) {
        fprintf(stderr, "Error: division by zero.\n");
    } else if (err == 1) {
        fprintf(stderr, "Error: unsupported operator '%c'.\n", op);
    } else {
        fprintf(stderr, "Error: calculation failed (code %d).\n", err);
    }

    return EXIT_FAILURE;
}

