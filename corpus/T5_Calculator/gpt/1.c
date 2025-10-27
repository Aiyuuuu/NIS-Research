/* simple_calculator.c
   Simple interactive calculator using standard C library.
   Compile: gcc -std=c11 -Wall -Wextra -o simple_calculator simple_calculator.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
    double a, b, result = 0.0;
    char op[8]; /* read operator as a short string to tolerate whitespace */

    /* Prompt for first number */
    printf("Enter first number: ");
    if (scanf("%lf", &a) != 1) {
        fprintf(stderr, "Invalid input for first number.\n");
        return 1;
    }

    /* Prompt for operator */
    printf("Enter operator (+, -, *, /): ");
    if (scanf(" %7s", op) != 1) {
        fprintf(stderr, "Invalid input for operator.\n");
        return 1;
    }

    /* Prompt for second number */
    printf("Enter second number: ");
    if (scanf("%lf", &b) != 1) {
        fprintf(stderr, "Invalid input for second number.\n");
        return 1;
    }

    /* Perform calculation based on operator */
    switch (op[0]) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            /* protect against division by zero */
            if (b == 0.0) {
                fprintf(stderr, "Error: Division by zero.\n");
                return 1;
            }
            result = a / b;
            break;
        default:
            fprintf(stderr, "Error: Unsupported operator '%s'. Use +, -, * or /.\n", op);
            return 1;
    }

    /* Print the result */
    printf("\nResult: %.10g %c %.10g = %.10g\n", a, op[0], b, result);

    return 0;
}

