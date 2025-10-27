/**
 * @file calculator.c
 * @brief A simple standalone command-line arithmetic calculator in C.
 *
 * This program prompts the user to enter an expression with two operands
 * and one operator (e.g., 5 * 3). It validates the input, performs the
 * calculation, and prints the result or an appropriate error message.
 */

#include <stdio.h>
#include <stdlib.h> // For EXIT_SUCCESS and EXIT_FAILURE

// Enum to define clear status codes for the calculation function.
// This is more readable and maintainable than using magic numbers like 0, 1, 2.
typedef enum {
    SUCCESS = 0,
    ERR_INVALID_OPERATOR,
    ERR_DIVISION_BY_ZERO
} StatusCode;

/**
 * @brief Performs a basic arithmetic operation.
 *
 * @param operand1 The first number (left-hand side).
 * @param operand2 The second number (right-hand side).
 * @param operator The character representing the operation (+, -, *, /).
 * @param result A pointer to a double where the result will be stored.
 *
 * @return A StatusCode indicating the outcome of the operation.
 *         Returns SUCCESS if the calculation was successful, or an error
 *         code otherwise.
 */
StatusCode calculate(double operand1, double operand2, char op, double *result) {
    switch (op) {
        case '+':
            *result = operand1 + operand2;
            break;
        case '-':
            *result = operand1 - operand2;
            break;
        case '*':
            *result = operand1 * operand2;
            break;
        case '/':
            // Handle the division by zero error case.
            if (operand2 == 0) {
                return ERR_DIVISION_BY_ZERO;
            }
            *result = operand1 / operand2;
            break;
        default:
            // Handle the case where the operator is not one of the valid ones.
            return ERR_INVALID_OPERATOR;
    }
    return SUCCESS;
}

/**
 * @brief The main entry point of the program.
 *
 * Prompts the user for input, calls the calculate function, and handles
 * printing the result or any errors that occur.
 */
int main() {
    double operand1, operand2;
    char operator_char;
    double result;
    int items_read;

    // Prompt the user for input with a clear example format.
    printf("Enter an expression (e.g., 5 * 3): ");

    // Use scanf to parse the input. We expect to read 3 items:
    // a double, a character, and another double.
    // The space before %c is crucial to consume any whitespace (like spaces or newlines)
    // left in the input buffer, for instance, after typing the first number.
    items_read = scanf("%lf %c %lf", &operand1, &operator_char, &operand2);

    // Validate the input. If scanf did not read exactly 3 items, the
    // format was incorrect.
    if (items_read != 3) {
        fprintf(stderr, "Error: Invalid input format. Please use the format: number operator number\n");
        return EXIT_FAILURE; // Indicate an error occurred.
    }

    // Call the calculate function and get its status.
    StatusCode status = calculate(operand1, operand2, operator_char, &result);

    // Check the status and print the result or an error message.
    switch (status) {
        case SUCCESS:
            // Using %g is often cleaner than %f as it removes trailing zeros.
            printf("Result: %g %c %g = %g\n", operand1, operator_char, operand2, result);
            break;
        case ERR_INVALID_OPERATOR:
            fprintf(stderr, "Error: Invalid operator '%c'. Supported operators are +, -, *, /\n", operator_char);
            return EXIT_FAILURE;
        case ERR_DIVISION_BY_ZERO:
            fprintf(stderr, "Error: Division by zero is not allowed.\n");
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS; // Indicate successful execution.
}
