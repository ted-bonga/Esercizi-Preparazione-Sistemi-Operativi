#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_STRING_LENGTH 51 // Lunghezza massima di una stringa nel file

pthread_mutex_t mutex;
int count;

typedef struct {
    char* filename;
    char* charset;
} ThreadArgs;

void* process_string(void* arg) {
    ThreadArgs* threadArgs = (ThreadArgs*)arg;
    char* filename = threadArgs->filename;
    char* charset = threadArgs->charset;

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        pthread_exit(NULL);
    }

    char line[MAX_STRING_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0'; // Rimuove il terminatore di linea

        int valid = 1; // Indica se la stringa è valida

        // Verifica se la stringa contiene tutti i caratteri di charset
        const char* charPtr = charset;
        while (*charPtr != '\0') {
            if (strchr(line, *charPtr) == NULL) {
                valid = 0;
                break;
            }
            charPtr++;
        }

        if (valid) {
            pthread_mutex_lock(&mutex);
            count++;
            pthread_mutex_unlock(&mutex);
        }
    }
    fclose(file);
    pthread_exit(NULL);
}

int count_valid_string(char* filename, char* charset, int n) {
    pthread_t threads[n];
    count = 0;
    pthread_mutex_init(&mutex, NULL);

    ThreadArgs threadArgs;
    threadArgs.filename = filename;
    threadArgs.charset = charset;

    for (int i = 0; i < n; i++) {
        if (pthread_create(&threads[i], NULL, process_string, (void*)&threadArgs) != 0) {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < n; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            exit(EXIT_FAILURE);
        }
    }

    pthread_mutex_destroy(&mutex);

    printf("Numero totale di stringhe identificate: %d\n", count/n);
    return count;
}

int main() {
    char* filename = "input.txt";
    char* charset = "abc";
    int n = 4;

    count_valid_string(filename, charset, n);

    return 0;
}
