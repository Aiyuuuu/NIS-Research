#include <stdio.h>

int main() {
    // Declare variables to hold the two numbers, the operator, and the result.
    // We use 'double' to allow for decimal numbers (e.g., 3.14).
    double num1, num2;
    char operator;
    double result;

    // --- Input ---
    // Prompt the user to enter their calculation.
    printf("Enter a simple arithmetic expression (e.g., 5 * 2):\n");
    
    // Read the user's input.
    // scanf reads a double (%lf), then a character (%c), then another double.
    // The space before %c is important to consume any whitespace (like spaces or newlines)
    // left in the input buffer.
    if (scanf("%lf %c %lf", &num1, &operator, &num2) != 3) {
        // If scanf does not successfully read 3 items, the input format is wrong.
        printf("Error: Invalid input format.\n");
        return 1; // Exit with an error code
    }

    // --- Processing ---
    // Use a switch statement to determine which operation to perform.
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
            // Special check for division by zero, which is not allowed.
            if (num2 == 0) {
                printf("Error: Division by zero is not allowed.\n");
                return 1; // Exit the program with an error code
            }
            result = num1 / num2;
            break;

        default:
            // If the operator is not one of the above, it's invalid.
            printf("Error: Invalid operator '%c'. Please use +, -, *, or /.\n", operator);
            return 1; // Exit the program with an error code
    }

    // --- Output ---
    // Print the formatted result to the terminal.
    // "%.2lf" prints the double with two digits after the decimal point.
    printf("Result: %.2lf %c %.2lf = %.2lf\n", num1, operator, num2, result);

    // Return 0 to indicate that the program executed successfully.
    return 0;
}
