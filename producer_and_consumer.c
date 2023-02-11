#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

//buffer size
#define SIZE 512

int main(){
    int pid, p[2];
    char buffer[SIZE];
    //create the pipe
    pipe(p);

    //if the process id equals to 0 then it's the son process
    if ((pid = fork()) == 0){
        //we need close p[1] because the son only read to the buffer
        close(p[1]);
        read(p[0],buffer,SIZE);
        close(p[0]);
        printf("%s",buffer);
    }else{ //it's the father process    
        //we close p[0]
        close(p[0]);
        strcpy(buffer,"soy el proceso padre producionedo info para que la reciba el proceso hijo¡¡\n");
        write(p[1],buffer,strlen(buffer));
        close(p[0]);
    }
    waitpid(pid,NULL,0);
    return(0);
}