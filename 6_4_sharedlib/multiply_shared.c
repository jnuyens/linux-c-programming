#include<stdio.h>
#include"shared.h"
int main(void)
{
    int x = 13;
    int y = 66;
    int result = 0;
    result = multiply(x,y);
    printf("\n Our result is [%u]\n",result);
    return 0;
}
