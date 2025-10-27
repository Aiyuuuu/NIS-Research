#include <stdio.h>

int main() {
    // Declare variables to hold the operator and the two numbers (operands).
    // Using 'double' allows for floating-point calculations (e.g., 3.5 / 2.0).
    char operator;
    double num1, num2, result;

    // --- Step 1: Get input from the user ---

    // Prompt for and read the first number
    printf("Enter the first number: ");
    scanf("%lf", &num1);

    // Prompt for and read the operator
    // The space before %c is important! It consumes any leftover newline/whitespace
    // characters from the previous scanf, preventing issues.
    printf("Enter an operator (+, -, *, /): ");
    scanf(" %c", &operator);

    // Prompt for and read the second number
    printf("Enter the second number: ");
    scanf("%lf", &num2);

    // --- Step 2: Select the operation and compute the result ---

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
            // Check for division by zero, which is an undefined operation.
            if (num2 != 0) {
                result = num1 / num2;
            } else {
                // If division by zero is attempted, print an error and exit.
                printf("Error: Division by zero is not allowed.\n");
                return 1; // Exit with an error code
            }
            break;

        // If the operator is not one of the valid options, show an error.
        default:
            printf("Error: Invalid operator entered.\n");
            return 1; // Exit with an error code
    }

    // --- Step 3: Display the final result ---

    // The %g format specifier is used to display the result cleanly,
    // removing trailing zeros (e.g., 8.0 becomes 8).
    printf("Result: %g %c %g = %g\n", num1, operator, num2, result);

    return 0; // Indicate that the program finished successfully
}
