/**
 * @file binary_search.c
 * @brief A C program to find an integer in a sorted list using Binary Search.
 *
 * This program first reads the number of elements, then the sorted list of
 * integers, and finally the target value to search for. It uses the classic
 * binary search algorithm to efficiently find the index of the target.
 *
 * The binary search algorithm works by:
 * 1. Comparing the target value to the middle element of the array.
 * 2. If they are not equal, the half in which the target cannot lie is eliminated.
 * 3. The search continues on the remaining half.
 * 4. This process is repeated until the value is found or the remaining half is empty.
 *
 * Input Format (from stdin):
 * Line 1: An integer N (the number of elements).
 * Line 2: N space-separated integers, sorted in ascending order.
 * Line 3: An integer T (the target value to find).
 *
 * Output Format (to stdout):
 * - If found: "Element [T] found at index [index]."
 * - If not found: "Element [T] not found in the list."
 */

#include <stdio.h>
#include <stdlib.h> // Required for malloc and free

/**
 * @brief Performs a binary search on a sorted integer array.
 *
 * @param arr The sorted array of integers to search in.
 * @param size The number of elements in the array.
 * @param target The integer value to search for.
 * @return The index of the target if found; otherwise, -1.
 */
int binarySearch(int arr[], int size, int target) {
    int low = 0;
    int high = size - 1;

    // Continue searching as long as the interval [low...high] is valid.
    while (low <= high) {
        // Calculate the middle index to avoid potential overflow with (low + high) / 2
        int mid = low + (high - low) / 2;

        // Check if the target is present at the middle
        if (arr[mid] == target) {
            return mid; // Target found
        }

        // If the target is smaller than the middle element, it can only be in the left subarray
        if (arr[mid] > target) {
            high = mid - 1; // Discard the right half
        }
        // If the target is larger than the middle element, it can only be in the right subarray
        else {
            low = mid + 1; // Discard the left half
        }
    }

    // If the loop finishes, the element was not present in the array
    return -1;
}

int main() {
    int num_elements;
    int *array = NULL;
    int target;
    int i;

    // 1. Get the number of elements from the user
    printf("Enter the number of elements: ");
    if (scanf("%d", &num_elements) != 1 || num_elements <= 0) {
        fprintf(stderr, "Error: Invalid number of elements.\n");
        return 1;
    }

    // Allocate memory for the array dynamically
    array = (int *)malloc(num_elements * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return 1;
    }

    // 2. Get the sorted elements from the user
    printf("Enter %d sorted integers (space-separated): ", num_elements);
    for (i = 0; i < num_elements; i++) {
        if (scanf("%d", &array[i]) != 1) {
            fprintf(stderr, "Error: Invalid input while reading array elements.\n");
            free(array); // Clean up allocated memory
            return 1;
        }
    }

    // 3. Get the target value to search for
    printf("Enter the target value to search for: ");
    if (scanf("%d", &target) != 1) {
        fprintf(stderr, "Error: Invalid input for target value.\n");
        free(array); // Clean up allocated memory
        return 1;
    }

    // Perform the binary search
    int result_index = binarySearch(array, num_elements, target);

    // 4. Output the result
    if (result_index != -1) {
        printf("Element %d found at index %d.\n", target, result_index);
    } else {
        printf("Element %d not found in the list.\n", target);
    }

    // Free the dynamically allocated memory
    free(array);

    return 0;
}
