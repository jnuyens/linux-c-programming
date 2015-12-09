#include <stdio.h>

int main (void)
{
	printf("char\t%zu\n", sizeof(char));   
	printf("short\t\t%zu\n", sizeof(short));    
	printf("int\t\t%zu\n", sizeof(int));
	printf("long\t\t%zu\n", sizeof(long));
	printf("float\t\t%zu\n", sizeof(float));
	printf("double\t\t%zu\n", sizeof(double));  
	printf("long double\t%zu\n", sizeof(long double));    
	printf("long long\t%zu\n", sizeof(long long));    
	printf("long double\t%zu\n", sizeof(long double));    
 	return 0;
}
