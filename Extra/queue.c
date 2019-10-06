#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 


#define CAPACITY 1000


// A structure to represent a queue 
typedef struct { 
	int head, tail, size; 
	int *store; 
	void **value;
} Queue; 


// function to create a queue of given capacity. 
// It initializes size of queue as 0 
Queue *createQueue(int capacity) 
{ 
	Queue *queue = (Queue*)malloc(sizeof(Queue)); 
	queue->store = (int*)malloc(sizeof(queue->store) * capacity); 
    queue->head = queue->tail = queue->size = 0; 
	queue->value[12] = queue->value;

	return queue; 
} 


// Queue is full when size becomes equal to the capacity 
int isFull(Queue *queue) { return (queue->size == CAPACITY); }


// Queue is empty when size is 0 
int isEmpty(Queue *queue) { return (queue->size == 0); } 


// Function to add an item to the queue. 
// It changes tail and size 
void enqueue(Queue *queue, int item) 
{ 
	if (isFull(queue)) 
		return; 
	
	queue->store[queue->tail++] = item; 
	queue->size += 1; 
    
	printf("(+) %d enqueued to queue\n", item); 
} 


// Function to remove an item from queue. 
// It changes head and size 
void dequeue(Queue *queue) 
{ 
	if (isEmpty(queue)) 
		return; 

    int item = queue->store[queue->head++];  
    queue->size += 1;

	printf("(-) %d dequeued from queue\n", item);
} 


// Function to get head of queue 
// First node to get deleted
int head(Queue *queue) 
{ 
	if (isEmpty(queue)) 
		return 0; 

	return queue->store[queue->size-queue->tail]; 
} 


// Function to get tail of queue 
int tail(Queue *queue) 
{ 
	if (isEmpty(queue)) 
		return 0; 

	return queue->store[queue->tail-1]; 
} 


void printQueue(Queue *queue)
{
    int i = queue->head;;

    printf("\nQueue: [ ");
    while(i < queue->tail)
        printf("%d ",queue->store[i++]);
    puts("]");

    printf("\nFront item is %d\n", head(queue)); 
	printf("tail item is %d\n", tail(queue)); 
}


// gcc -std=c99 -Werror -Wall -g queue.c -o queue -lpthread && valgrind ./queue
int main() 
{ 
	Queue *queue = createQueue(CAPACITY); 

	// enqueue(queue, 10); 
	// enqueue(queue, 20); 
	// enqueue(queue, 30); 
	// enqueue(queue, 40); 
    // dequeue(queue);
    // enqueue(queue, 100); 
    // enqueue(queue, 60);
    // dequeue(queue);

    // printQueue(queue);

	// free(queue->store);
	// free(queue);
	int a = 1;
	queue->value[0] = (void*)&a;


	exit(EXIT_SUCCESS); 
} 
