#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
typedef struct s{
    char firstName[20];
    char lastName[20];
    int studentId;
    char semester;
} Student;

int writeStudent(int argc,char **argv){
    char *fileName = argv[1];
    int fd = open(fileName, O_WRONLY|O_CREAT, 0666);
    for(int i = 0; i < 10; i++){
        Student myStudent;
        myStudent.studentId = (i+1)*100;
        myStudent.semester = (i+1);
        sprintf(myStudent.firstName, "Juanito_%d", i);
        sprintf(myStudent.lastName, "Perez_%d", i);
        write(fd, &myStudent, sizeof(myStudent));
    }
    close(fd);
    return 0;
}
int readStudent(int argc,char **argv){
    char *fileName = argv[1];
    int fd = open(fileName,O_RDONLY);
    Student myS;
    while(read(fd,&myS,sizeof(myS))){
        printf("%s %s : %d: %d\n",myS.firstName,myS.lastName,myS.studentId,myS.semester);
    }
    close(fd);
    return 0;
}

int main(int argc, char **argv){
    char *fileName = argv[1];
    char *lastName = argv[2];
    char *newLastName = argv[3];
    int recordPos = -1;
    int i = -1;
    readStudent(argc, argv);
    int fd = open(fileName,O_RDONLY);
    Student myS;
    while(read(fd,&myS,sizeof(myS))){
        i++;
        if(!strcmp(myS.lastName, lastName)){
            recordPos = i;
            break;
        }
    }
    close(fd);
    if(recordPos!=-1){
        printf("El record existe en la posicion %d\n",recordPos);
        char lastNameBuf[sizeof(myS.lastName)];
        strncpy(lastNameBuf, newLastName, sizeof(myS.lastName));
        fd = open(fileName, O_WRONLY);
        lseek(fd, sizeof(myS)*recordPos + sizeof(myS.firstName), SEEK_SET);
        write(fd, &lastNameBuf, sizeof(myS.lastName));
        close(fd);
    } else{
        printf("el record no existe\n");
    }
    return 0;
}