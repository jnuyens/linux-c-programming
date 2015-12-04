#include <stdio.h>
#include <time.h>

int main(void)
{ 
	struct timespec tim;
   	tim.tv_sec = 0;
   	tim.tv_nsec = 500000000L;	
	int i = 0;    
	while ( i < 20 ) { 
		printf( "%d\n", i );
		i++;            
		nanosleep(&tim , NULL);
		/*nanosecond sleep
		there are one million microseconds in 
		one second and a thousand nanoseconds
		in one microsecond.
		nanosleep() is defined in <time.h> */
	}
	return 0;
}

