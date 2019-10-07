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
        queue->value = value;
    }
    queue->size++;

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
    if (queue->size > 0) {
        // if (item != NULL) 
        printf("here %d %d\n", *(int*)queue->value, *(int*)queue->head->value); 
        // if (queue->head != NULL) {

        printf("dequeue: %d\n", *(int*)queue->head->value);
        queue->head = queue->head->next;
        queue = queue->next;
        // }
    }
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


// gcc -g -Wall -std=gnu99 queueLinked.c -o queueLinked && ./queueLinked
int main()
{
    Queue *queue = queue_alloc(12);

    int a = 10;
    int b = 20;
    int c = 30;
    int d = 60;


    // dequeue(queue);
    enqueue(queue, (void*)&a);
    enqueue(queue, (void*)&b);
    enqueue(queue, (void*)&c);
    enqueue(queue, (void*)&d);
    enqueue(queue, (void*)&a);
    enqueue(queue, (void*)&b);
    // printf("Queue before dequeue\n");
    printList(queue->head);

    dequeue(queue);
    printList(queue->head);

    dequeue(queue);
    // printf("Queue after dequeue\n");
    printList(queue->head);
    dequeue(queue);
    // dequeue(queue);
    // printf("Queue after dequeue\n");
    // printList(queue->head);

    // free(queue->value);
    // free_list(queue);

    return EXIT_SUCCESS;
}