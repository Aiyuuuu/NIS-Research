#include <stdio.h>
#include <stdbool.h> // For using bool, true, false

#define MAX_SIZE 100 // Define a maximum size for the array

// A utility function to swap two integer values
void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

/**
 * Implements the Bubble Sort algorithm to sort an array of integers in-place.
 * 
 * @param arr The array of integers to be sorted.
 * @param n   The number of elements in the array.
 */
void bubbleSort(int arr[], int n) {
    int i, j;
    bool swapped;

    // The outer loop runs for each pass. After each pass, the largest
    // unsorted element "bubbles up" to its correct position.
    for (i = 0; i < n - 1; i++) {
        swapped = false;

        // The inner loop performs the comparisons and swaps.
        // The boundary `n - 1 - i` is an optimization, as elements after
        // this point are already in their correct, sorted positions.
        for (j = 0; j < n - 1 - i; j++) {
            // Compare adjacent elements
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true; // A swap occurred in this pass
            }
        }

        // OPTIMIZATION: If no two elements were swapped by the inner loop,
        // then the array is already sorted, and we can break early.
        if (swapped == false) {
            break;
        }
    }
}

// A utility function to print an array
void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// The main driver function
int main() {
    int arr[MAX_SIZE];
    int n;

    // 1. Read the number of elements from the user
    printf("Enter the number of elements (1 to %d): ", MAX_SIZE);
    scanf("%d", &n);

    // Input validation
    if (n <= 0 || n > MAX_SIZE) {
        printf("Error: Number of elements must be between 1 and %d.\n", MAX_SIZE);
        return 1; // Indicate an error
    }

    // 2. Read the elements into the array
    printf("Enter %d integers separated by spaces:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // 3. Display the original array
    printf("Original array: \n");
    printArray(arr, n);

    // 4. Call the bubbleSort function to sort the array
    bubbleSort(arr, n);

    // 5. Display the sorted array
    printf("Sorted array: \n");
    printArray(arr, n);

    return 0; // Indicate successful execution
}
