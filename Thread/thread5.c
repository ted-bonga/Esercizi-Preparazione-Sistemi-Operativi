#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>

pthread_mutex_t mutex;

int counter=0;
int val=-1;

void* roll_dice(){
    pthread_mutex_lock(&mutex);
    int value=(rand() % 6)+1;
    int* result=malloc(sizeof(int));
    *result=value;
    if(value==val)
    counter++;
    //printf("%d\n",value);
    pthread_mutex_unlock(&mutex);
    return (void*) result;


}

int main(int argc, char* argv[]){
    int* res;
    int* count;
    srand(time(NULL));

    pthread_t th[8];
    pthread_mutex_init(&mutex,NULL);
    int i;
    // if(pthread_create(&th,NULL,&roll_dice,NULL)!=0){
    //     return 1;
    // }
    printf("Ciao sono un programma che lancia 8 dadi,scegli che numero da 1 a 8 e io ti dirò quante volte è uscito\n");
    scanf("%d",&val);
    if(val>=8 || val<=0){
    bool b=false;
    while(b==false){
        printf("Devi inserire un numero compreso tra 1 e 7 inclusi\n");
        //printf("Ciao sono un programma che lancia 8 dadi,scegli che numero da 1 a 8 e io ti dirò quante volte è uscito\n");
        scanf("%d",&val);
        if(val<8 && val>0){
        b=true;
        }
        }
    }
    for(i=0;i<8;i++){
        

        if(pthread_create(th+i,NULL,&roll_dice,NULL)!=0){
            printf("Errore on create thread\n");
            return 1;
        }
        //printf("Thread %d has started\n",i); used for debug
    }
    // if(pthread_join(th,(void**) &res)!=0){
    //     return 2;
    // }
    for(i=0;i<8;i++){
        if(pthread_join(th[i],(void**) &res)!=0){
            printf("Errore on join thread\n");
            return 2;
        }
        printf("Result: %d\n",*res);
        free(res);
    }
    pthread_mutex_destroy(&mutex);
    printf("Count: %d\n",counter);

    return 0;
}