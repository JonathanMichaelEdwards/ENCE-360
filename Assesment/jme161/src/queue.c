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
    void *value;
    int capacity;

    struct QueueStruct *head;
    struct QueueStruct *tail;
    struct QueueStruct *next;
} Queue;


typedef struct {
    pthread_mutex_t lock;

    sem_t read;
    sem_t write;

    int size;
} Manager;
Manager manage;


/**
 * Allocate a concurrent queue of a specific size
 * @param size   - The size of memory to allocate to the queue
 * @return queue - Pointer to the allocated queue
 */
Queue *queue_alloc(int size) 
{
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->next = queue->head = queue->tail = NULL;
    queue->capacity = size;
    manage.size = 0;

    pthread_mutex_init(&manage.lock, NULL);

    sem_init(&manage.read, 0, 0);
    sem_init(&manage.write, 0, 1); 

    return queue;
}


void printList(Queue *list)
{
    printf("Queue = [");
    while (list != NULL) {
        printf("%d", *(int*)list->value);
        if(list->next != NULL) printf(", ");
        list = list->next;
    }
    puts("]");
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
void queue_put(Queue *queue, void *item) 
{   
    sem_wait(&manage.write);
    pthread_mutex_lock(&manage.lock);

    Queue *queue_ = (Queue*)malloc(sizeof(Queue));

    queue_->value = item;
    queue_->next = NULL;
    
    if (queue->tail == NULL) {
        queue->head = queue->tail = queue_;
    } else {
        queue->tail->next = queue_;
        queue->tail = queue_;
        if (manage.size == 0) {
            queue->head = queue_;
        }
    }
    manage.size++;
    if (item != NULL) { printf("+ "); printList(queue->head); };

    pthread_mutex_unlock(&manage.lock);
    sem_post(&manage.read);
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
    sem_wait(&manage.read);
    pthread_mutex_lock(&manage.lock);

    void *item = malloc(sizeof(void));

    if (queue->head != NULL) {
        item = queue->head->value;
        queue->head = queue->head->next;
        queue = queue->next;
        manage.size--;
    } 
    if (item != NULL) { printf("- "); printList(queue); };
    
    pthread_mutex_unlock(&manage.lock);
    sem_post(&manage.write);

    return item;
}
