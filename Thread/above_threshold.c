#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    char *filename;
    int n;
    int threshold;
    int count;
} ThreadData;

void* count_above_threshold(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    FILE* file = fopen(data->filename, "rb");
    if (file == NULL) {
        perror("Errore durante l'apertura del file");
        pthread_exit(NULL);
    }

    int value;
    while (fread(&value, sizeof(int), 1, file) == 1) {
        if (value > data->threshold) {
            data->count++;
        }
    }

    fclose(file);
    pthread_exit(NULL);
}

int above_threshold(char *filename, int n, int threshold) {
    pthread_t* threads = (pthread_t*)malloc(n * sizeof(pthread_t));
    ThreadData* thread_data = (ThreadData*)malloc(n * sizeof(ThreadData));
    int i;

    for (i = 0; i < n; i++) {
        thread_data[i].filename = filename;
        thread_data[i].n = n;
        thread_data[i].threshold = threshold;
        thread_data[i].count = 0;

        if (pthread_create(&threads[i], NULL, count_above_threshold, (void*)&thread_data[i]) != 0) {
            perror("Errore durante la creazione del thread");
            exit(EXIT_FAILURE);
        }
    }

    int total_count = 0;

    for (i = 0; i < n; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Errore durante l'attesa del thread");
            exit(EXIT_FAILURE);
        }
        total_count += thread_data[i].count;
    }

    free(threads);
    free(thread_data);

    printf("Numero totale di int con valore maggiore di threshold: %d\n", total_count);
    return total_count;
}
