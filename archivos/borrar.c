#include <unistd.h>
#include <string.h>
#include <stdio.h>
int main(int argc, char **argv){
    char *file = argv[1];
    char *pwd = getcwd(NULL,0);
    char path[strlen(file)+strlen(pwd)+2];
    sprintf(path,"%s/%s",pwd,file);
    unlink(path);

    return 0;
}