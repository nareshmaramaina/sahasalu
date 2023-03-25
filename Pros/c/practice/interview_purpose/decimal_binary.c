/* C Program to Convert Decimal to Binary */
 
#include <stdio.h>

void Decimal_to_Binary(int number)
{
    int j;
    for(int i = 31; i >= 0; i--)
    {
        j = number >> i;
        
        if(j & 1)
            printf("1");
        else
            printf("0");
    }
}
int main() 
{
    int number;
    
    printf("\n Please Enter the Number You want to Convert  :  ");
    scanf("%d", &number);
    
    Decimal_to_Binary(number); 
            
    return 0;
}
