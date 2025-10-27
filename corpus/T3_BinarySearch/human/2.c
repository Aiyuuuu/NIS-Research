/*
 * C library for general binary search. 
 * You must supply a compare() function using void pointers.
 *
 * Author: Christopher W. Schankula
 * Last updated: December 20th, 2017
 * Code is licensed under the CC BY 4.0 license.
 *
 * THE CODE PROVIDED HEREIN IS PROVIDED "AS-IS"
 * THE AUTHOR ASSUMES NO RESPONSBILITY OR WARRANTY
 * FOR USE OF THE CODE PROVIDED HEREIN
 * EXTENSIVE TESTING OF THIS CODE IS REQUIRED
 * TO ENSURE ITS CORRECTNESS AS PART OF THE INTENDED
 * APPLICATION THEREOF
 */

#include <stdio.h>
#include <stdlib.h>

int binary_search(void *A, void *elem, size_t s, int low, int high, int compare(const void *, const void *)) {
    if (high < low) {
        return -1; // element not found
    }

    int middle = low + (high - low) / 2;
    int comp = compare(elem, (void *) ((char *)A + s * middle));

    if (comp == 0)
        return middle;
    else if (comp > 0)
        return binary_search(A, elem, s, middle + 1, high, compare);
    else
        return binary_search(A, elem, s, low, middle - 1, compare);
}


int compareInt(const void *a, const void *b){
	int n1 = *(int *)a;
	int n2 = *(int *)b;
	return n1 - n2;
}

int main(){
	int n=0;
	printf("\nEnter the number of elements: ");
	  scanf("%d", &n);


printf("\nEnter the elements (one by one in ascending order):\n");
    // elements of the list
    int A[n];
    
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }
printf("\nEnter the element you want to find: ");
    // element we want to find in the list
    int k = 0;
    scanf("%d", &k);

	        int ind = binary_search(A, &k, sizeof(int), 0, n - 1, compareInt);
	
		if (ind == -1)
			printf("\nElement %d does not exist in array.\n", k);
		else
			printf("Found element %d at position %d.\n", k, ind);
	

	return 0;
}
