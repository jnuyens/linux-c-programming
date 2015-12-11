#include <pthread.h>
#include <stdio.h>
#define NUMBER_OF_THREADS     15
void *PrintHello(void *threadid)
{
   long tid;
   tid = (long)threadid;
   printf("Hello World! It's me, thread #%ld!\n", tid);
   pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
   pthread_t threads[NUMBER_OF_THREADS];
   int return_code;
   long t;
   for(t=0; t<NUMBER_OF_THREADS; t++){
      printf("In main: creating thread %ld\n", t);
      return_code = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
      if (return_code){
         printf("ERROR; return code from pthread_create() is %d\n", return_code);
         exit(-1);
      }
   }

   /* Last thing that main() should do */
   pthread_exit(NULL);
}

