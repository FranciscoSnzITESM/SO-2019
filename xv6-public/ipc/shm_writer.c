#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    int key = 27; // numero usado para generar el id del bloque de memoria
    int shmid = shmget(key,100,IPC_CREAT);
    char *word;
    word = (char *)shmat(shmid, NULL, 0);
    // word = "Hello World"; // reemplaza el apuntador
    printf("1\n");
    sprintf(word,"Hello World"); // word[0] = 'H' ...
    printf("2\n");
    while(word[0] == 'H'){
        sleep(1);
    }
    printf("Sali del ciclo");
    return 0;
}