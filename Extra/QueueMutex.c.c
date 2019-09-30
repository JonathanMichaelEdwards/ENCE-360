#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>

#define CAPACITY 1000
#define NTHREADS 1


// A structure to represent a queue 
typedef struct { 
	int head, tail, size; 
	int *store; 
} Queue; 


typedef struct {
    int value;
} Task;


pthread_mutex_t lock;
sem_t read;


Queue *createQueue(int capacity) 
{ 
	Queue *queue = (Queue*)malloc(sizeof(Queue)); 
	queue->store = (int*)malloc(sizeof(int) * capacity); 
    queue->head = queue->tail = queue->size = 0; 

	return queue; 
} 


void queue_put(Queue *queue, void *item)
{ 
	queue->store[queue->tail++] = *(int*)item; 
	queue->size += 1; 
} 


void *queue_get(Queue *queue)
{ 
    void *item = NULL;

    item = (void*)&queue->store[queue->head++];  
    queue->size += 1;

    return item;
} 


void *doSum(void *arg) {
    int sum = 0;
    Queue *queue = (Queue*)arg;

    Task *task = (Task*)queue_get(queue);
    while (task) {
        sum += task->value;
        free(task);
        // printf("%d\n", task->value);
        task = (Task*)queue_get(queue);
    }

    pthread_exit((void*)(intptr_t)sum);
}


int main(int argc, char *argv[])
{
    pthread_t threads[NTHREADS];
    int thread_args[NTHREADS];
    pthread_mutex_init(&lock, NULL);
    sem_init(&read, 0, 0);
    
    
    /* spawn the threads */
    for (int i = 0; i < NTHREADS; i++) {
        thread_args[i] = i;
        
        pthread_create(&threads[i], NULL, doSum, &thread_args[i]);
    }

    /* wait for threads to finish */
    for (int i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    return 1;
}