#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

/*
** Program to find an element using Binary Search
** Made by - Abhishek Chand (modified)
*/

void BinarySearch(int A[],int n,int search)
{
	int i,j,mid;
	i=0;
	j=n-1;
	mid=(i+j)/2;
	while(i<=j)
	{
		if(A[mid]<search)
			i=mid+1;
		else if(A[mid]==search)
		{
			printf("%d is present at location %d\n",search,mid+1);
			break;
		}
		else
			j=mid-1;
		
		mid=(i+j)/2;
	}
	if(i>j)
    	printf("%d is not present in the array\n",search);
}

int main()
{
	int i,n,*A,search;
	char ch;

	do
	{
		printf("Enter the size of Array : ");
		scanf("%d",&n);
		A=(int *)malloc(n*sizeof(int));
		printf("Enter the elements of Array:\n");
		for(i=0;i<n;i++)
			scanf("%d",&A[i]);
	
		printf("Enter the element to search : ");
		scanf("%d",&search);
		
		BinarySearch(A,n,search);
  		
  		printf("\nTo continue enter (Y/y):");
  		fflush(stdin);
  		scanf(" %c",&ch);	
	}while(ch=='Y'||ch=='y');
	
	free(A);
	return 0;
}

