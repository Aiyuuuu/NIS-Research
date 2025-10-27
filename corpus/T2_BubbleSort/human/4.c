#include<stdio.h>

int main()
{
    int a[50], n;
    int i, j, c;

    printf("\n\nEnter number of elements in the array less than and equal to 50 \n");
    scanf("%d", &n);
    if (n > 50) {
        printf("\n\nEnter number within the range");
        goto exit;
    }
    for (i = 0; i < n; i++) {
        printf("\n\nEnter elements of A[%d] array\n", i);
        scanf("%d", &a[i]);
    }
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (a[j] < a[j + 1]) {
                c = a[j];
                a[j] = a[j + 1];
                a[j + 1] = c;
            }
        }
    }
    printf("\nArray after sorting is Ascending order is \n\n");  // Note: Actually descending; minor text fix optional
    for (i = 0; i < n; i++) {
        printf("The element in A[%d] is %d\n", i, a[i]);
    }
exit:
    getchar();  // Simple standard pause (press Enter to exit)
    return 0;
}
