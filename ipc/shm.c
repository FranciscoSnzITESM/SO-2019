#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    int key = 27; // numero usado para generar el id del bloque de memoria
    int shmid;
    int pid;
    char *word;
    pid = fork();
    if(pid == 0) {
      shmid = shmget(key,10,IPC_CREAT|0666);
      word = (char *)shmat(shmid, 0, 0);
      sprintf(word,"Hola memoria");
      printf("I am here %s\n", word); 
      printf("esperando a que se lea\n");
      while(word[0] == 'H'){
          sleep(1);
      }
      printf("Sali del ciclo: %s\n",word);
    } else {
      sleep(2);
      shmid = shmget(key,10,IPC_CREAT|0666);
      word = (char *)shmat(shmid, 0, 0);
      printf("Lo que hay en la me moria es : %s\n",word);
      word[0] = '*';
      sleep(2);
    }
    return 0;
}
