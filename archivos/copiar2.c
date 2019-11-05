#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char **argv){
    char *file1 = argv[1];
    char *file2 = argv[2];
    char *pwd = getcwd(NULL,0);
    // One for '/' and one for end of string
    char path1[strlen(file1)+strlen(pwd)+2];
    char path2[strlen(file2)+strlen(pwd)+2];
    sprintf(path1,"%s/%s",pwd,file1);
    sprintf(path2,"%s/%s",pwd,file2);

    printf("pwd %s\n",path1);
    printf("pwd %s\n",path2);

    int fd1 = open(path1, O_RDONLY);
    // create if it doesnt exist and open for write
    int fd2 = open(path2, O_WRONLY|O_CREAT, 0666);

    char buffer[100];
    int n;
    while((n = read(fd1,buffer,100))!=0){
        printf("n: %d\n",n);
        write(fd2,buffer,n);
    }

    close(fd1);
    close(fd2);
}