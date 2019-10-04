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
    sem_t read;
    sem_t write;

    pthread_mutex_t lockTail;
    pthread_mutex_t lockHead;

    void *value;
    int size;

    struct QueueStruct *next;
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
    queue->value = NULL;
    queue->size = 0;

    pthread_mutex_init(&queue->lockHead, NULL);
    pthread_mutex_init(&queue->lockTail, NULL);

    sem_init(&queue->read, 0, 0);
    sem_init(&queue->write, 0, 1); 

    return queue;
}


void free_list(Queue *list) 
{
    for (Queue *l = list; l != NULL;) {
        Queue *next = l->next;
        free(l);

        l = next;
    }
}


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
    free(queue);
}




//
// Print all the values in a linked list structure
//
void print_list(Queue *list) {
    for (Queue*l = list; l != NULL; l = l->next) {
        printf("%d", *(int*)l->value);

        if (l->next) {
            printf(", ");
        }
    }

    printf("\n");
}


//
// Append a value to the front of a linked list
// the returned list now looks like:  head->rest of list 
//
Queue *append(void *x, Queue *head) 
{
    Queue *queue_ = head;
    
    queue_->next = head;
    queue_->value = x;
    queue_->size++;

    return queue_;
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
// int arr[20];

void queue_put(Queue *queue, void *item) 
{   
    sem_wait(&queue->write);
    pthread_mutex_lock(&queue->lockTail);
    
    // queue->next = NULL;
    // queue->value = item;
    // queue->size++;
    queue = append(item, queue);

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
// make && ./queue_test
void *queue_get(Queue *queue) 
{
    void *item = NULL;

    sem_wait(&queue->read);
    pthread_mutex_lock(&queue->lockTail);

    if (queue->size > 0) {
        item = queue->value;
    }
    // queue->size--;

    pthread_mutex_unlock(&queue->lockTail);
    sem_post(&queue->write);

    return item;
}
