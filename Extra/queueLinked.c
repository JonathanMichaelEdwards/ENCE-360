#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0
#define FULL 10



typedef struct queue {
    pthread_mutex_t lockTail;
    pthread_mutex_t lockHead;

    void *value;
    int size;
    struct queue *front;
    struct queue *rear;
    struct queue *next;
} Queue;



Queue *queue_alloc(int size) 
{
    Queue *queue = (Queue*)malloc(sizeof(Queue) * size);

    queue->next = NULL;
    queue->front = NULL;
    queue->rear = NULL;
    queue->value = malloc(sizeof(void));
    queue->size = 0;

    // pthread_mutex_init(&queue->lockHead, NULL);
    // pthread_mutex_init(&queue->lockTail, NULL);


    return queue;
}


void enqueue(Queue *queue, void *value)
{
    Queue *queue_ = (Queue*)malloc(sizeof(Queue));

    // pthread_mutex_lock(&queue->lockHead);

    queue_->value = value;
    queue_->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = queue_;
    } else {
        queue->rear->next = queue_;
        queue->rear = queue_;
    }
    queue->size++;
    // if (value != NULL) 
    printf("Queuing: %d\n", *(int*)queue_->value);
    // pthread_mutex_unlock(&queue->lockHead);
}


void dequeue(Queue *queue)
{
    //Queue *queue_ = queue->front;

    
    // while (queue->front->next != NULL) {
    if (queue->size > 0) {
        // if (queue->front != NULL) {

        printf("dequeue: %d\n", *(int*)queue->front->value);
        queue->front = queue->front->next;
        queue = queue->next;
        // }
    }
        // break;
    // }
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
    int c = 60;


    // dequeue(queue);
    enqueue(queue, (void*)&a);
    enqueue(queue, (void*)&b);
    enqueue(queue, (void*)&c);
    // printf("Queue before dequeue\n");
    printList(queue->front);

    dequeue(queue);
    printf("Queue after dequeue\n");
    printList(queue->front);
    dequeue(queue);
    printf("Queue after dequeue\n");
    printList(queue->front);

    // free(queue->value);
    // free_list(queue);

    return EXIT_SUCCESS;
}