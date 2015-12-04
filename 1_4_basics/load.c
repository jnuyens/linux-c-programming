#include <stdio.h>
#include <stdlib.h>

int main (void)
{
	char loadavg[4];
	FILE *fp;
	fp=fopen("/proc/loadavg", "r");
	int i=0;
        fread(loadavg,4,1,fp);
	//we have read the characters into a 4 character array	
	//let's examine the content
	for(i=0; i<4; i++){
       		printf("%c\n", loadavg[i]);
    	}     
	//now we convert the string to a floating point value
	//with atof - a C standard library function.
	//https://en.wikipedia.org/wiki/C_string_handling#Numeric_conversions
	float loadfloat;
	loadfloat=atof(loadavg);
	printf("%f\n", loadfloat);

	//compare this with 0.5 to illustrate our if-then-else
	if ( loadfloat < 0.1 ) {
		printf("The system is not doing a lot currently.\n");
	}
	else if (loadfloat < 0.5 ) {
		printf("The system is working a little bit.\n");
	}
	else if (loadfloat < 2 ) {
		printf("The system is under heavy load.\n");
	} 
	else {
		printf("ALERT: The system might be overloaded\n");
	}

 	return 0;
}
