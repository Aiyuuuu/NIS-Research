#include <stdio.h>
#include <stdlib.h>

/* Iterative binary search.
 * Returns the 0-based index of target in arr[0..n-1], or -1 if not found.
 * Assumes arr is sorted in non-decreasing (ascending) order.
 */
int binary_search(const int arr[], int n, int target) {
    int low = 0;
    int high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2; /* avoids overflow */
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        /* Failed to read number of elements */
        return 1;
    }

    if (n < 0) n = 0;

    int *arr = NULL;
    if (n > 0) {
        arr = malloc(n * sizeof *arr);
        if (arr == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            /* Input error; clean up and exit */
            free(arr);
            return 1;
        }
    }

    int target;
    if (scanf("%d", &target) != 1) {
        free(arr);
        return 1;
    }

    int index = binary_search(arr, n, target);
    printf("%d\n", index); /* prints 0-based index or -1 if not found */

    free(arr);
    return 0;
}

