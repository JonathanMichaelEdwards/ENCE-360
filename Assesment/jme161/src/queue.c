#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>

#include "queue.h"

typedef struct {
    char *data;
    size_t length;

} Buffer;
typedef struct {
    char *url;
    int min_range;
    int max_range;
    Buffer *result;
}  Task;


#define handle_error_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
        do { perror(msg); exit(EXIT_FAILURE); } while (0)



/* -------- Queue --------
 * Is an abstract type of a concurrent queue.
 * You must provide an implementation of this type 
 * but it is hidden from the outside.
 */
typedef struct QueueStruct {
    void *value;

    struct QueueStruct *head;
    struct QueueStruct *tail;
    struct QueueStruct *next;
} Queue;


/* -------- Manager -------- 
 * - Stores the read and write 
 *   semephores, the lock mutex
 *   and keeps track of the size
 *   of the Queue.  
 */
typedef struct {
    int size;
    int capacity;

    sem_t read;
    sem_t write;
    pthread_mutex_t lock;
} Manager;
Manager manager;


/**
 * Allocate a concurrent queue of a specific size
 * @param size   - The size of memory to allocate to the queue
 * @return queue - Pointer to the allocated queue
 */
Queue *queue_alloc(int size) 
{
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->next = queue->head = queue->tail = NULL;
    queue->value = NULL;
    manager.capacity = size;
    manager.size = 0;

    pthread_mutex_init(&manager.lock, NULL);

    sem_init(&manager.read, 0, 0);
    sem_init(&manager.write, 0, 1); 

    return queue;
}


void freeList(Queue *list)
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
    freeList(queue->head);
    free(queue);
}


/**
 * Creates a temporary Queue 
 * 
 * @param queue - A NULL queue that stores a tem queue.
 * @param item  - An item to be added onto the queue.
 */
void tempQueue(Queue **queue_, void *item)
{
    Queue *queueTemp = (Queue*)malloc(sizeof(Queue));

    queueTemp->value = item;
    queueTemp->next = NULL;

    *queue_ = queueTemp;
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
 * Place an item into the concurrent queue.
 * If no space available then queue will block
 * until a space is available when it will
 * put the item into the queue and immediatly return
 *  
 * @param queue - Pointer to the queue to add an item to
 * @param item  - An item to add to queue. Uses void* to hold an arbitrary
 *               type. User's responsibility to manager memory and ensure
 *               it is correctly typed.
 */
void queue_put(Queue *queue, void *item) 
{   
    sem_wait(&manager.write);
    pthread_mutex_lock(&manager.lock);

    Queue *queue_ = NULL;
    
    if (manager.size < manager.capacity) {
        tempQueue(&queue_, item);
        if (queue->tail == NULL) {
            queue->head = queue->tail = queue_;
        } else {
            queue->tail->next = queue_;
            queue->tail = queue_;
            if (manager.size == 0) {
                queue->head = queue_;
            }
        }
        manager.size++;
        // printf("task: %d\n", *(int*)item);
    }

    // printf("%d %d ", manager.size, manager.capacity);
    // if (item != NULL) printList(queue->head);
    // if (item != NULL) printf("item = %c\n", *(char*)item);
    
    pthread_mutex_unlock(&manager.lock);
    sem_post(&manager.read);
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
    sem_wait(&manager.read);
    pthread_mutex_lock(&manager.lock);

    // void *item = NULL;
    void *item;// = NULL;
    Queue *temp = NULL;

    if (queue->head != NULL) {
        // item = malloc(sizeof(void) * 2);
        manager.size--;
        temp = queue->head;
        queue->head = queue->head->next;
        if (queue->head == NULL) { 
            queue->tail = NULL;
		} 
        item = temp->value;
        free(temp);
    } 
    // printf("here %d ", manager.size);
    // if (item != NULL) printList(queue->head);
    
    pthread_mutex_unlock(&manager.lock);
    sem_post(&manager.write);

    return item;
}
