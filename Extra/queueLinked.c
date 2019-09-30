#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define FULL 10



typedef struct queue {
    int data;
    struct queue *front;
    struct queue *rear;
    struct queue *next;
} Queue;



void initialize(Queue *queue)
{
    queue->front = queue->rear = NULL;
}


void enqueue(Queue *queue, int value)
{
    Queue *queue_ = (Queue*)malloc(sizeof(Queue));

    queue_->data = value;
    queue_->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = queue_;
    } else {
        queue->rear->next = queue_;
        queue->rear = queue_;
    }
}


void dequeue(Queue *queue)
{
    Queue *queue_ = queue->front;

    queue->front = queue->front->next;
    free(queue_);
}


void printList(Queue *list)
{
    while (list != NULL) {
        printf("%d", list->data);
        if(list->next != NULL) printf(", ");
        list = list->next;
    }
    puts("");
}


// void freeList(Queue *list) 
// {
//     // Free the malloced ptr value 
//     // free(list->next);  // do this once

//     // Free the malloced ptr next
//     while (list != NULL) {  // freeing each space in the linked list
//         // Queue *next = list->next;
//         printf("%d ", list->data);
//         // free(list);
//         // list = next;
//         list = list->next;
//     }
// }


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


void test2()
{
    //// queue.c
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    initialize(queue);
    
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 50);
    printList(queue->front);
    dequeue(queue);
    printList(queue->front);

    void *item = (void*)&queue->front->data;
    ///

    // queue_test.c
    Task *task = (Task*)item;
    printf("%d\n", task->value);  // 10 is outputted

    free(task);  
    free_list(queue->front);
    free(queue);
    //
}


int main()
{
    // Queue *queue = malloc(sizeof(Queue));
    // Queue *tmp = queue;

    // initialize(queue);
    // tmp = enqueue(queue, 10);
    // tmp = enqueue(queue, 20);
    // tmp = enqueue(queue, 30);
    // printf("Queue before dequeue\n");
    // printList(queue->front);
    // dequeue(queue);
    // printf("Queue after dequeue\n");
    // printList(queue->front);

    // free(queue);
    // free(tmp->next);
    // free_list(queue);

    // int sum = 0;
    // Queue *queue = (Queue*)malloc(sizeof(Queue));

    // void *item = malloc(1000);

    // int b = 10;
    // int *a = &b;
    // item = (void*)a;

    // // Task *task = (Task*)queue_get(queue);
    // Task *task = (Task*)item;

    // printf("%d\n", task->value);
    // // while (task) {
    // //     sum += task->value;
    // //     // printf("%d\n", sum);
    // //     free(task);

    // //     task = (Task*)queue_get(queue);
    // // }
    // free(task);

    // test();
    test2();
    

    return EXIT_SUCCESS;
}