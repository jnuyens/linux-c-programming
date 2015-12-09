#include <stdio.h>
#include <string.h>
int main(void)
{
	char passwd[32];
	int password_ok = 0;
	printf("Please enter your password : \n");
	gets(passwd);
	if(strcmp(passwd, "super-secret-password"))
	{
		printf ("You entered a wrong password \n");
	}
	else
	{
		password_ok = 1;
	}
	if(password_ok)
	{
		printf ("Access granted\n");
	}
	return 0;
}
