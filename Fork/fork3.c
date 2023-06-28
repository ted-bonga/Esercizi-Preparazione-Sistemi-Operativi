#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc,char* argv[]){
    int fd[2];
    //fd[0] - read
    //fd[1] - write
    if(pipe(fd)==-1){
        printf("An error occured with opening the pipe\n");
        return 1;
    }
    int id=fork();
    if(id==-1){
        printf("An error occured with fork\n");
        return 4;
    }
    if(id==0){
        close(fd[0]);
        int x;
        printf("Input a number: ");
        scanf("%d", &x);
        if(write(fd[1],&x,sizeof(int))== -1){
            printf("An error occured with writing to the pipe\n ");
            return 2;
        }
        write(fd[1], &x, sizeof(int));
        close(fd[1]);
    } else{
        close(fd[1]);
        int y;
        if(read(fd[0],&y,sizeof(int))==-1){
            printf("An error occured with reading to the pipe\n");
            return 3;
        }
        y=y*3;
        close(fd[0]);
        printf("Got from child process %d\n", y);
    }
    
    return 0;
}
