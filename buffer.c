#include "buffer.h"

void initBuffer(Buffer *b) {
    b->producer_index = 0;
    b->consumer_index = 0;
    b->count = 0;
    pthread_mutex_init(&(b->mutex), NULL);
    pthread_cond_init(&(b->full), NULL);
    pthread_cond_init(&(b->empty), NULL);
}

void printBuffer(Buffer *b) {
    pthread_mutex_lock(&(b->mutex));
    printf("=======================================\n");
    printf("Buffer State:\n");
    printf("Producer Index: %d\n", b->producer_index);
    printf("Consumer Index: %d\n", b->consumer_index);
    printf("Item Count: %d\n", b->count);
    printf("---------------------------------------\n");

    for (int i = 0; i < b->count; i++) {
        int index = (b->consumer_index + i) % BUFFER_SIZE;
        printf("Line %d: %s", index, b->lines[index]);
    }

    if (b->count == 0) {
        printf("Buffer is empty.\n");
    }

    printf("=======================================\n");

    pthread_mutex_unlock(&(b->mutex));

}

