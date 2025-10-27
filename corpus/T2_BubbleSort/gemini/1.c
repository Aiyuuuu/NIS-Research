/**
 * @file bubble_sort_static.c
 * @brief A C program to sort a fixed number of integers using Bubble Sort.
 *
 * This program demonstrates a simple implementation of the Bubble Sort
 * algorithm using a fixed-size array (static allocation). It reads up to
 * a predefined maximum number of integers from standard input, sorts them
 * in ascending order, and prints the result. This version avoids dynamic
 * memory management.
 *
 * How to compile and run:
 * 1. Compile: gcc -Wall -Wextra -std=c99 -o bubble_sort_static bubble_sort_static.c
 * 2. Run: ./bubble_sort_static
 * 3. Enter integers separated by spaces or newlines.
 * 4. Press Ctrl+D (on Unix/Linux) or Ctrl+Z then Enter (on Windows) to
 *    signal the end of input.
 */

#include <stdio.h>   // For standard input/output
#include <stdlib.h>  // For exit codes (EXIT_SUCCESS, EXIT_FAILURE)
#include <stdbool.h> // For the boolean type (true, false)

// Define the maximum number of integers the program can handle.
#define MAX_NUMBERS 1000

/**
 * @brief Swaps the values of two integer pointers.
 * @param a Pointer to the first integer.
 * @param b Pointer to the second integer.
 */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Sorts an array of integers in ascending order using the Bubble Sort algorithm.
 *
 * This implementation includes an optimization to stop early if the array becomes
 * sorted before all passes are complete.
 *
 * @param arr The array of integers to be sorted.
 * @param n The number of elements in the array.
 */
void bubbleSort(int arr[], int n) {
    if (n <= 1) {
        return; // An array with 0 or 1 elements is already sorted.
    }

    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }

        // OPTIMIZATION: If no swaps occurred in a pass, the array is sorted.
        if (!swapped) {
            break;
        }
    }
}

/**
 * @brief Prints the elements of an integer array to standard output.
 * @param arr The array to print.
 * @param size The number of elements in the array.
 */
void printArray(const int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/**
 * @brief Main function to drive the program.
 *
 * It reads integers into a fixed-size array, calls the sorting function,
 * and prints the result.
 */
int main(void) {
    int numbers[MAX_NUMBERS];
    int size = 0;

    printf("Enter up to %d integers. Press Ctrl+D (Unix) or Ctrl+Z (Windows) to stop.\n", MAX_NUMBERS);

    // Read integers into the array, ensuring we don't exceed its bounds.
    // The loop stops when input ends (scanf fails) or the array is full.
    while (size < MAX_NUMBERS && scanf("%d", &numbers[size]) == 1) {
        size++;
    }

    if (size == 0) {
        printf("No numbers were entered.\n");
    } else {
        printf("\nOriginal list: ");
        printArray(numbers, size);

        // Sort the array.
        bubbleSort(numbers, size);

        printf("Sorted list:   ");
        printArray(numbers, size);
    }

    return EXIT_SUCCESS;
}
