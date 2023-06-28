/*********************************************************************
 *  _____  ______          _____  __  __ ______ 
 * |  __ \|  ____|   /\   |  __ \|  \/  |  ____|
 * | |__) | |__     /  \  | |  | | \  / | |__   
 * |  _  /|  __|   / /\ \ | |  | | |\/| |  __|  
 * | | \ \| |____ / ____ \| |__| | |  | | |____ 
 * |_|  \_\______/_/    \_\_____/|_|  |_|______|
 * 
 * *******************************************************************
 * 
 * 
 * DO NOT FORGET TO FILL THE FOLLOWING WITH YOUR PERSONAL DATA
 * First Name:
 * Last Name:
 * Student Id:
 * 
 * 
 * ***********************************/


/***************************************************************************************************
SPECIFICA (ITA):

Implementare una programma in c tale che prende come argomento 2 nomi di file F1 e F2 
- Il main thread crea due thread/processi T1 e T2
- il T1 e T2 leggono ripetutamente da standard input stringhe (senza spazi) senza alcun ordine preciso
- T1 scrive la stringa letta in coda al file F1
- T2 scrive la stringa letta in testa al file F2
- T1 e T2 terminano quando lo stream su standard input è terminato
- quando T1 e T2 terminano, il main thread stampa a schermo il numero di byte complessivamente scritta da T1 e T2 e termina

// Nota: Assumere che le stringhe hanno tutte la stessa taglia


SPECS (ENG):

Implement a program that takes 2 filenames F1 and F2 as arguments
- The main thread creates two threads/processes T1 and T2
- T1 and T2 repeatedly read from standard input strings (without spaces) without any precise order
- T1 writes the string read at the end of file F1
- T2 writes the string read at the head of the file F2
- T1 and T2 end when the standard input stream is finished
- when T1 and T2 terminate, the main thread prints the total number of bytes written by T1 and T2 and terminates

// Note: you can assume that strings keeps the same number of chars


****************************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void* T1_function(){
    printf("Test from threads\n");
    sleep(3);
    printf("Ending thread\n");
}

int main(int argc,char* argv[]){
    pthread_t t[3];
    int i;
    for(i=0;i<4;i++) pthread_create(t+i, NULL, T1_function, NULL);
     for(i=0;i<4;i++) pthread_join(t[i], NULL);
}