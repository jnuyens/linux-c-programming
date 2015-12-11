CC=gcc
CFLAGS=-Wall
LDFLAGS=

all: server client

server: server.o
	$(CC) $(LDFAGS) server.o -o server

client: client.o
	$(CC) $(LDLAGS) client.o -o client

server.o: server.c
	$(CC) $(CFLAGS) -c server.c -o server.o

client.o: client.c
	$(CC) $(CFLAGS) -c client.c -o client.o

clean:
	rm -f *.o client server 
