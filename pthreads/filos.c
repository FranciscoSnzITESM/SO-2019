#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define NUM_FILOS 5
#define NUM_THREADS 5
pthread_mutex_t forks[NUM_FILOS];
void actions(){
    sleep(1+rand()%5);
}

void * life(void *ptId){
    long tid;
    tid = (long)ptId;
    srand(time(NULL) + tid);
    while(1){
        // pensar
        printf("Voy a pensar un rato %ld\n",tid);
        actions();
        printf("Tengo hambre %ld\n",tid);
        if(tid % 2 == 0){
            pthread_mutex_lock(&forks[tid]);
            printf("Ya tengo el tenedor derecho %ld\n",tid);
            pthread_mutex_lock(&forks[(tid+1)%NUM_FILOS]);
            printf("Ya tengo el tenedor izquierdo %ld\n",tid);
            printf("A comer %ld\n",tid);
            actions();
            printf("Ya comi regreso tenedores %ld\n",tid);
            pthread_mutex_unlock(&forks[tid]);
            pthread_mutex_unlock(&forks[(tid+1)%NUM_FILOS]);
        }else{
            pthread_mutex_lock(&forks[tid+1]);
            printf("Ya tengo el tenedor izquierdo %ld\n",tid);
            pthread_mutex_lock(&forks[(tid)%NUM_FILOS]);
            printf("Ya tengo el tenedor izquierdo %ld\n",tid);
            printf("A comer %ld\n",tid);
            actions();
            printf("Ya comi regreso tenedores %ld\n",tid);
            pthread_mutex_unlock(&forks[tid]);
            pthread_mutex_unlock(&forks[(tid+1)%NUM_FILOS]);
        }
    }
}
int main (int argc, char *argv[]){
    pthread_t threads[NUM_FILOS];
    int rc;
    long t;
    for(t=0; t<NUM_THREADS; t++){
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, life, (void *)t);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    pthread_exit(NULL);
}