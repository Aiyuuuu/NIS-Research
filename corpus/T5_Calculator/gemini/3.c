#include <stdio.h> // This is the standard input/output library for functions like printf and scanf

// The main function is the entry point of every C program
int main() {

    // --- 1. Declare Variables ---
    char op;            // To store the operator (+, -, *, /)
    double num1, num2;  // To store the two numbers (using double for decimal values)

    // --- 2. Get User Input ---
    printf("--- A Simple C Calculator ---\n");

    // Prompt the user for the first number
    printf("Enter the first number: ");
    scanf("%lf", &num1); // Read a double-precision floating-point number

    // Prompt the user for an operator
    printf("Enter an operator (+, -, *, /): ");
    scanf(" %c", &op); // The space before %c is important! It consumes any leftover whitespace
                       // (like the 'Enter' key press) from the previous input.

    // Prompt the user for the second number
    printf("Enter the second number: ");
    scanf("%lf", &num2);

    // --- 3. Perform Calculation using a switch statement ---
    printf("\n"); // Print a newline for better formatting

    switch (op) {
        case '+':
            printf("%.2lf + %.2lf = %.2lf\n", num1, num2, num1 + num2);
            break; // Exit the switch block

        case '-':
            printf("%.2lf - %.2lf = %.2lf\n", num1, num2, num1 - num2);
            break;

        case '*':
            printf("%.2lf * %.2lf = %.2lf\n", num1, num2, num1 * num2);
            break;

        case '/':
            // --- 4. Check for Division by Zero ---
            if (num2 == 0) {
                printf("Error: Division by zero is not allowed.\n");
            } else {
                printf("%.2lf / %.2lf = %.2lf\n", num1, num2, num1 / num2);
            }
            break;

        // If the operator doesn't match any of the cases
        default:
            printf("Error: You have entered an invalid operator.\n");
            printf("Please use one of the following: +, -, *, /\n");
    }

    // --- 5. Exit the program ---
    return 0; // Tell the operating system that the program executed successfully
}
