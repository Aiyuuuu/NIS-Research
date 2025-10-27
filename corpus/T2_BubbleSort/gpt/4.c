/* bubblesort.c
 *
 * Usage (stdin):
 *   First integer: n (number of elements)
 *   Then: n integers
 *
 * Example:
 *   echo "5 3 1 4 5 2" | ./bubblesort
 *   Output: 1 2 3 4 5
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o bubblesort bubblesort.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void bubbleSort(int arr[], int n) {
    if (n <= 1) return;
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        // After i passes, the last i elements are in place.
        for (int j = 0; j < n - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                swapped = true;
            }
        }
        if (!swapped) break; // array already sorted
    }
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: expected integer count 'n' on stdin.\n");
        return 1;
    }
    if (n < 0) {
        fprintf(stderr, "Error: negative array size not allowed.\n");
        return 1;
    }

    int *arr = NULL;
    if (n > 0) {
        arr = malloc((size_t)n * sizeof *arr);
        if (!arr) {
            fprintf(stderr, "Error: memory allocation failed.\n");
            return 1;
        }
        for (int i = 0; i < n; ++i) {
            if (scanf("%d", &arr[i]) != 1) {
                fprintf(stderr, "Error: expected %d integers after n.\n", n);
                free(arr);
                return 1;
            }
        }
    }

    bubbleSort(arr, n);

    for (int i = 0; i < n; ++i) {
        if (i) putchar(' ');
        printf("%d", arr[i]);
    }
    putchar('\n');

    free(arr);
    return 0;
}

