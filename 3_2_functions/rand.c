#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RANDOMNUMBER 20
int main ()
{	
	int i;
	srand(time(NULL));
	for (i=0 ; i<RANDOMNUMBER ; i++) {
		printf ("random_number[%d]= %d\n",i, rand ());
	}
	return 0;
}
