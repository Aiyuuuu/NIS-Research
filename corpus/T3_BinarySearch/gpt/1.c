#include <stdio.h>
#include <stdlib.h>

/*
 * Binary search program
 *
 * Input format:
 *   First line: n (number of integers)
 *   Next n lines: one integer per line (must be sorted in non-decreasing order)
 *   Final line: target (integer to search for)
 *
 * Output:
 *   Prints a single integer: the zero-based index of target in the array if found,
 *   otherwise prints -1.
 */

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Failed to read n.\n");
        return 1;
    }
    if (n < 0) {
        fprintf(stderr, "n must be non-negative.\n");
        return 1;
    }

    int *arr = NULL;
    if (n > 0) {
        arr = malloc((size_t)n * sizeof(int));
        if (arr == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return 1;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Failed to read array element %d.\n", i);
            free(arr);
            return 1;
        }
    }

    int target;
    if (scanf("%d", &target) != 1) {
        fprintf(stderr, "Failed to read target.\n");
        free(arr);
        return 1;
    }

    int left = 0;
    int right = n - 1;
    int found_index = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            found_index = mid;
            break;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf("%d\n", found_index);

    free(arr);
    return 0;
}

