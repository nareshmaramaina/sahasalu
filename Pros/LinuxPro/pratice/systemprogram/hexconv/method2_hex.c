#include<stdio.h>
#include<math.h>
 
int main()
{
      int decimal_number = 0, remainder, hexadecimal_number;
      int count;
      printf("Enter a Hexadecimal Number:\t");
      scanf("%d", &hexadecimal_number); 
      for(count = 0; hexadecimal_number > 0; count++)
      {
            remainder = hexadecimal_number % 10;
            decimal_number = decimal_number + remainder * pow(16, count);
            hexadecimal_number = hexadecimal_number / 10;
      }
      printf("\nDecimal Equivalent:\t%d\n", decimal_number);
      return 0;
}
