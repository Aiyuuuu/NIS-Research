/**
 * @file binary_search_tool.c
 * @brief A standalone C command-line tool to perform binary search on a sorted integer array.
 *
 * This program reads the size of a sorted array, the array elements, and a 
 * target value from standard input. It then uses a binary search algorithm
 * to find the index of the target value and prints the result.
 *
 * How to Compile and Run:
 * 1. Compile: gcc -o binary_search_tool binary_search_tool.c -Wall
 * 2. Run: ./binary_search_tool
 *
 * Example Interaction:
 * Enter the number of elements in the sorted array: 8
 * Enter the 8 sorted elements separated by spaces: 2 5 8 12 16 23 38 56
 * Enter the target value to search for: 23
 * Element 23 found at index: 5
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Performs binary search on a sorted integer array to find a target value.
 *
 * This function implements an iterative binary search algorithm.
 * 
 * @param arr The sorted array of integers to search in.
 * @param size The number of elements in the array.
 * @param target The integer value to search for.
 * @return The index of the target element if found; otherwise, -1.
 */
int binarySearch(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        // Calculate mid-point to avoid potential overflow with (left + right) / 2
        int mid = left + (right - left) / 2;

        // Check if target is present at mid
        if (arr[mid] == target) {
            return mid;
        }

        // If target is greater, ignore the left half
        if (arr[mid] < target) {
            left = mid + 1;
        } 
        // If target is smaller, ignore the right half
        else {
            right = mid - 1;
        }
    }

    // If we reach here, the element was not present in the array
    return -1;
}

/**
 * @brief Main function to drive the binary search tool.
 *
 * Reads array data and a target from stdin, calls binarySearch, 
 * and prints the result.
 */
int main() {
    int n; // Size of the array
    int *arr; // Pointer for the dynamically allocated array
    int target; // Value to search for
    int i; // Loop counter

    // 1. Read the size of the array
    printf("Enter the number of elements in the sorted array: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Error: Invalid input for array size. Please enter a positive integer.\n");
        return 1; // Exit with an error code
    }

    // 2. Allocate memory for the array
    arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return 1; // Exit with an error code
    }

    // 3. Read the sorted array elements from the user
    printf("Enter the %d sorted elements separated by spaces: ", n);
    for (i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Error: Invalid input while reading array elements.\n");
            free(arr); // Clean up allocated memory
            return 1;
        }
    }

    // 4. Read the target value to search for
    printf("Enter the target value to search for: ");
    if (scanf("%d", &target) != 1) {
        fprintf(stderr, "Error: Invalid input for target value.\n");
        free(arr); // Clean up allocated memory
        return 1;
    }

    // 5. Call the binary search function
    int result_index = binarySearch(arr, n, target);

    // 6. Print the result
    if (result_index != -1) {
        printf("Element %d found at index: %d\n", target, result_index);
    } else {
        printf("Element %d not found in the array.\n", target);
    }

    // 7. Free the dynamically allocated memory
    free(arr);

    return 0; // Successful execution
}
