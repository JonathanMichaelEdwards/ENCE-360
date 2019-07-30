#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct {
    float *total;
    int n;

    pthread_mutex_t *lock;
    pthread_t thread;

} Worker;


void *secondThread(void *ptr) {
    int i = 0;
    printf("%d\n", ptr);
    while (i < 10000) i++;

    return NULL;
}


int main(int argc, char const *argv[])
{
    pthread_t thread;

    puts("First Thread 1.");

    // int arg = 123;

    Worker *worker = (Worker*)malloc(10);
    pthread_create(&thread, NULL, secondThread, NULL);//(void*)&worker);
    pthread_join(thread, NULL);  // adding new thread

    return EXIT_SUCCESS;
}
