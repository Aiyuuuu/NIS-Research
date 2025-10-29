#include <stdio.h>
#include <stdlib.h>

/*
 * Iterative binary search.
 * Parameters:
 *   arr    - pointer to first element of sorted (ascending) integer array
 *   n      - number of elements in arr
 *   target - value to search for
 * Returns:
 *   index (0-based) of target in arr if found, otherwise -1.
 */
int binarySearch(const int arr[], int n, int target) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        /* avoid overflow when computing mid */
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; /* not found */
}

int main(void) {
    int n;

    /* Read size */
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Failed to read array size\n");
        return 2;
    }
    if (n < 0) {
        fprintf(stderr, "Array size must be non-negative\n");
        return 3;
    }

    /* Allocate array */
    int *arr = NULL;
    if (n > 0) {
        arr = (int *)malloc((size_t)n * sizeof(int));
        if (!arr) {
            fprintf(stderr, "Memory allocation failed\n");
            return 4;
        }
    }

    /* Read n integers (assumes they are sorted ascending as required) */
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Failed to read array element %d\n", i);
            free(arr);
            return 5;
        }
    }

    /* Read target */
    int target;
    if (scanf("%d", &target) != 1) {
        fprintf(stderr, "Failed to read target value\n");
        free(arr);
        return 6;
    }

    /* Search and print result index (0-based). If not found print -1. */
    int idx = binarySearch(arr, n, target);
    printf("%d\n", idx);

    free(arr);
    return 0;
}

