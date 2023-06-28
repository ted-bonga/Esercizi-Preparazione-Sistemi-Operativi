#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

pthread_mutex_t mutex;
int count;
bool isPalindroma(char *c) {
    int len = strlen(c);
    int i, j;

    // Verifica se la stringa è vuota o di lunghezza 1
    if (len <= 1)
        return true;

    // Confronta i caratteri dall'inizio e dalla fine
    for (i = 0, j = len - 1; i < j; i++, j--) {
        if (c[i] != c[j])
            return false;
    }

    // Tutti i caratteri corrispondono, la stringa è palindroma
    return true;
}

void* routine(void* arg){
    int *result=malloc(sizeof(int));
    FILE* fptr;
    fptr=fopen(arg,"r");
    if(fptr==NULL)
    printf("Errore nell'apertura del file\n");
    char c[1000];
    count=0;
    while( (fgets(c,1000,fptr))){
        pthread_mutex_lock(&mutex);
        printf("%s\n",c);
        if(isPalindroma(c)){
        count++;
        }
        pthread_mutex_unlock(&mutex);
    }
    fclose(fptr);
    printf("count:%d\n",count);
    *result=count;
    return result;
}

int check_palindrome(char *filename, int n){
        pthread_t th[n];
        pthread_mutex_init(&mutex,NULL);

       for(int i=0;i<n;i++){
        if(pthread_create(&th[i],NULL,&routine,filename)!=0){
            perror("Error on create thread\n");
        }
    }
    int globalResult=0;
    for(int i=0;i<n;i++){
        int *r;
        if(pthread_join(th[i],&r)!=0){
            perror("Error on join thread\n");
            }
            globalResult=globalResult+*r;
            free(r);
            pthread_mutex_destroy(&mutex);
    }
    printf("GlobalResult:%d \n",globalResult);
}


int main(int argc,char* argv[]){
    int n=2;
    char* filename="input.txt";
    check_palindrome(filename,n);
  
    return 0;

}