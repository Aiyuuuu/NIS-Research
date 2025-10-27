/**
 * @file simple_calculator.c
 * @brief A simple interactive command-line calculator.
 *
 * This program prompts the user to enter an expression consisting of two numbers
 * and an operator (+, -, *, /). It then performs the calculation and
 * prints the result to the console. The program includes robust error
 * handling for invalid input, invalid operators, and division by zero.
 *
 * It is a single, self-contained file using only the standard C library.
 *
 * To compile and run:
 *   gcc -Wall -Wextra -std=c11 -o calculator simple_calculator.c
 *   ./calculator
 */

#include <stdio.h> // For standard input/output functions (printf, scanf)

int main(void) {
    double num1, num2;
    char operator;
    double result;

    // 1. Prompt the user for input
    printf("Enter an expression (e.g., 5 * 3.14): ");

    // 2. Read the input from the user
    // The scanf function returns the number of items successfully read.
    // We expect to read 3 items: a double, a char, and another double.
    // The space before %c is crucial to consume any whitespace (like a newline)
    // left in the input buffer from previous inputs, making it more robust.
    if (scanf("%lf %c %lf", &num1, &operator, &num2) != 3) {
        printf("Error: Invalid input format.\n");
        printf("Please enter two numbers and an operator, separated by spaces.\n");
        return 1; // Exit with an error code
    }

    // 3. Perform the calculation based on the operator
    switch (operator) {
        case '+':
            result = num1 + num2;
            break;

        case '-':
            result = num1 - num2;
            break;

        case '*':
            result = num1 * num2;
            break;

        case '/':
            // Critical check: handle division by zero
            if (num2 == 0.0) {
                printf("Error: Division by zero is not allowed.\n");
                return 1; // Exit with an error code
            }
            result = num1 / num2;
            break;

        default:
            // Handle cases where the operator is not one of the valid ones
            printf("Error: Invalid operator '%c'.\n", operator);
            printf("Supported operators are +, -, *, /.\n");
            return 1; // Exit with an error code
    }

    // 4. Print the result
    // The %g format specifier is used for a cleaner output. It automatically
    // chooses between %f (decimal notation) and %e (scientific notation)
    // and removes trailing zeros (e.g., 5.000000 becomes 5).
    printf("%g %c %g = %g\n", num1, operator, num2, result);

    return 0; // Indicate successful execution
}
