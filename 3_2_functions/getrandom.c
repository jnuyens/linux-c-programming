#include <stdio.h>
#include <linux/random.h>

int is_a_prime_or_not( int checkprime1, int checkprime2)
{
	int prime_roulette=0;
	getrandom(&prime_roulette,sizeof(prime_roulette),GRND_NONBLOCK);

	if (prime_roulette > 100){
	 	printf("%d, it’s a prime \n", prime_roulette); 
	} else {
		printf("%d, it’s not a prime\n", prime_roulette);
	}
	return 1;
}

int main(void)
{ 
	is_a_prime_or_not(50,13);
	return 0;
}
