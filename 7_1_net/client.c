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
