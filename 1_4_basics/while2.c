#include <stdio.h>
#include <unistd.h>

int main(void)
{ 
	int i = 0;    
	while ( i < 20 ) { /* While i is less than 20 */
		printf( "%d\n", i );
		i++;             /* Update i with one*/
		sleep(1);
	}
	return 0;
}

