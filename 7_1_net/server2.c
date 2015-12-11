#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_FD_HANDLERS	10

static int fd_handlers[MAX_FD_HANDLERS] = { 0 };

/* we need to keep ourselves a list of file descriptors for the open connections 
* and manage it with fd_handlers_add and fd_handlers_remove*/
static void fd_handlers_add(int fd)
{
	int i;
	for(i = 0; i < MAX_FD_HANDLERS; i++) {
		if(fd_handlers[i] == 0) {
			fd_handlers[i] = fd;
			break;
		}
	}
}

static void fd_handlers_remove(int fd)
{
	int i;
	for(i = 0; i < MAX_FD_HANDLERS; i++) {
		if(fd_handlers[i] == fd)
			fd_handlers[i] = 0;
	}
}

static void fd_handlers_build_fd_set(fd_set *rfds)
{
	int i;
	FD_ZERO(rfds); /*initializes the list */
	for(i = 0; i < MAX_FD_HANDLERS; i++) {
		if(fd_handlers[i] != 0) {
			FD_SET(fd_handlers[i], rfds);
		}
	}
}

static int fd_handlers_get_max_fd(fd_set *rfds)
{
	int i, maxfd = 0;
	for(i = 0; i < MAX_FD_HANDLERS; i++) {
		if(fd_handlers[i] > maxfd)
			maxfd = fd_handlers[i];
	}
	return maxfd;
}

static void string_modificator(char *string)
{
	size_t len = strlen(string);
	int i;
	for (i = 0; i < len; i++) {
		if ((i % 2) == 0) {
			string[i] = toupper(string[i]);
		} else {
			string[i] = tolower(string[i]);
		}
	}
}

static void handle_server_event(int sfd)
{
	struct sockaddr_in cliaddr;
	socklen_t clilen = sizeof(cliaddr);

	/* accept new incomming connection */
	int cfd = accept(sfd, (struct sockaddr *) &cliaddr, &clilen);
	printf("incoming connection (fd = %d)!\n", cfd);
	/* store fd for select loop */
	fd_handlers_add(cfd);
}

static void handle_client_event(int cfd)
{
	char string[200+1];
	memset(string, '\0', sizeof(string));

	read(cfd, string, sizeof(string)-1);
	printf("message received (fd = %d): %s\n", cfd, string);
	string_modificator(string);
	write(cfd, string, strlen(string) + 1);
	printf("message send (fd = %d): %s\n", cfd, string);

	close(cfd);
	/* remove fd from select loop */
	fd_handlers_remove(cfd);
}

int main(int argc, char *argv[])
{
	int sfd, n;
	struct sockaddr_in servaddr;

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd < 0) {
		printf("Socket could not be created!\n");
		exit(1);
	}
	fd_handlers_add(sfd);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(5000);

	n = bind(sfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if (n != 0) {
		perror("bind");
		exit(1);
	}

	if(listen(sfd, 10) != 0) {
		perror("listen");
	}
	printf("Start listening...\n");
	for (;;) {
		int rv;
		fd_set rfds;

		/* build fd set */
		fd_handlers_build_fd_set(&rfds);

		/* get max fd */
		int max_fd = fd_handlers_get_max_fd(&rfds);

		/* with select we look at all the read file descriptors */
		rv = select(max_fd + 1, &rfds, NULL, NULL, NULL);

		if (rv < 0) {	/* select error! */
			perror("select");
		} else if (rv > 0) {	/* something happened! */
			int i;
			printf("Data is available now.\n");

			for(i = 0; i < MAX_FD_HANDLERS; i++) {
				if(fd_handlers[i] == 0)
					continue;

/* FD_ISSET returns true if something happened on the file descriptor which 
*the select function noticed, false otherwise */
				if(FD_ISSET(fd_handlers[i], &rfds)) {
					if (fd_handlers[i] == sfd) { 
				/* handle new incoming connection with accept*/
						handle_server_event(sfd);
					} else { /* handle client request */
						handle_client_event(fd_handlers[i]);
					}
				}
			}
		}
	}
	close(sfd);

	return 0;
}
