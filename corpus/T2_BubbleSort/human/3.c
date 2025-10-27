#include<stdio.h>
int main()
{
	int ar[5];int j;int i;int k;
	for(i=0;i<5;i++)
	{
		printf("Input number %d: ",i+1);
		scanf("%d",&ar[i]);
	}
	printf("\n\n");
	
	printf("Original List :\n\n");
	for(i=0;i<5;i++)
	{
		printf("%d  ",ar[i]);
	}
	printf("\n\n\n");
		
	int temp;
	for(j=0;j<5;j++)
	{
		for(k=0;k<4;k++)
		{
			if(ar[k]>ar[k+1])
			{
				temp=ar[k];
				ar[k]=ar[k+1];
				ar[k+1]=temp;
			}
		}
	}
	
	printf("Sorted List :\n\n");
	for(i=0;i<5;i++)
	{
		printf("%d  ",ar[i]);
	}
	printf("\n\n");
	
	return 0;
}
