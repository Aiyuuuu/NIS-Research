/* simple_calculator.c
 *
 * Interactive calculator using only the standard C library.
 * - Uses scanf for all input
 * - Supports +, -, * and /
 * - Checks for division by zero
 * - Handles invalid input and allows quitting with 'q' or 'Q'
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char op;
    double a, b, result;
    int ch;

    puts("Simple interactive calculator");
    puts("Supported operators: +  -  *  /");
    puts("Type 'q' or 'Q' at the operator prompt to quit.");

    while (1) {
        /* Read operator (or quit command). The leading space in the format
           string skips any leftover whitespace/newline. */
        printf("\nEnter operator (+ - * /) or q to quit: ");
        if (scanf(" %c", &op) != 1) {
            /* EOF or input error */
            fprintf(stderr, "Input error or EOF detected. Exiting.\n");
            break;
        }

        if (op == 'q' || op == 'Q') {
            puts("Exiting calculator. Goodbye!");
            break;
        }

        if (op != '+' && op != '-' && op != '*' && op != '/') {
            printf("Invalid operator '%c'. Please enter one of +, -, *, / or q to quit.\n", op);
            /* Clear rest of the line to remove unexpected input */
            while ((ch = getchar()) != '\n' && ch != EOF) { /* discard */ }
            continue;
        }

        /* Read first number */
        printf("Enter first number: ");
        if (scanf("%lf", &a) != 1) {
            printf("Invalid number input. Please try again.\n");
            /* Clear rest of the line */
            while ((ch = getchar()) != '\n' && ch != EOF) { /* discard */ }
            continue;
        }

        /* Read second number */
        printf("Enter second number: ");
        if (scanf("%lf", &b) != 1) {
            printf("Invalid number input. Please try again.\n");
            /* Clear rest of the line */
            while ((ch = getchar()) != '\n' && ch != EOF) { /* discard */ }
            continue;
        }

        /* Clear any trailing characters on the line (helpful if user typed extra) */
        while ((ch = getchar()) != '\n' && ch != EOF) { /* discard */ }

        /* Perform the requested operation with safety checks */
        switch (op) {
            case '+':
                result = a + b;
                printf("%.10g %c %.10g = %.10g\n", a, op, b, result);
                break;
            case '-':
                result = a - b;
                printf("%.10g %c %.10g = %.10g\n", a, op, b, result);
                break;
            case '*':
                result = a * b;
                printf("%.10g %c %.10g = %.10g\n", a, op, b, result);
                break;
            case '/':
                if (b == 0.0) {
                    puts("Error: division by zero is undefined.");
                } else {
                    result = a / b;
                    printf("%.10g %c %.10g = %.10g\n", a, op, b, result);
                }
                break;
            default:
                /* This should not happen because we validated op earlier */
                fprintf(stderr, "Unexpected operator. This is a program error.\n");
                break;
        }
    }

    return 0;
}

