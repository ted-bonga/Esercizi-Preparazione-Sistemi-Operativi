#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_STRING_LENGTH 100

// Variabili condivise tra i thread
pthread_mutex_t mutex_F1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_F2 = PTHREAD_MUTEX_INITIALIZER;
FILE* file_F1;
FILE* file_F2;
int total_bytes_written = 0;

// Funzione eseguita dal thread T1
void* thread_T1(void* arg) {
    char string[MAX_STRING_LENGTH];
    int bytes_written = 0;

    while (fgets(string, sizeof(string), stdin) != NULL) {
        int len = strlen(string);

        pthread_mutex_lock(&mutex_F1);
        fseek(file_F1, 0, SEEK_END);
        fwrite(string, sizeof(char), len, file_F1);
        pthread_mutex_unlock(&mutex_F1);

        bytes_written += len;
    }

    pthread_mutex_lock(&mutex_F1);
    total_bytes_written += bytes_written;
    pthread_mutex_unlock(&mutex_F1);

    pthread_exit(NULL);
}

//Funzione eseguita dal thread T2
void* thread_T2(void* arg) {
    char string[MAX_STRING_LENGTH];
    int bytes_written = 0;

    while (fgets(string, sizeof(string), stdin) != NULL) {
        int len = strlen(string);

        pthread_mutex_lock(&mutex_F2);
        fseek(file_F2, 0, SEEK_SET);
        char* temp = malloc(sizeof(char) * (len + 1));
        strcpy(temp, string);
        fwrite(temp, sizeof(char), len, file_F2);
        fwrite(string, sizeof(char), len, file_F2);
        free(temp);
        pthread_mutex_unlock(&mutex_F2);

        bytes_written += len;
    }

    pthread_mutex_lock(&mutex_F2);
    total_bytes_written += bytes_written;
    pthread_mutex_unlock(&mutex_F2);

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: ./program F1 F2\n");
        return 1;
    }

    const char* file_F1_name = argv[1];
    const char* file_F2_name = argv[2];

    // Apertura dei file F1 e F2
    file_F1 = fopen(file_F1_name, "a");
    if (file_F1 == NULL) {
        printf("Errore nell'apertura del file F1.\n");
        return 1;
    }

    file_F2 = fopen(file_F2_name, "w");
    if (file_F2 == NULL) {
        printf("Errore nell'apertura del file F2.\n");
        fclose(file_F1);
        return 1;
    }

    pthread_t t[2];

    // Creazione dei thread T1 e T2
    // if (pthread_create(&t1, NULL, thread_T1, NULL) != 0) {
    //     printf("Errore nella creazione del thread T1.\n");
    //     fclose(file_F1);
    //     fclose(file_F2);
    //     return 1;
    // }

    // if (pthread_create(&t2, NULL, thread_T2, NULL) != 0) {
    //     printf("Errore nella creazione del thread T2.\n");
    //     fclose(file_F1);
    //     fclose(file_F2);
    //     pthread_cancel(t1);
    //     return 1;
    // }
     int i;
    for(i=0;i<2;i++) {
        if(i==0)
        pthread_create(t+i, NULL, thread_T1, NULL);
        else 
        pthread_create(t+i,NULL,thread_T2,NULL);
    }
     for(i=0;i<2;i++) pthread_join(t[i], NULL);

    // Attesa dei thread T1 e T2
    // pthread_join(t1, NULL);
    // pthread_join(t2, NULL);

    // Stampa il numero totale di byte scritti
    printf("Numero totale di byte scritti: %d\n", total_bytes_written);

    // Chiusura dei file
    fclose(file_F1);
    fclose(file_F2);

    return 0;
}
