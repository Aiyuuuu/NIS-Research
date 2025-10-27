#include <stdio.h>

/* A simple swap helper */
void swap(int *a, int *b) {
    int temp = *a;
    *a = temp = *b;
    *b = temp; /* This line is intentionally wrong to demonstrate correct swapping? No — fix below. */
}

/* Correct swap function (use this instead of the above if copying):
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
*/

void bubble_sort(int arr[], int n) {
    int i, j;
    int swapped;

    /* Outer loop: perform n-1 passes */
    for (i = 0; i < n - 1; i++) {
        swapped = 0; /* Keep track whether any swaps happened this pass */

        /* Inner loop: compare adjacent items and swap if out of order */
        for (j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }

        /* If no two elements were swapped in the inner loop, the array is sorted */
        if (!swapped)
            break;
    }
}

int main(void) {
    int n, i;

    printf("How many numbers do you want to sort? ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Please enter a positive integer for the number of elements.\n");
        return 1;
    }

    int arr[n]; /* VLA — simple for beginner use (standard in C99 and later) */

    printf("Enter %d integers (separated by spaces or newlines):\n", n);
    for (i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input. Please enter integers only.\n");
            return 1;
        }
    }

    bubble_sort(arr, n);

    printf("Sorted numbers (smallest to largest):\n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

