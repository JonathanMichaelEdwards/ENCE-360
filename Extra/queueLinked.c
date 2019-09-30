#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define FULL 10



typedef struct node {
    int data;
    struct node *next;
} Node;


typedef struct {
    Node *front;
    Node *rear;
} Queue;



void initialize(Queue *queue)
{
    queue->front = queue->rear = NULL;
}


void enqueue(Queue *queue, int value)
{
    Node *tmp = malloc(sizeof(Node));

    tmp->data = value;
    tmp->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = tmp;
    } else {
        queue->rear->next = tmp;
        queue->rear = tmp;
    }
}


void dequeue(Queue *queue)
{
    queue->front = queue->front->next;
}


void printList(Node *list)
{
    while (list != NULL) {
        printf("%d", list->data);
        if(list->next != NULL) printf(", ");
        list = list->next;
    }
    puts("");
}


int main()
{
    Queue *queue = malloc(sizeof(Queue));

    initialize(queue);
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    printf("Queue before dequeue\n");
    printList(queue->front);
    dequeue(queue);
    printf("Queue after dequeue\n");
    printList(queue->front);

    return EXIT_SUCCESS;
}