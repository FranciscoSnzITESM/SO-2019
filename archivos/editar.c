#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
char *search;
char *replace;
void compara(int writer, char *word){
    // equal
    if(strcmp(search,word)==0){
        write(writer,replace,strlen(replace));
    }
    // not equal
    else{
        write(writer,word,strlen(word));
    }
}
int main(int argc,char **argv){
    char *file = argv[1];
    char *pwd = getcwd(NULL,0);
    search = argv[2];
    replace = argv[3];

    char readPath[strlen(file)+strlen(pwd)+2];
    sprintf(readPath,"%s/%s",pwd,file);
    char writePath[strlen(readPath)+4];
    sprintf(writePath,"%s/TEMP%s",pwd,file);

    int reader = open(readPath, O_RDONLY);
    int writer = open(writePath, O_WRONLY|O_CREAT, 0666);

    char c;
    char word[100];
    int i=0;
    while(read(reader, &c, 1)){
        if(c!=' ' && c!='\n'){
            word[i++] = c;
        }
        else{
            word[i] = '\0';
            compara(writer, word);
            write(writer,&c,1);
            i=0;
        }
    }
    // Last word
    if(i>0){
        word[i] = '\0';
        compara(writer, word);
    }

    close(reader);
    close(writer);
    
    unlink(readPath);
    link(writePath,readPath);
    unlink(writePath);
}