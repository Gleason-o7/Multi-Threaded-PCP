//ASSIGNMENT 4: Multi-threaded Producer Consumer Pipeline
#include "buffer.h"

void *getInput(void *arg);

int main() {
	pthread_t input_t;//, sep_t, plus_t, out_t;

	Buffer buffer1;
	initBuffer(&buffer1);	

	pthread_create(&input_t, NULL, getInput, (void *)&buffer1);
	/*	
	pthread_create(&sep_t, NULL, sepLines, NULL);
	pthread_create(&plus_t, NULL, replace, NULL);
	pthread_create(&out_t, NULL, printOutput, NULL);
	*/
	
	pthread_join(input_t, NULL);
	/*
	pthread_join(sep_t, NULL);
	pthread_join(plus_t, NULL);
	pthread_join(out_t, NULL);
	*/
}


void *getInput(void *arg) {

	// Recast void * to buffer * pointing to &buffer1
	Buffer *b = (Buffer *)arg;
	char line[LINE_LENGTH];
	while (1) {
		
		// Reads up to LINE_LENGTH from stdin into line
		// Unless "STOP\n" is read
		if ((fgets(line, LINE_LENGTH, stdin) == NULL) || strcmp(line, "STOP\n") == 0) {
			break;
		}

		// Lock buffer1 
		pthread_mutex_lock(&(b->mutex));

		// Wait if the buffer is full
		while (b->count == BUFFER_SIZE) 
			pthread_cond_wait(&(b->empty), &(b->mutex));

		// Add line the the buffer
		strcpy(b->lines[b->p_index], line);
		b->p_index = (b->p_index + 1) % BUFFER_SIZE;
		b->count++;

		pthread_cond_signal(&(b->full));
		
		// Unlock buffer1
		pthread_mutex_unlock(&(b->mutex));
	}


	// indicate there is no remaining data to process
	b->count = -1;
	pthread_cond_signal(&(b->full));
	return NULL;
}
