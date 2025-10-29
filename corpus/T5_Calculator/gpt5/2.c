/* simple_calculator.c
   A minimal interactive calculator (C, C99). Compile with:
   gcc -std=c99 -Wall -Wextra simple_calculator.c -o simple_calculator
*/

#include <stdio.h>

int main(void) {
    double a, b;
    char op;
    char again = 'n';

    printf("Simple Interactive Calculator\n");
    do {
        printf("\nEnter first number: ");
        if (scanf("%lf", &a) != 1) {
            printf("Invalid input for number. Please try again.\n");
            /* clear bad input */
            while (getchar() != '\n');
            continue;
        }

        printf("Enter operator (+, -, *, /): ");
        /* leading space in format skips any leftover whitespace/newline */
        if (scanf(" %c", &op) != 1) {
            printf("Failed to read operator. Please try again.\n");
            while (getchar() != '\n');
            continue;
        }

        printf("Enter second number: ");
        if (scanf("%lf", &b) != 1) {
            printf("Invalid input for number. Please try again.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (op) {
            case '+':
                printf("%.10g %c %.10g = %.10g\n", a, op, b, a + b);
                break;
            case '-':
                printf("%.10g %c %.10g = %.10g\n", a, op, b, a - b);
                break;
            case '*':
                printf("%.10g %c %.10g = %.10g\n", a, op, b, a * b);
                break;
            case '/':
                if (b == 0.0) {
                    printf("Error: Division by zero is not allowed.\n");
                } else {
                    printf("%.10g %c %.10g = %.10g\n", a, op, b, a / b);
                }
                break;
            default:
                printf("Error: Unsupported operator '%c'. Use +, -, * or /.\n", op);
        }

        printf("Perform another calculation? (y/n): ");
        /* read the user's reply (skip whitespace) */
        if (scanf(" %c", &again) != 1) {
            /* if reading fails, exit loop */
            break;
        }

    } while (again == 'y' || again == 'Y');

    printf("Goodbye!\n");
    return 0;
}

