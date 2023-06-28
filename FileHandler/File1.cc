#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_STRING_LENGTH 100
char var[1000];
char *arrayString[3];
int main(int argc,char* argv[]){
    char string[MAX_STRING_LENGTH];
    FILE* fptr;
    if (argc != 2) {
        printf("Usage: ./program <F1>\n");
        return 1;
    }
     const char* file_F1_name = argv[1];
     
    fptr=fopen(file_F1_name,"w");
    //  while (fgets(string, sizeof(string), stdin) != NULL) {
    //    int len = strlen(string);
    //     fseek(fptr, 0, SEEK_END);
    //     fwrite(string, sizeof(char), len, fptr);

    // }
    while (fgets(string, sizeof(string), stdin) != NULL) {
        int len=strlen(string);
        fseek(fptr,0, SEEK_END);
        fwrite(string, sizeof(char), len, fptr);
       
    }
    fclose(fptr);
    return 0;
}