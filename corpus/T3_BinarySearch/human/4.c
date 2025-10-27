#include <stdio.h>
#include <stdlib.h>

// returns location of number or -1
int length;
int binSearch(int array[], int l, int r, int x)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;

        // check if in middle
        if (array[mid] == x)
            return mid;

        // If element is less than mid,
        // it is in left subarray
        if (array[mid] > x)
            return binSearch(array, l, mid - 1, x);

        // Else the element is in right subarray
        return binSearch(array, mid + 1, r, x);
    }

    // if element not present
    return -1;
}
int main()
{

    int x=0;
    int y=0;
    puts("***Program for binary search***");
    printf("How long is the array:\n");
    scanf("%i", &length);
    puts("***Enter sorted array from smallest to biggest***");
    int array[length];
    for (x=0; x<length;x++)
    {
        printf("Enter number %d: ", (x+1));
        scanf("%d", &array[x]);

    }
    printf("Enter number to search: ");
        scanf("%d", &y);

    int n = sizeof(array) / sizeof(array[0]);
    int result = binSearch(array, 0, n - 1, y);
    (result == -1)
        ? printf("Element is not present in array")
        : printf("Element is present at index %d", result);
    return 0;
}

