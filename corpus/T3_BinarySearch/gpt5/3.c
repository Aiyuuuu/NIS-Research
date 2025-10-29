/*
 * binary_search.c
 * Simple beginner-friendly C program that performs binary search on a sorted list.
 *
 * Usage:
 * 1. Compile: gcc -std=c99 -Wall -o binary_search binary_search.c
 * 2. Run:     ./binary_search
 *
 * The program asks for:
 *  - number of elements in the sorted list
 *  - the sorted numbers (ascending) entered one by one
 *  - the number to search for
 *
 * It prints the position (1-based) where the number was found, or indicates it wasn't found.
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * Iterative binary search.
 * Returns the 0-based index of `key` in `arr` if found, otherwise -1.
 */
int binary_search(int arr[], int size, int key) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        /* mid computed this way to avoid potential overflow */
        int mid = low + (high - low) / 2;

        if (arr[mid] == key) {
            return mid; /* found */
        } else if (arr[mid] < key) {
            low = mid + 1; /* search right half */
        } else {
            high = mid - 1; /* search left half */
        }
    }

    return -1; /* not found */
}

int main(void) {
    int n;

    printf("Enter number of elements in the sorted list: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of elements. Please enter a positive integer.\n");
        return 1;
    }

    /* allocate array for numbers */
    int *arr = malloc(n * sizeof(int));
    if (arr == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }

    printf("Enter %d sorted numbers (ascending), one by one:\n", n);
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input. Please enter integers only.\n");
            free(arr);
            return 1;
        }
    }

    int key;
    printf("Enter number to search for: ");
    if (scanf("%d", &key) != 1) {
        printf("Invalid input.\n");
        free(arr);
        return 1;
    }

    int idx = binary_search(arr, n, key);
    if (idx >= 0) {
        /* Print 1-based position to be easier for beginners */
        printf("Number found at position %d.\n", idx + 1);
    } else {
        printf("Number not found in the list.\n");
    }

    free(arr);
    return 0;
}

