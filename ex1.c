#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t mutex;

void* routine(void* arg){
    int b=*(int*) arg*3;
    printf("Hello from thread: %d\n",b);
    *(int*)arg=b;
    return arg;
}

int main(int argc,char* argv[]){
    pthread_t t[3];
    for(int i=0;i<3;i++){
        int *a=malloc(sizeof(int));
        *a=3;
        if(pthread_create(&t[i],NULL,&routine,a)!=0){
            perror("Errore nel creare il thread\n");
        }
    }

    int globalSum=0;
      for(int i=0;i<3;i++){
        int* result;
        if(pthread_join(t[i],&result)!=0){
            perror("Errore nel join del thread\n");
        }
        globalSum +=*result;
        free(result);


    }

    printf("%d\n",globalSum);
  

    return 0;
}
