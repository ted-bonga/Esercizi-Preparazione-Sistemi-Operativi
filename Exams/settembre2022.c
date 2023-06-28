#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_FILENAME_LENGTH 100
#define BUFFER_SIZE 1024

typedef struct {
    char filename[MAX_FILENAME_LENGTH];
    int read_bytes;
    int c_count;
} FileInfo;

void *process_file(void *arg) {
    FileInfo *file_info = (FileInfo *)arg;
    FILE *file = fopen(file_info->filename, "r");
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        pthread_exit(NULL);
    }

    char buffer[BUFFER_SIZE];
    int bytes_read;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            if (buffer[i] == 'c') {
                file_info->c_count++;
            }
        }
        file_info->read_bytes += bytes_read;

        if (file_info->c_count >= 20) {
            break;
        }
    }

    printf("File: %s\n", file_info->filename);
    printf("Bytes letti: %d\n", file_info->read_bytes);
    printf("Caratteri 'c' letti: %d\n", file_info->c_count);

    fclose(file);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Utilizzo: %s <N> <file1> <file2> ... <fileN>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int file_count = argc - 2;
    pthread_t *threads = malloc(file_count * sizeof(pthread_t));
    FileInfo *file_info = malloc(file_count * sizeof(FileInfo));

    for (int i = 0; i < file_count; i++) {
        snprintf(file_info[i].filename, MAX_FILENAME_LENGTH, "%s", argv[i + 2]);
        file_info[i].read_bytes = 0;
        file_info[i].c_count = 0;

        pthread_create(&threads[i], NULL, process_file, (void *)&file_info[i]);
    }

    int total_c_count = 0;

    for (int i = 0; i < file_count; i++) {
        pthread_join(threads[i], NULL);
        total_c_count += file_info[i].c_count;
    }

    printf("Totale caratteri 'c' letti: %d\n", total_c_count);

    free(threads);
    free(file_info);

    return 0;
}
