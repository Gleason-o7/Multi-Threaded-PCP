#ifndef BUFFER_H
#define BUFFER_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 50
#define LINE_LENGTH 1000

typedef struct {
    char lines[BUFFER_SIZE][LINE_LENGTH];
    int p_index;
    int c_index;
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t full;
    pthread_cond_t empty;
} Buffer;

void initBuffer(Buffer *b);
void printBuffer(Buffer *b);

#endif
