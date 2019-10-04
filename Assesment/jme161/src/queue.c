#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>

#include "queue.h"


#define handle_error_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
        do { perror(msg); exit(EXIT_FAILURE); } while (0)



/*
 * Queue - the abstract type of a concurrent queue.
 * You must provide an implementation of this type 
 * but it is hidden from the outside.
 */
typedef struct QueueStruct {
//     // sem_t mutex;
    sem_t read;
    sem_t write;

    pthread_mutex_t lockTail;
    pthread_mutex_t lockHead;

    // void *value;
    int size;
    // struct QueueStruct *front;
    // struct QueueStruct *rear;
    // struct QueueStruct *next;

    struct QueueStruct *next;
    void *value;
} Queue;


/**
 * Allocate a concurrent queue of a specific size
 * @param size   - The size of memory to allocate to the queue
 * @return queue - Pointer to the allocated queue
 */
Queue *queue_alloc(int size) 
{
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->next = NULL;
    // queue->front = NULL;
    // queue->rear = NULL;
    // queue->value = malloc(sizeof(void));
    // queue->size = 0;

    pthread_mutex_init(&queue->lockHead, NULL);
    pthread_mutex_init(&queue->lockTail, NULL);

    // sem_init(&queue->mutex, 0, 1);
    sem_init(&queue->read, 0, 0);
    // sem_init(&queue->write, 0, size-1); 
    sem_init(&queue->write, 0, 1); 

    return queue;
}


// void free_list(Queue *list) 
// {

//     for (Queue *l = list; l != NULL;) {
//         Queue *next = l->next;
//         free(l);

//         l = next;
//     }
// }


/**
 * Free a concurrent queue and associated memory 
 *
 * Don't call this function while the queue is still in use.
 * (Note, this is a pre-condition to the function and does not need
 * to be checked)
 * 
 * @param queue - Pointer to the queue to free
 */
void queue_free(Queue *queue) 
{
    // free_list(queue->front);
    // free(queue->store);
    // free(queue);
}


/**
 * Place an item into the concurrent queue.
 * If no space available then queue will block
 * until a space is available when it will
 * put the item into the queue and immediatly return
 *  
 * @param queue - Pointer to the queue to add an item to
 * @param item  - An item to add to queue. Uses void* to hold an arbitrary
 *               type. User's responsibility to manage memory and ensure
 *               it is correctly typed.
 */

int a = 0;


void queue_put(Queue *queue, void *item) 
{   
    // if (a > 16) return;

    sem_wait(&queue->write);
    pthread_mutex_lock(&queue->lockTail);

    // queue_->value = item;
    // queue_->next = NULL;
    
    // if (queue->rear == NULL) {
    //     queue->front = queue->rear = queue_;
    // } else {
    //     queue->rear->next = queue_;
    //     queue->rear = queue_;
    // }
    // struct Link *head_ = (struct Link*)malloc(sizeof(struct Link));
    queue->next = NULL;
    queue->value = item;

    queue->size++;
    

    // printf("%d\n", *(int*)queue->rear->value);


    pthread_mutex_unlock(&queue->lockTail);
    sem_post(&queue->read);
}


/**
 * Get an item from the concurrent queue
 * 
 * If there is no item available then queue_get
 * will block until an item becomes avaible when
 * it will immediately return that item.
 * 
 * @param queue - Pointer to queue to get item from
 * @return item - item retrieved from queue. void* type since it can be 
 *                arbitrary 
 */
///// Need to signal to quit

// make && valgrind ./queue_test
void *queue_get(Queue *queue) 
{
    // if (a > queue->size) return NULL;
    

    sem_wait(&queue->read);
    // pthread_mutex_lock(&queue->lockTail);

    // Queue *queue_ = queue->front;

    // if (queue->rear == NULL) return;

    void *item = malloc(sizeof(void));

    // printf("%d\n", queue->size);

    if (queue->size > 0) {
        // printf("%d\n", *(int*)(queue->value));
        item = queue->value;
        // queue->front = queue->front->next;
        // queue = queue->next;
        
        // // return item;
        // printf("%d\n", *(int*)item);
    }
    

    // printf("%d\n", *(int*)queue->value);
    // item = queue->front->value;
    // queue->front = queue->front->next;
    // free(queue_);


    // pthread_mutex_unlock(&queue->lockTail);
    sem_post(&queue->write);

    // if (queue->count > queue->size) return NULL;

    return item;
}
