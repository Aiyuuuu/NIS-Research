#include <stdio.h>

// Define a constant for the maximum array size to avoid "magic numbers".
#define MAX_SIZE 100

// Function Prototypes (declarations)
// It's good practice to declare functions before you use them.
void swap(int *a, int *b);
void bubbleSort(int arr[], int n);
void printArray(int arr[], int size);

/**
 * The main function is the entry point of every C program.
 */
int main() {
    int arr[MAX_SIZE]; // Declare an integer array with a fixed maximum size.
    int n;             // Variable to store the actual number of elements the user wants.

    // 1. Get user input
    printf("--- Bubble Sort Program ---\n");
    printf("Enter the number of elements to sort (up to %d): ", MAX_SIZE);
    scanf("%d", &n);

    // Input validation: Check if the number of elements is valid.
    if (n <= 0 || n > MAX_SIZE) {
        printf("Invalid number of elements. Please enter a number between 1 and %d.\n", MAX_SIZE);
        return 1; // Exit the program with an error code.
    }

    printf("Enter %d integers, separated by spaces:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // 2. Show the original array
    printf("\nOriginal array: ");
    printArray(arr, n);

    // 3. Sort the array using Bubble Sort
    bubbleSort(arr, n);

    // 4. Print the sorted array
    printf("Sorted array:   ");
    printArray(arr, n);
    
    return 0; // Indicate that the program finished successfully.
}

/**
 * @brief Swaps the values of two integer variables.
 * @param a Pointer to the first integer.
 * @param b Pointer to the second integer.
 * We use pointers here so the function can modify the original variables in the calling function.
 */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Sorts an array of integers using the Bubble Sort algorithm.
 * @param arr The array to be sorted.
 * @param n   The number of elements in the array.
 */
void bubbleSort(int arr[], int n) {
    int i, j;
    // Outer loop for the number of passes.
    // After each pass, the largest unsorted element "bubbles up" to its correct position.
    for (i = 0; i < n - 1; i++) {

        // Inner loop for comparing adjacent elements in each pass.
        // The range of the inner loop decreases with each pass, because the
        // elements at the end of the array are already sorted.
        for (j = 0; j < n - i - 1; j++) {
            
            // Compare the adjacent elements.
            // For descending order, use < instead of >
            if (arr[j] > arr[j + 1]) {
                // If they are in the wrong order, swap them.
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

/**
 * @brief Prints the elements of an integer array.
 * @param arr The array to print.
 * @param size The number of elements in the array.
 */
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
