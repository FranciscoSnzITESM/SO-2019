#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int forever = 1;

void signalHandler(int sgn){
    printf("Recibi la señal %d \n", sgn);
    forever = 0;
}

int main(){
    int pid;
    signal(10, signalHandler);
    pid = fork();//referencia al hijo
    if(pid==0){//soy el hijo
        printf("Soy el hijo\n");
        // Codigo que quiero que haga el hijo
        while(forever){}
        printf("Saliendo del ciclo infinito\n");
    }else{
        printf("Soy el proceso padre y mi hijo es: %d\n",pid);
        sleep(5);
        kill(pid,10);
        // Codigo del padre
        for(;;){}
    }
   return 0;
}