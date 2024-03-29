#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int created;
int n;
int size;
int limit;
pid_t id;
int p1[2];
int p2[2];
void passNumber(int m){
    if(created==0){
        // Print the new prime number
        fprintf(stderr, "%d, ", m);
        id = fork();
        // Parent
        if(id==0){
            created=1;
        }
        // Child
        else if(id>0){
            n=m;
            p1[0] = p2[0];
            p1[1] = p2[1];
            pipe(p2);
            //fprintf(stderr, "%d %d - %d %d\n", p1[0],p1[1],p2[0],p2[1]);
            //fprintf(stderr, "%d\n", m);
        }
    }else{
        char c[size];
        sprintf(c, "%d", m);
        write(p2[1], c, sizeof(c));
    }
}

int main(int argc,char** argv){
    created=0;
    pipe(p2);
    // Size of char digits
    char sizec[10];
    read(0 ,sizec, sizeof(sizec));
    size = atoi(sizec);
    // Limit
    char a[size];
    read(0, a, size);
    limit = atoi(a);
    // First number(2)
    read(0, a, size);
    n = atoi(a);
    fprintf(stderr, "Prime Numbers:%d, ", n);
    char curr[size];
    int i;
    do{
        read(p1[0], curr, size);
        if(atoi(curr)==limit+1){
            break;
        }
        // fprintf(stderr, "from: %d check: %s\n",n, curr);
        // If cant drop
        if(atoi(curr)%n!=0){
            passNumber(atoi(curr));
        }
    }while(atoi(curr)<limit);
    sprintf(a, "%d", limit+1);
    write(p2[1], a, size);
    if(created==0){
        fprintf(stderr, "\n");
    }
    return 0;
}