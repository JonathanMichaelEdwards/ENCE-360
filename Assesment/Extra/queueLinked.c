#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0
#define FULL 10



typedef struct queue {
    sem_t read;
    sem_t write;

    pthread_mutex_t lockTail;
    pthread_mutex_t lockHead;

    void *value;
    int size;
    struct queue *next;
    struct queue *head;
    struct queue *tail;
} Queue;


// typedef struct queueStore {
//     // pthread_mutex_t lockTail;
//     // pthread_mutex_t lockHead;

//     struct queueStore *head;
//     struct queueStore *tail;
//     Queue *queueInfo;
// } QueueStore;


pthread_mutex_t lock;

Queue *queue_alloc(int size) 
{
    // QueueStore *queueStore = (QueueStore*)malloc(sizeof(QueueStore));
    Queue *queue = (Queue*)malloc(sizeof(Queue));

    queue->next = NULL;
    queue->head = NULL;
    queue->tail = NULL;
    queue->value = malloc(sizeof(void));
    queue->size = 0;

    pthread_mutex_init(&queue->lockHead, NULL);
    pthread_mutex_init(&queue->lockTail, NULL);
    pthread_mutex_init(&lock, NULL);

    sem_init(&queue->read, 0, 0);
    sem_init(&queue->write, 0, 1); 


    return queue;
}


int size1 = 0;
void enqueue(Queue *queue, void *value)
{
    // sem_wait(&queue->write);
    // pthread_mutex_lock(&queue->lockHead);  


    Queue *queue_ = (Queue*)malloc(sizeof(Queue));

    queue_->value = value;
    queue_->next = NULL;

    if (queue->tail == NULL) {
        queue->head = queue->tail = queue_;
    } else {
        queue->tail->next = queue_;
        queue->tail = queue_;
        if (size1 == 0) {
            queue->head->value = value;
        }
    }
    
    // if (queue->head->next != NULL) 
    size1++;

    printf("Queuing: %d\n", *(int*)queue_->value);


    // pthread_mutex_unlock(&queue->lockTail);
    // sem_post(&queue->read);
}


void dequeue(Queue *queue)
{
    //Queue *queue_ = queue->head;
    // sem_wait(&queue->read);
    pthread_mutex_lock(&lock);
    
    // while (queue->head->next != NULL) {
    // if (queue->size > 0) {
    //     // if (item != NULL) 
    //     // if (queue->head != NULL) {

    //     printf("dequeue: %d\n", *(int*)queue->head->value);
    //     queue->head = queue->head->next;
    //     queue = queue->next;
    //     // }
    // }
    // if (queue != NULL) {
    if (queue->head != NULL) {
        if (queue->head->value != NULL) printf("got: %d\n", *(int*)queue->head->value); 
        queue->head = queue->head->next;
        queue = queue->next;

        size1--;
    }
    // }
        // break;
    // }
    pthread_mutex_unlock(&lock);
    // sem_post(&queue->write);
}


void printList(Queue *list)
{
    while (list != NULL) {
        printf("%d", *(int*)list->value);
        if(list->next != NULL) printf(", ");
        list = list->next;
    }
    puts("");
}


void free_list(Queue *list) {

    for (Queue *l = list; l != NULL;) {
        Queue *next = l->next;
        free(l);

        l = next;
    }
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
    // sem_wait(&write);
    // pthread_mutex_lock(&lock);
    // pthread_mutex_lock(&lock2);

    // pthread_mutex_lock(&queue->lockHead);   
    // pthread_mutex_lock(&queue->lockTail);


    // Block the queue if it is full
    Queue *queue_ = (Queue*)malloc(sizeof(Queue));

    queue_->value = item;
    queue_->next = NULL;
    
    // printf("size: %d\n", 
    if (queue->tail == NULL) {
        queue->head = queue->tail = queue_;
    } else {
        queue->tail->next = queue_;
        queue->tail = queue_;
        if (size == 0) {
            queue->head->value = item;
        }
    }

    // queue->value = item;
    // queue->size++;
    // if (queue->head->next != NULL) 
    size++;

    // printf("send ");
    if (item != NULL) 
        printf("sent: %d\n", *(int*)item);

    // pthread_mutex_unlock(&queue->lockTail);
    // pthread_mutex_unlock(&queue->lockHead);
    // pthread_mutex_unlock(&lock2);
    // pthread_mutex_unlock(&lock);
    // sem_post(&read);
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
    // sem_wait(&read);
    // // sem_wait(&queue->stop1);
    // pthread_mutex_lock(&lock);
    // pthread_mutex_lock(&lock2);
    // // pthread_mutex_lock(&queue->lockTail);
    // pthread_mutex_lock(&queue->lockHead);

    // Block the queue if it is empty
    void *item = malloc(sizeof(void));


    // Goes over one to many hence program blocks.

    
    if (queue->head != NULL) {
        item = queue->head->value;
        if (queue->head->value != NULL) printf("got: %d\n", *(int*)queue->head->value); 
        queue->head = queue->head->next;
        queue = queue->next;

        size--;
    } 
    // if (queue->head != NULL) item = queue->head->value;
    

    // sem_destroy(&write);
    // sem_destroy(&read);

    // pthread_mutex_unlock(&lock2);
    // pthread_mutex_unlock(&lock);
    // // sem_post(&queue->stop2);
    // sem_post(&write);


    return item;
}

// gcc -g -Wall -std=gnu99 queueLinked.c -o queueLinked && ./queueLinked
int main()
{
    Queue *queue = queue_alloc(12);

    int a = 10;
    // int b = 20;
    // int c = 30;
    // int d = 60;


    // dequeue(queue);
    // dequeue(queue);
    // dequeue(queue);
    // dequeue(queue);
    // dequeue(queue);
    // dequeue(queue);

    // enqueue(queue, (void*)&a);
    // enqueue(queue, (void*)&b);
    // enqueue(queue, (void*)&c);
    // enqueue(queue, (void*)&d);
    // enqueue(queue, (void*)&a);
    // enqueue(queue, (void*)&b);

    queue_put(queue, (void*)&a);
    // queue_put(queue, (void*)&b);
    // queue_put(queue, (void*)&c);
    // queue_put(queue, (void*)&d);
    // queue_put(queue, (void*)&a);
    // queue_put(queue, (void*)&b);

    void *item = queue_get(queue);
    printf("item: %d\n", *(int*)item);

    
    printList(queue->head);
    // dequeue(queue);
    // printList(queue->head);
    // dequeue(queue);
    // printList(queue->head);
    // dequeue(queue);
    // printList(queue->head);
    // dequeue(queue);
    // printf("Queue after dequeue\n");
    // printList(queue->head);

    // free(queue->value);
    // free_list(queue);

    return EXIT_SUCCESS;
}