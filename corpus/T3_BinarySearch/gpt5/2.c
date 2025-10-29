#include <stdio.h>
#include <stdlib.h>

/* Iterative binary search:
 * Returns the index (0-based) of target in arr[0..n-1], or -1 if not found.
 */
int binary_search(int arr[], int n, int target) {
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;  /* avoids overflow */
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main(void) {
    int n;
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input for count.\n");
        return 1;
    }
    if (n <= 0) {
        fprintf(stderr, "Count must be a positive integer.\n");
        return 1;
    }

    int *arr = malloc(n * sizeof(int));
    if (!arr) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d sorted integer(s), one per line:\n", n);
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input for array element %d.\n", i);
            free(arr);
            return 1;
        }
    }

    int target;
    printf("Enter target value to search for: ");
    if (scanf("%d", &target) != 1) {
        fprintf(stderr, "Invalid input for target.\n");
        free(arr);
        return 1;
    }

    int idx = binary_search(arr, n, target);
    if (idx >= 0) {
        printf("Target %d found at index (0-based): %d\n", target, idx);
        printf("Target %d found at position (1-based): %d\n", target, idx + 1);
    } else {
        printf("Target %d not found in the array.\n", target);
    }

    free(arr);
    return 0;
}

