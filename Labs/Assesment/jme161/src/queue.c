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
    // pthread_mutex_t lock;
    
    // pthread_mutex_t head_lock;

    // struct QueueStruct *next;
    // void *value;

    void *value;
    struct QueueStruct *front;
    struct QueueStruct *rear;
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
    queue->front = queue->rear = NULL;

    // pthread_mutex_init(&queue->lock, NULL);
    // sem_init(&queue->read, 0, 0);
    // // sem_init(&queue->write, 0, 1);

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
    // free(queue->next);
    // free(queue);

    // Queue *head = NULL;

    // for (Queue *l = queue; l != NULL;) {
    //     Queue *next = l->next;
    //     free(l);

    //     l = next;
    // }
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
    // Queue *head = (Queue*)malloc(sizeof(Queue));
   
    // // wait until the queue has been written to
    // // sem_wait(&queue->read);

    // pthread_mutex_lock(&queue->lock);
	// // queue->store[queue->tail++] = *(int*)item; 

    // head->next = head;
    // head->value = item;

    // pthread_mutex_unlock(&queue->lock);
    // sem_post(&queue->write);

    Queue *queue_ = (Queue*)malloc(sizeof(Queue));

    queue_->value = item;
    queue_->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = queue_;
    } else {
        queue->rear->next = queue_;
        queue->rear = queue_;
    }
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
    void *item = malloc(sizeof(void));
    // void *item = 0;

    // Queue *head, *next; 
    // // sem_wait(&queue->read);
    
    // int sum = 10;
    // queue->front = queue->front->next;
    // item = queue->front->value;

    // queue_put(queue, item);
    // item = (int*)&sum;
    int b = 10;
    int *a = &b;
    item = (void*)a;

    
    // printf("%d\n", *(int*)item);
    // queue_put(queue, &item);
    
    // // pthread_mutex_lock(&queue->lock);
    // item = (void*)&queue->store[queue->head++]; 
    // // pthread_mutex_unlock(&queue->lock);
    // // sem_post(&queue->read)
    
    
    // // sem_post(&queue->read);
    
    // printf("%d\n", *(int*)item);
    // puts("here");
    

    return item;
}































// #define QUEUE_POISON1 ((void*)0xCAFEBAB5)

// typedef struct QueueStruct {
// 	struct QueueStruct *head;
// 	pthread_mutex_t head_lock;

// 	struct QueueStruct *tail;
// 	pthread_mutex_t tail_lock;

// 	struct QueueStruct *divider;
// } Queue;


// Queue *queue_alloc(int size)
// {
// 	Queue *root = 
// 		malloc(sizeof(Queue));
// 	pthread_mutex_init(&root->head_lock, NULL);
// 	pthread_mutex_init(&root->tail_lock, NULL);

// 	root->divider = NULL;
// 	root->head = root->divider;
// 	root->tail = root->divider;
// 	return root;
// }


// // void INIT_QUEUE_HEAD(struct queue_head *head)
// // {
// // 	head->next = QUEUE_POISON1;
// // }


//  void queue_put(Queue *queue, void *item)
// {
// 	// new->next = NULL;

// 	pthread_mutex_lock(&queue->tail_lock);
// 	queue->tail = (Queue*)item;
// 	pthread_mutex_unlock(&queue->tail_lock);
// }


// void *queue_get(Queue *queue)
// {
// 	Queue *head, *next = NULL;

	// while (1) {
	// 	pthread_mutex_lock(&queue->head_lock);
	// 	head = queue->head;
	// 	// next = head->next;
	// 	if (next == NULL) {
	// 		pthread_mutex_unlock(&queue->head_lock);
	// 		return NULL;
	// 	}
	// 	queue->head = next;
	// 	pthread_mutex_unlock(&queue->head_lock);
		
	// 	if (head == queue->divider) {
	// 		queue_put(head, queue);
	// 		continue;
	// 	}

		// queue->head = QUEUE_POISON1;
	// }
// }
