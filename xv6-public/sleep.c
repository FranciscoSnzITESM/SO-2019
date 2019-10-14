#include "types.h"
#include "user.h"

int main(int argc, char *argv[]){
    if(argc<2){
        printf(2,"Missing seconds input\n");
        exit();
    }
    int sec = atoi(argv[1]);
    if(sec<=0){
        printf(2,"Invalid value\n");
        exit();
    }else{
        sleep(atoi(argv[1])*100);
    }
    exit();
}