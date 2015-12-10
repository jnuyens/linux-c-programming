#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc,char *argv[])
{
	int fd;
	struct sockaddr_in cliaddr;

	/* create socket */
	fd=socket(AF_INET,SOCK_STREAM,0);
	if(fd < 0){
		printf("Socket could not be created!\n");
		exit(1);	
	}

	/* set address and destination port */
	bzero(&cliaddr,sizeof(cliaddr));
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_port=htons(5000);

	/* convert destination ip to correct format */
	if(inet_pton(AF_INET, "127.0.0.1", &cliaddr.sin_addr)<=0)
	{
		printf("\n inet_pton error occured\n");
		return 1;
	}

	/* connect to server */
	if(connect(fd, (struct sockaddr *)&cliaddr, sizeof(cliaddr))) {
		perror("connect");
		return 1;
	}

	char msg[200] = { 0 };
	printf("type msg: ");
	scanf("%s", msg);
	
	write(fd, msg, strlen(msg) + 1);
	printf("message send: %s\n", msg);
	read(fd, msg, sizeof(msg));
	printf("message received: %s\n", msg);
	 
	close(fd);

	return 0;
}

So far the client; now the server:
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>

static void string_modificator(char *string)
{
	size_t len = strlen(string);
	int i;
	for(i = 0; i < len; i++) {
		if ((i % 2) == 0) {
			string[i] = toupper(string[i]);
		} else {
			string[i] = tolower(string[i]);
		}
	}
}

static void handle_connection(int cfd)
{
	char string[200];
	memset(string, '\0', sizeof(string));

	read(cfd, string, sizeof(string) - 1);
	printf("message received (fd = %d): %s\n", cfd, string);
	string_modificator(string);
	write(cfd, string, strlen(string) + 1);
	printf("message send (fd = %d): %s\n", cfd, string);
}

int main(int argc,char *argv[])
{
	int sfd,cfd,n;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t clilen;

	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd < 0){
		printf("Socket could not be created!\n");
		exit(1);	
	}

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(5000);

	/* bind local port to specific number */
	n=bind(sfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(n != 0){
		printf("Could not bind port!\n");
		perror("bind");
		exit(1);
	}

	/* start listening on local port */
	listen(sfd,10);
	printf("Start listening...\n");
	clilen=sizeof(cliaddr);
	for(;;)
	{
		cfd = accept(sfd,(struct sockaddr *)&cliaddr, &clilen);
		printf("incoming connection (fd = %d)!\n", cfd);
		handle_connection(cfd);
		close(cfd);
		printf("connection closed (fd = %d)\n", cfd);
	}
	close(sfd);

	return 0;
}

