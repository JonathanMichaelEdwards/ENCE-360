
/****************************************************************
 File: Queue.c
 ----------------
 This file implements the IntQueue interface given in IntQueue.h.
 ****************************************************************/

#include <stdlib.h>
#include <stdio.h>


/****************************************************************
 The queue is implemented as a linked list of nodes, each
 containing an int queue entry and a pointer to the next node.
*/
struct node { 
	int data;
	struct node *next; 
};
typedef struct node Node;

/****************************************************************
 The state of the queue is encapsulated in this struct, which
 contains a pointer to the head and tail of the queue. The IntQueue
 ADT is a pointer to a struct of this type.
*/
struct queue {
	Node *head;
	Node *tail;
};

/*****************************************************************/
IntQueue createQueue() 
{ 

	IntQueue queue = (IntQueue) malloc(sizeof(struct intqueue));
	
	if (queue == NULL) { 
		printf("Out of memory!\n");
		exit(1);
	} 
	
	queue->head = NULL;
	queue->tail = NULL;
	
	return queue;
} 

/*****************************************************************/
int isEmpty (IntQueue queue)
{
	return (queue->head == NULL) && (queue->tail == NULL);
}

/****************************************************************
 Implementation note: Each dequeue both removes the element from
 the queue and deallocates the node. The last call to free()
 deallocates the intqueue struct.
*/
void deleteQueue(IntQueue queue) 
{ 

	do { 
		dequeue(queue);
	} while (!isEmpty(queue));
	
	free(queue);
} 

/****************************************************************
 Implementation note: This is a private function for creating
 an intqueue node pointer with given data contents. It's only
 here to make enqueue() a little easier to read.
*/
static Node *createNode(int data) 
{ 
	Node *node = (Node *) malloc(sizeof(Node));
	
	if (node == NULL) { 
		printf("Out of memory!\n");
		exit(1);
	} 
	
	node->data = data;
	node->next = NULL;

	return node;
} 

/****************************************************************
 Implementation note: Since an empty queue just consists of a
 NULL head and tail, it is necessary to distinguish that as a
 special case. A similar comment holds for dequeue.
*/
void enqueue(IntQueue queue, int data) 
{ 
	Node *node = createNode(data);
	
	if (!isEmpty(queue)) {
		queue->tail->next = node;
		queue->tail = queue->tail->next;
	}
	else {
		queue->head = node;
		queue->tail = node;
	}
}

/*****************************************************************/
int dequeue(IntQueue queue) 
{ 
	Node *temp;
	int data;

	if (queue->head == NULL) { 
		// Queue is empty
		return 0;
	} 
	else { 
		temp = queue->head;
		queue->head = queue->head->next;

		if (queue->head == NULL) { 
			queue->tail = NULL;
		} 

		data = temp->data;
		free(temp);
		return data;
	}
} 

/*****************************************************************/
void printQueue (IntQueue queue)
{
	Node *current;

	if (isEmpty(queue)) {
		printf("Attempt to print empty queue failed.\n");
		return;
	}

	current = queue->head;

	printf("%d  ", current->data);
	while (current != queue->tail) {
		current = current->next;
		printf("%d  ", current->data);
	}
	printf("\n");
}