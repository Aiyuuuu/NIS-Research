#include<stdio.h>
int main()
{
int a[100],n,i,temp;
printf("Enter n value :");
scanf("%d",&n);
printf("Enter elements :");
for(i=0;i<n;i++)
scanf("%d",&a[i]);

for(i=0;i<n;i++)
{
if(a[i]>a[i+1])
{
a[i]=temp;
a[i]=a[i+1];
a[i+1]=temp;
}
}
for(i=0;i<n;i++)
printf("%d\t",a[i]);
}

