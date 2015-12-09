#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define COUNT 640 * 1024 * 1024

int main()
{
   int i = 0;
   printf("malloc and write!\n");
   
   int64_t *buf = (int64_t *)malloc(COUNT * sizeof(int64_t));
   
   for(i = 0; i < COUNT; i++ ) {
       buf[i] = 0x0000000000000001;
   }

   return 0;
}
