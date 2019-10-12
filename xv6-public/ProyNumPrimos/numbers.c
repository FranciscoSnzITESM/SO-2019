#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc,char** argv){
    int limit = 100;
    char limitc[3];
    sprintf(limitc, "%d", limit);
    write(1, limitc, sizeof(limitc));
    int i;
    char c[3];
    for(i=2;i<=limit;i++){
        sprintf(c, "%d", i);
        write(1, c, sizeof(c));
    }
    return 0;
}