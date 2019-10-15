#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int main(int argc,char** argv){
    int limit = 100;
    char limitc[(int) floor(log10(limit)+1)];
    char size[10];
    int s = sizeof(limitc);
    sprintf(size, "%d",s);
    // Write byte size
    write(1, size, sizeof(size));
    sprintf(limitc, "%d", limit);
    // Write limit
    write(1, limitc, sizeof(limitc));
    int i;
    char c[sizeof(limitc)];
    for(i=2;i<=limit;i++){
        sprintf(c, "%d", i);
        // Write numbers
        write(1, c, sizeof(c));
    }
    return 0;
}