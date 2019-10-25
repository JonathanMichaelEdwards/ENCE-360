#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>


// int main (void)
// {
//     pid_t childId = fork();

//     if (childId == 0)
//     printf("I am Tweedledee\n");        // Child
//     else printf("I am Tweedledum\n");   // Parent

//     return EXIT_SUCCESS;
// }



void *myFunction(void* arg) 
{ 
    printf("I am Tweedledum\n"); 
    
    return NULL;
}

int main(void)
{
    pthread_t childId;
    pthread_create(&childId, NULL, myFunction, NULL);
    printf("I am Tweedledee\n");

    pthread_join(childId, NULL);  // added join to join threads

    return EXIT_SUCCESS;
}