// #include <stdio.h> 
#include <stdlib.h> 


// #define BUFFER_LENGTH 100



// typedef struct node {
//     char *value;
//     struct node *next;
// } Node;


// struct node *newList() 
// {
//     Node *head = (Node*)malloc(sizeof(Node));
//     head->value = (char*)malloc(sizeof(char) * BUFFER_LENGTH);
//     head->next = NULL;

//     return head;
// }


// struct node * getnode(char *data){
//     struct node *temp = malloc(sizeof(struct node));

//     temp->value = data;
//     temp->next = NULL;

//     return temp;
// }

// void append(Node *head, char *x)
// {
// 	struct node *right = head;

// 	while (right->next != NULL){
//        right = right->next;
//     }
// 	right->next = getnode(x);
// }

// void rem(Node *head)
// {
// 	head = head->next;
// }


// void freeList(Node *list) 
// {
//     // Free the malloced ptr value 
//     free(list->value);  // do this once

//     // Free the malloced ptr next
//     while (list) {  // freeing each space in the linked list
//         Node *next = list->next;
//         free(list);
//         list = next;
//     }
// }


// void printList(struct node *list) {
//     for (struct node *l = list; l != NULL; l = l->next) {
//         printf("%s", l->value);

//         if (l->next) {
//             printf(", ");
//         }
//     }

//     printf("\n");
// }


// int main(void) 
// {
//     Node *list = newList();

//     append(list, "Hello");
//     append(list, " Jonathan");
// 	rem(list);
    
//     // freeList(list);

//     printList(list);
// }








#include <stdio.h>
 
typedef struct node
{
    int data;
    struct node* next;
} Node;
 
/*
    init the stack
*/
Node *init()
{
    Node *node = (Node*)malloc(sizeof(Node));
	// node->data = 0;

	return node;
}
 
/*
    push an element into stack
*/
void push(struct node* head, int data)
{
    // struct node* tmp = (struct node*)malloc(sizeof(struct node));
	struct node* tmp = head;
    // if(tmp == NULL)
    // {
    //     exit(0);
    // }
    tmp->data = data;
    tmp->next = NULL;
    head = tmp;

	// head->data = data;
}
/*
    pop an element from the stack
*/
void pop(struct node *head)
{
    struct node* tmp = head;

    head = head->next;
    // free(tmp);
	head = tmp;

    // return head;
}
/*
    returns 1 if the stack is empty, otherwise returns 0
*/
int empty(struct node* head)
{
    return head == NULL ? 1 : 0;
}
 
/*
    display the stack content
*/
void display(struct node* head)
{
    struct node *current;
    current = head;
    if(current!= NULL)
    {
        printf("Stack: ");
        do
        {
            printf("%d ",current->data);
            current = current->next;
        }
        while (current!= NULL);
        printf("\n");
    }
    else
    {
        printf("The Stack is empty\n");
    }
 
}

int main(int argc, char const *argv[])
{
	Node *node = init();
	

	push(node, 10);
	push(node, 30);
	// pop(node);
	display(node);
	printf("%d\n", node->data);
	

	return 0;
}
