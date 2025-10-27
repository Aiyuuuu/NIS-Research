#include <stdio.h>
#include <stdlib.h>

int main()
{ int choice,x,y,z;
    printf("enter 1st number");
    scanf("%d",&x);
    printf("enter 2nd number");
    scanf("%d",&y);
    printf("press 0 to add, 1 to sub,2 to multiply,3 to divide");
    scanf("%d",&choice);
    switch(choice)
    {
        case 0: z=x+y;
                printf("%d",z);
                break;

        case 1: z=x-y;
                printf("%d",z);
                break;
        case 2: z=x*y;
                printf("%d",z);
                break;
        case 3: 
            if (y == 0)
                printf("Division by zero not allowed!");
            else{
                z=x/y;
                printf("%d",z);}
            break;
    }
    return 0;
}
