#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t mutex;

void* routine(){
    int value=100;
    int *res=malloc(sizeof(int));
    *res=value/2;
    printf("Nel thread res: %d\n",*res);
    return (void*) res;
}

int main(int argc,char* argv[]){
    pthread_t t[3];
    int globalResult=0;
    for(int i=0;i<3;i++){
        if(pthread_create(&t[i],NULL,&routine,NULL)!=0){
            perror("Errore nel creare il thread\n");
        }
    }

      for(int i=0;i<3;i++){
        int *result;
        if(pthread_join(t[i],&result)!=0){
            perror("Errore nel join del thread\n");
        }
        printf("global result:%d\n",globalResult);
        globalResult=globalResult+*result;
        free(result);

    }
    printf("%d\n",globalResult);

    return 0;
}
