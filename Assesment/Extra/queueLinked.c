#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>



int size = 0;
int capacity = 0;


typedef struct queue {
    void *value;
    struct queue *next;
    struct queue *head;
    struct queue *tail;
} Queue;


Queue *queue_alloc(int size) 
{
    Queue *queue = (Queue*)malloc(sizeof(Queue));

    queue->next = NULL;
    queue->head = NULL;
    queue->tail = NULL;
    queue->value = NULL;
    capacity = size;

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


void free_list(Queue *list)
 {

    for (Queue *l = list; l != NULL;) {
        Queue *next = l->next;
        free(l);

        l = next;
    }
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
    Queue *queue_ = NULL;
    
    if (size < capacity) {
        tempQueue(&queue_, item);
        if (queue->tail == NULL) {
            queue->head = queue->tail = queue_;
        } else {
            queue->tail->next = queue_;
            queue->tail = queue_;
            if (size == 0) {
                queue->head = queue_;
            }
        }
        size++;
    }

    // printf("(+) %d\n", *(int*)item);
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
    void *item = NULL;
    Queue *temp = NULL;

    if (queue->head != NULL) {
        temp = queue->head;
        queue->head = queue->head->next;

        if (queue->head == NULL) { 
			queue->tail = NULL;
		} 

        item = temp->value;
        free(temp);

        size--;
        
    } 

    
    // printf("(-) %d\n", *(int*)item);

    return item;
}



void test()
{
    Queue *queue = queue_alloc(2);

    int a = 10;
    int b = 20;
    int c = 30;
    int d = 60;

    queue_put(queue, (void*)&a);
    printList(queue->head);

    queue_get(queue);
    printList(queue->head);
    
    queue_put(queue, (void*)&b);
    printList(queue->head);

    queue_put(queue, (void*)&c);
    printList(queue->head);

    queue_get(queue);
    printList(queue->head);

    queue_put(queue, (void*)&d);
    printList(queue->head);

    queue_put(queue, (void*)&d);
    printList(queue->head);

    queue_put(queue, (void*)&a);
    printList(queue->head);

    queue_put(queue, (void*)&a);
    printList(queue->head);

    free_list(queue->head);
    free(queue);
}


// gcc -g -Wall -std=gnu99 queueLinked.c -o queueLinked && ./queueLinked
int main()
{
    test();

    return EXIT_SUCCESS;
}