#include <unistd.h>
#include <string.h>
#include <stdio.h>
int main(int argc,char **argv){
    char *old = argv[1];
    char *new = argv[2];
    char *pwd = getcwd(NULL,0);
    char oldpath[strlen(old)+strlen(pwd)+2];
    char newpath[strlen(new)+strlen(pwd)+2];
    sprintf(oldpath,"%s/%s",pwd,old);
    sprintf(newpath,"%s/%s",pwd,new);
    link(oldpath,newpath);
    unlink(oldpath);

    return 0;
}