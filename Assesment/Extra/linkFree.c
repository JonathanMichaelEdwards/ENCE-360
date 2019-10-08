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
    // pthread_mutex_unlock(&queue->lockHead);
}


void dequeue(Queue *queue)
{
    //Queue *queue_ = queue->front;

    
    // while (queue->front->next != NULL) {
    if (queue->size > 0) {
        queue->front = queue->front->next;
        queue = queue->next;
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


void *queue_get(Queue *queue) 
{   
    void *item = malloc(1000);

    int b = 10;
    int *a = &b;
    item = (void*)a;

    return item;
}


typedef struct {
    int value;
} Task;


void test()
{
    //// queue.c
    void *item = malloc(100);  // just setting sum space for this example

    int b = 10;
    item = (void*)&b;
    ///

    // queue_test.c
    Task *task = (Task*)item;
    printf("%d\n", task->value);  // 10 is outputted

    free(task);  
    //
}


// gcc -g -Wall -std=gnu99 queueLinked.c -o queueLinked && ./queueLinked
void test2()
{
    //// queue.c
    Queue *queue = queue_alloc(12);

    printf("%d\n", *(int*)queue->value);
    
    // enqueue(queue, 10);
    // enqueue(queue, 20);
    // enqueue(queue, 50);
    // printList(queue->front);
    // dequeue(queue);
    // printList(queue->front);

    // void *item = (void*)&queue->front->data;
    // ///

    // // queue_test.c
    // Task *task = (Task*)item;
    // printf("%d\n", task->value);  // 10 is outputted

    // // free(task);  
    // // free(queue->front);
    // free_list(queue->front);
    // free(queue);
    //
}


int main()
{
    Queue *queue = queue_alloc(12);

    int a = 10;
    int b = 20;


    dequeue(queue);
    enqueue(queue, (void*)&a);
    enqueue(queue, (void*)&b);
    enqueue(queue, (void*)&a);
    printf("Queue before dequeue\n");
    printList(queue->front);
    dequeue(queue);
    printf("Queue after dequeue\n");
    printList(queue->front);

    // free(queue->value);
    // free_list(queue->next);
    free_list(queue);


    return EXIT_SUCCESS;
}

