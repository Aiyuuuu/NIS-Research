#include <stdio.h>

// Define the maximum number of integers the program can handle.
// You can change this value and recompile if you need to sort more numbers.
#define MAX_SIZE 100

/**
 * @brief Swaps two integer values.
 * 
 * @param a Pointer to the first integer.
 * @param b Pointer to the second integer.
 */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Sorts an array of integers using the Bubble Sort algorithm.
 * 
 * This function repeatedly steps through the list, compares adjacent elements,
 * and swaps them if they are in the wrong order. The pass through the list is
 * repeated until the list is sorted.
 * 
 * @param arr The array of integers to be sorted.
 * @param n The number of elements in the array.
 */
void bubbleSort(int arr[], int n) {
    int i, j;
    int swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = 0; // Flag to detect any swap in a pass
        // Last i elements are already in place, so the inner loop can avoid them
        for (j = 0; j < n - i - 1; j++) {
            // Compare adjacent elements
            if (arr[j] > arr[j + 1]) {
                // Swap them if they are in the wrong order
                swap(&arr[j], &arr[j + 1]);
                swapped = 1; // Set flag to true
            }
        }

        // If no two elements were swapped by inner loop, then the array is sorted
        if (swapped == 0) {
            break;
        }
    }
}

/**
 * @brief Prints the elements of an integer array to the console.
 * 
 * @param arr The array to print.
 * @param size The number of elements in the array.
 */
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/**
 * @brief Main function to read integers, sort them, and print the result.
 */
int main() {
    int numbers[MAX_SIZE];
    int count = 0;
    int num;

    printf("Enter up to %d integers separated by spaces or newlines.\n", MAX_SIZE);
    printf("Press Ctrl+D (Unix/Linux) or Ctrl+Z then Enter (Windows) to end input.\n");

    // Read numbers from standard input until EOF is reached or the array is full
    while (scanf("%d", &num) == 1) {
        // Check if the array has space
        if (count < MAX_SIZE) {
            numbers[count] = num;
            count++;
        } else {
            // If the array is full, inform the user and stop reading.
            printf("\nWarning: Maximum array size of %d reached. Ignoring further input.\n", MAX_SIZE);
            // We must break the loop to stop trying to read more numbers
            break;
        }
    }

    // Check if any numbers were entered
    if (count == 0) {
        printf("No numbers entered. Exiting.\n");
    } else {
        printf("\nOriginal list: \n");
        printArray(numbers, count);

        // Sort the array
        bubbleSort(numbers, count);

        printf("\nSorted list: \n");
        printArray(numbers, count);
    }
    
    return 0;
}
