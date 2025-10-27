/**
 * @file binary_search.c
 * @brief A C program to perform binary search on a sorted list of integers.
 *
 * This program reads a sorted list of n integers from standard input,
 * followed by a target integer. It then performs a binary search to find
 * the target's index and prints the result.
 *
 * Input Format:
 * line 1: An integer n, the number of elements.
 * next n lines: The sorted integers, one per line.
 * last line: The integer target to search for.
 *
 * Example Input:
 * 10
 * 2
 * 5
 * 8
 * 12
 * 16
 * 23
 * 38
 * 56
 * 72
 * 91
 * 23
 *
 * Example Output:
 * Target 23 found at index 5.
 */

#include <stdio.h>
#include <stdlib.h> // For malloc(), free(), and exit()

/**
 * @brief Performs an iterative binary search on a sorted integer array.
 *
 * This function searches for a `target` value within a sorted array `arr`.
 * It returns the index of the target if found, otherwise it returns -1.
 *
 * @param arr The sorted integer array to search in.
 * @param size The number of elements in the array.
 * @param target The integer value to search for.
 * @return The index of the `target` if found; otherwise, -1.
 */
int binary_search(int arr[], int size, int target) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        // Calculate mid index safely to prevent potential overflow
        // for very large arrays (low + high could exceed max int).
        int mid = low + (high - low) / 2;

        // Check if target is present at mid
        if (arr[mid] == target) {
            return mid; // Target found
        }
        
        // If target is greater, ignore the left half
        if (arr[mid] < target) {
            low = mid + 1;
        }
        // If target is smaller, ignore the right half
        else { // arr[mid] > target
            high = mid - 1;
        }
    }

    // If we reach here, the element was not present
    return -1;
}

int main() {
    int n; // Number of elements in the list

    // 1. Read the number of elements (n)
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: Invalid input for number of elements.\n");
        return 1; // Exit with an error code
    }

    // Handle the edge case of an empty or invalid-sized list
    if (n <= 0) {
        int target;
        // Even with an empty list, we must consume the target from stdin
        // to conform to the input format.
        if (scanf("%d", &target) == 1) {
             printf("Target %d not found in an empty list.\n", target);
        }
        return 0; // Successful execution, but nothing to search
    }

    // 2. Allocate memory for the array dynamically
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return 1; // Exit with an error code
    }

    // 3. Read the n sorted integers into the array
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Error: Failed to read element at index %d.\n", i);
            free(arr); // Clean up allocated memory before exiting
            return 1;
        }
    }

    // 4. Read the target integer to search for
    int target;
    if (scanf("%d", &target) != 1) {
        fprintf(stderr, "Error: Failed to read the target value.\n");
        free(arr); // Clean up
        return 1;
    }

    // 5. Perform the binary search by calling our function
    int index = binary_search(arr, n, target);

    // 6. Print the result based on the return value
    if (index != -1) {
        printf("Target %d found at index %d.\n", target, index);
    } else {
        printf("Target %d not found.\n", target);
    }

    // 7. Clean up: free the dynamically allocated memory
    free(arr);

    return 0; // Indicate successful execution
}
