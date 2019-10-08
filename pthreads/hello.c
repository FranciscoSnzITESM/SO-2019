#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 100

int saldo = 0;
// Protegen regiones criticas de codigo
pthread_mutex_t lockSaldo;

void *PrintHello(void *threadid)
{
    long tid;
    int localsaldo;
    pthread_mutex_lock(&lockSaldo);
    localsaldo = saldo;
    saldo = localsaldo + 1;
    pthread_mutex_unlock(&lockSaldo);
    tid = (long)threadid;
    printf("Hello World! It's me, thread #%ld!\n", tid);
    printf("Forzar perder el cpu\n");
    pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    for(t=0; t<NUM_THREADS; t++){
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    // Equals pthread_exit(NULL) at end of main
    for(t=0;t<NUM_THREADS;t++){
        pthread_join(threads[t], NULL);
    }
    printf("Todos los Hilos han terminado, saldo: %d\n",saldo);
    /* Last thing that main() should do */
    // Wait for all threads to finish
    pthread_exit(NULL);
}