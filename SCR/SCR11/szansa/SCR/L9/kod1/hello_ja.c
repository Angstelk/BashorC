#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define THREADS	100

void *PrintHello(void *threadid)
{
   long tid;
   tid = (long)threadid;
   printf("Witaj, wątek : #%ld!\n", tid);
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
   pthread_t threads[THREADS];
   int result;
   long t;
   for(t=0;t<THREADS;t++){
     printf("Pętla główna tworząca wątek :  %ld\n", t);
     result = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
     if (result){
       printf("Numer błędu przy tworzeniu wątku :  %d\n", result);
       exit(-1);
       }
     }

   pthread_exit(NULL);
}
