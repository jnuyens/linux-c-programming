#include <stdio.h>

int main (void)
{


char path[1024];
char output[2048];

fgets(path, 1024, stdin);
fputs(path,  stdout);


FILE *contents;
path[strlen(path) - 1] = '\0';
contents=fopen(path,"r");

fread(output,1,1024,contents);
int i=0;
for(i=0; i<1024;i++){
	printf("%c",output[i]);
}

}
