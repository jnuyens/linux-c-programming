#include <stdio.h>
#include <unistd.h>

int main(void)
{ 
	int i = 0;    
	while ( i < 20 ) { 
		printf( "%d\n", i );
		i++;            
		usleep(200000); /*microsecond sleep
		there are one million microseconds in 
		one second
		defined in <unistd.h> 
		nanosleep() is defined in <time.h> */
	}
	return 0;
}

