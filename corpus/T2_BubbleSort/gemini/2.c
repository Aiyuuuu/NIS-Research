#include <stdio.h>

// Function to swap two integer elements.
// It takes pointers to the integers to modify their values directly.
void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Function to implement the Bubble Sort algorithm.
// It takes an integer array and its size as input.
void bubbleSort(int arr[], int n) {
    int i, j;
    // The outer loop runs for n-1 passes. After each pass, the largest
    // unsorted element "bubbles up" to its correct position at the end.
    for (i = 0; i < n - 1; i++) {
        // The inner loop performs the comparisons and swaps.
        // The range of the inner loop shrinks with each pass (n-i-1),
        // because the elements at the end of the array are already sorted.
        for (j = 0; j < n - i - 1; j++) {
            // For ascending order, if the current element is greater
            // than the next one, swap them.
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// Function to print the elements of an array.
void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// The main function where the program execution begins.
int main() {
    int n, i;

    // 1. Get the number of elements from the user.
    printf("Enter the number of elements you want to sort: ");
    scanf("%d", &n);

    // Basic input validation
    if (n <= 0) {
        printf("The number of elements must be positive.\n");
        return 1; // Exit with an error code
    }

    // Declare an array of the specified size (Variable Length Array - C99 standard).
    int arr[n];

    // 2. Get the integer inputs from the user.
    printf("Enter %d integers, one by one:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Optional: Display the array before sorting.
    // printf("Unsorted array: \n");
    // printArray(arr, n);

    // 3. Call the bubbleSort function to sort the array.
    bubbleSort(arr, n);

    // 4. Display the final sorted array.
    printf("\nSorted array in ascending order:\n");
    printArray(arr, n);

    return 0; // Indicate successful execution
}
