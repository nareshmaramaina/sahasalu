#include<stdio.h>
#include<math.h>
 
int main()
{
      int decimal_number = 0, remainder, hexadecimal_number;
      int count = 0;
      printf("Enter a Hexadecimal Number:\t");
      scanf("%d", &hexadecimal_number); 
      while(hexadecimal_number > 0)
      {
            remainder = hexadecimal_number % 10;
            decimal_number = decimal_number + remainder * pow(16, count);
            hexadecimal_number = hexadecimal_number / 10;
            count++;
      }
      printf("\nDecimal Equivalent:\t%d\n", decimal_number);
      return 0;
}
