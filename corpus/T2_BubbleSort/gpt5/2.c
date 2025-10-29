#include <stdio.h>
#include <stdlib.h>

/* Simple Bubble Sort demo:
 *  - Prompts the user for the number of integers
 *  - Reads integers one-by-one from standard input
 *  - Sorts them in ascending order using Bubble Sort
 *  - Prints the sorted list
 */

int main(void) {
    int n, i, j, swapped;
    int *arr;

    printf("How many numbers do you want to sort? ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input for count.\n");
        return 1;
    }

    if (n <= 0) {
        printf("Nothing to sort (count must be positive).\n");
        return 0;
    }

    arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    for (i = 0; i < n; ++i) {
        printf("Enter number %d: ", i + 1);
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid integer input. Exiting.\n");
            free(arr);
            return 1;
        }
    }

    /* Bubble Sort (ascending) with early exit optimization */
    for (i = 0; i < n - 1; ++i) {
        swapped = 0;
        for (j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                swapped = 1;
            }
        }
        if (!swapped) {
            /* No swaps in this pass -> array is sorted */
            break;
        }
    }

    printf("\nSorted list (ascending):\n");
    for (i = 0; i < n; ++i) {
        printf("%d", arr[i]);
        if (i < n - 1) putchar(' ');
    }
    putchar('\n');

    free(arr);
    return 0;
}

