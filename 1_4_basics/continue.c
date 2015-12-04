#include <stdio.h>
#include <time.h>

int main(void)
{ 
	struct timespec tim;
   	tim.tv_sec = 0;
   	tim.tv_nsec = 500000000L;	
	int i = 0;    
	while ( i < 20 ) { 
		i++;
		if (i == 13) {
                        continue ;
                }
		printf( "%d\n", i );
		nanosleep(&tim , NULL);
	}
	return 0;
}

