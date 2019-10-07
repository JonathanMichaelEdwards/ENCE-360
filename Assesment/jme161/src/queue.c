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
    // sem_t read;
    // sem_t write;
    sem_t stop1;
    sem_t stop2;

    // pthread_mutex_t lockTail;
    pthread_mutex_t lockHead;

    void *value;
    int size;
    int capacity;
    struct QueueStruct *front;
    struct QueueStruct *rear;
    struct QueueStruct *next;
} Queue;


// typedef struct {
pthread_mutex_t lock;
pthread_mutex_t lock2;

sem_t read;
sem_t write;

//     // Queue *queue;
// } Manager;


/**
 * Allocate a concurrent queue of a specific size
 * @param size   - The size of memory to allocate to the queue
 * @return queue - Pointer to the allocated queue
 */
Queue *queue_alloc(int size) 
{
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    // Manager *manage = (Manager*)malloc(sizeof(Manager));
    queue->next = NULL;
    queue->front = NULL; //(Queue*)malloc(sizeof(Queue));;
    queue->rear = NULL;
    queue->capacity = size;
    queue->size = 0;

    

    // pthread_mutex_init(&queue->lockHead, NULL);
    pthread_mutex_init(&lock, NULL);
    // pthread_mutex_init(&queue->lockTail, NULL);

    sem_init(&read, 0, 0);
    sem_init(&write, 0, 1); 
    sem_init(&queue->stop1, 0, 0);
    sem_init(&queue->stop2, 0, 1);

    // sem_init(&queue->read, 0, 0);
    // sem_init(&queue->write, 0, 1); 

    return queue;
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

int size = 0;
void queue_put(Queue *queue, void *item) 
{   
    // Manager *manage = (Manager*)malloc(sizeof(Manager));

    // if (queue->size == 10) {
    //     sem_destroy(&read);
    //     sem_destroy(&write);
    // }

    // sem_wait(&queue->stop2);
    sem_wait(&write);
    pthread_mutex_lock(&lock);
    // pthread_mutex_lock(&lock2);

    // pthread_mutex_lock(&queue->lockHead);   
    // pthread_mutex_lock(&queue->lockTail);


    // Block the queue if it is full
    Queue *queue_ = (Queue*)malloc(sizeof(Queue));

    queue_->value = item;
    queue_->next = NULL;
    
    // printf("size: %d\n", 
    if (queue->rear == NULL) {
        queue->front = queue->rear = queue_;
    } else {
        queue->rear->next = queue_;
        queue->rear = queue_;
        if (size == 0) {
            queue->front->value = item;
        }
    }

    // queue->value = item;
    // queue->size++;
    // if (queue->front->next != NULL) 
    size++;

    // printf("send ");
    // if (item != NULL) 
        // printf("sent: %d\n", *(int*)item);

    // pthread_mutex_unlock(&queue->lockTail);
    // pthread_mutex_unlock(&queue->lockHead);
    // pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock);
    sem_post(&read);
    // sem_post(&queue->stop1);
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
void *queue_get(Queue *queue) 
{
    sem_wait(&read);
    // sem_wait(&queue->stop1);
    pthread_mutex_lock(&lock);
    // pthread_mutex_lock(&lock2);
    // // pthread_mutex_lock(&queue->lockTail);
    // pthread_mutex_lock(&queue->lockHead);

    // Block the queue if it is empty
    void *item = malloc(sizeof(void));


    // Goes over one to many hence program blocks.
    if (queue->front->next != NULL) {
        item = queue->front->value;
        // if (queue->front->value != NULL) printf("got: %d\n", *(int*)queue->front->value); 
        queue->front = queue->front->next;
        queue = queue->next;
    } else if (queue->front != NULL) item = queue->value;

    size--;
    

    // sem_destroy(&write);
    // sem_destroy(&read);

    // pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock);
    // sem_post(&queue->stop2);
    sem_post(&write);


    return item;
}
