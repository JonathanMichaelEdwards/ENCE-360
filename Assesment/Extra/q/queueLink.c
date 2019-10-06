#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>



typedef struct node {
    void *val;
    struct node *next;
} node_t;


//
// Reverse a linked list in place (modifies original list)
//
node_t *reverse_list(node_t *list) {
    node_t *head = NULL;

    for (node_t *l = list; l != NULL;) {
        node_t *next = l->next;
        l->next = head;
        head = l;

        l = next;
    }

    return head;
}


void print_list(node_t * head) 
{
    node_t * current = head;

    while (current != NULL) {
        if (current->val != NULL) printf("%d ", *(int*)current->val);
        current = current->next;
    }
}


void push(node_t *head, void *val) 
{
    node_t * current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = malloc(sizeof(node_t));
    current->next->val = val;
    current->next->next = NULL;
}


// int remove_last(node_t * head) {
//     int retval = 0;
//     /* if there is only one item in the list, remove it */
//     if (head->next == NULL) {
//         retval = head->val;
//         free(head);
//         return retval;
//     }

//     /* get to the second to last node in the list */
//     node_t * current = reverse_list(head);
//     while (current->next->next != NULL) {
//         current = current->next;
//     }

//     /* now current points to the second to last item of the list, so let's remove current->next */
//     retval = current->next->val;
//     free(current->next);
//     current->next = NULL;

//     return retval;
// }



void *pop(node_t **head) 
{
    
    // void *retval = (void*)&-1;
    node_t *next_node = NULL;

    // if (*head == NULL) {
    //     return -1;
    // }

    next_node = (*head)->next;
    // retval = (*head)->val;
    // free(*head);

    *head = next_node;

    return next_node->val;
}


void *queue_get(node_t *node) 
{
    // node_t *node2 = (node_t*)malloc(sizeof(node_t));

    // node2 = node;
    puts("yes");
    void *item = 0;//pop(&node->next);

    return item;
}


int main(int argc, char const *argv[])
{
    node_t *node = (node_t*)malloc(sizeof(node_t));

    int a = 10;
    push(node, (void*)&a);
    // push(node, 20);
    // push(node, 30);
   
    print_list(node);
    
    void *item = queue_get(node);
    
    
    printf("%d\n", *(int*)item);
    // node = reverse_list(node);
    // puts("");
    // print_list(node);


    return 0;
}
