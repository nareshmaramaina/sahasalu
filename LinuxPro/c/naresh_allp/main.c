#include<stdio.h>
#define BLUE "\33[34m"
#define RED "\33[31m"
#define BRIGHT_RED "\33[01;31m"
#define GREEN "\33[32m"
#define NORMAL "\33[0m"
#define MAGENTA "\33[35m"
#define BOLDBLUE "\033[1m\033[34m"      
#define BOLDGREEN "\033[1m\033[32m"
#define BOLDMAGENTA "\033[1m\033[35m"
int main()
{
                fprintf(stderr ," \t Error in usage%d\n",ERROR) ;
                fprintf(stderr ,RED" \t Error in usage\n") ;
                fprintf(stderr ,BLUE" \t Error in usage\n") ;
                fprintf(stderr ,GREEN" \t Error in usage\n") ;
                fprintf(stderr ,MAGENTA" \t Error in usage\n") ;
                fprintf(stderr ,BOLDBLUE" \t Error in usage\n"NORMAL) ;

}
