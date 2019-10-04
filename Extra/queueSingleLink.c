#include <stdio.h>
#include <stdlib.h>

// Data Structure to store a linked list node
struct Node
{
	int data;
	struct Node* next;
};

// Helper function to print given linked list
void printList(struct Node* head)
{
	struct Node* ptr = head;
	while (ptr)
	{
		printf("%d -> ", ptr->data);
		ptr = ptr->next;
	}

	printf("null\n");
}

// Helper function to insert new Node in the beginning of the linked list
void push(struct Node* head, int data)
{
	// Allocate the new Node in the heap and set its data
	// struct Node* newNode = head;
	head->data = data;

	// Set the .next pointer of the new Node to point to the current
	// first node of the list.
	head = head->next;

	// Change the head pointer to point to the new Node, so it is
	// now the first node in the list.
	// head = newNode;
}

// The opposite of Push(). Takes a non-empty list and removes the front
// node, and returns the data which was in that node.
int pop(struct Node** headRef)
{
	// underflow condition
	if (*headRef == NULL)
		return -1;

	struct Node* head = *headRef;
	int result = head->data; // pull out data before node is deleted

	(*headRef) = (*headRef)->next;  // unlink the head node for the caller
									// Note the * -- uses a reference-pointer
									// just like Push() and DeleteList().

	free(head);				 // free the head node

	return result;			  // don't forget to return the data from link
}


// main method
int main(void)
{
	// input keys
	int keys[] = {1, 2, 3, 4};
	int n = sizeof(keys)/sizeof(keys[0]);

	// points to the head node of the linked list
	struct Node* head = malloc(sizeof(struct Node));

	// construct linked list
	for (int i = n-1; i >= 0; i--)
		push(head, keys[i]);
        

	// int i = pop(&head);
	// printf("Popped node %d\n", i);

	// print remaining linked list
	printList(head);

	return 0;
}