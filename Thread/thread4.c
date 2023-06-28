/*
  create thread without if
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
int mails=0;
pthread_mutex_t mutex;
void* routine(){
    pthread_mutex_lock(&mutex);
    for(int i=0; i<100000;i++)
    mails++;
    pthread_mutex_unlock(&mutex);
    return NULL;
    }

int main(int argc,char* argv[]){
    pthread_t th[4];
    int i;
    pthread_mutex_init(&mutex,NULL);
    for(i=0; i<4;i++){
        if(pthread_create(th+i,NULL,&routine,NULL)!=0){
            perror("Failed to create thread\n");
            return 1;
        }
        printf("Thread %d has started\n",i);
    }
    for(i=0;i<4;i++){
        if(pthread_join(th[i],NULL)!=0){
            perror("Failed to join thread\n");
            return 2;
        }
        printf("Thread %d has finished execution\n",i);
    }
    pthread_mutex_destroy(&mutex);
    printf("%d\n",mails);
    return 0;
}