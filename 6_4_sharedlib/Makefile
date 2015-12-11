all: shared.c shared.h
	gcc -c -Wall -Werror -fPIC shared.c
	gcc -shared -o libshared.so shared.o
