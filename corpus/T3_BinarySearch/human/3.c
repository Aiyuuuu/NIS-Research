#include <stdio.h>

int count=0;

int b_search(int a[10],int low,int high,int key)
{
    count++;
    int mid;
    if(low>high)
    {
        return -1;
    }
    else
    {
        mid=(low+high)/2;
        if(a[mid] == key)
            return mid;
        else if(a[mid]<key)
            b_search(a,mid+1,high,key);
        else
            b_search(a,low,mid-1,key);
    }
}

int main(void) 
{
	int a[10],n,key,i,f;
	printf("Enter size of arrray: ");
	scanf("%d",&n);
	
	for(i=0;i<n;i++)
	    scanf("%d",&a[i]);
	    
	printf("Enter Element to be searched:");
	scanf("%d",&key);
	
	f=b_search(a,0,n-1,key);
	
	if(f==-1)
	{
	    printf("NOT FOUND\n");
	    printf("OPERATION COUNT=%d\n",count);
	}
	
	else
	{
	    printf("Found at %d\n",f+1);
	    printf("OPERATION COUNT=%d",count);
	}
	
	return 0;
}

