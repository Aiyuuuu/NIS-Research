/* bubblesort_static.c
 *
 * Read up to MAX_N ints from stdin, sort them using Bubble Sort,
 * and print the sorted list to stdout.
 *
 * Compile:
 *   gcc -std=c11 -O2 -Wall -Wextra -o bubblesort_static bubblesort_static.c
 *
 * Example:
 *   echo "3 1 4 1 5 9 2" | ./bubblesort_static
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000  /* adjust this if you need to support more numbers */

int main(void) {
    int arr[MAX_N];
    size_t n = 0;
    int value;

    /* Read integers from stdin until EOF or capacity reached */
    while (scanf("%d", &value) == 1) {
        if (n >= MAX_N) {
            fprintf(stderr, "Error: too many input values (max %d).\n", MAX_N);
            return 2;
        }
        arr[n++] = value;
    }

    /* If no input, exit quietly */
    if (n == 0) return 0;

    /* Classic Bubble Sort with early-exit optimization */
    for (size_t i = 0; i + 1 < n; ++i) {
        int swapped = 0;
        for (size_t j = 0; j + 1 < n - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                swapped = 1;
            }
        }
        if (!swapped) break; /* already sorted */
    }

    /* Print sorted numbers space-separated */
    for (size_t i = 0; i < n; ++i) {
        if (i) putchar(' ');
        printf("%d", arr[i]);
    }
    putchar('\n');

    return 0;
}

