#include <stdio.h> 
#include <stdlib.h> 


#define BUFFER_LENGTH 100



typedef struct node {
    char *value;
    struct node *next;
} Node;


struct node *newList() 
{
    Node *head = (Node*)malloc(sizeof(Node));
    head->value = (char*)malloc(sizeof(char) * BUFFER_LENGTH);
    head->next = NULL;

    return head;
}


struct node *append(Node *head, char *x)
 {
    Node *head_ = (Node*)malloc(sizeof(Node));
    head_->next = head;
    head_->value = x;

    return head_;
}


void freeList(Node *list) 
{
    // Free the malloced ptr value 
    free(list->value);  // do this once

    // Free the malloced ptr next
    while (list) {  // freeing each space in the linked list
        Node *next = list->next;
        free(list);
        list = next;
    }
}


void printList(Node *list)
{
    while (list != NULL) {
        printf("%s, ", list->value);
        list = list->next;
    }
    puts("");
}


int main(void) 
{
    Node *list = newList();

    append(list, "Hello");
    append(list, " Jonathan");
    
    // freeList(list);

    printf("%s\n", list->value);
    // printList(list);
}