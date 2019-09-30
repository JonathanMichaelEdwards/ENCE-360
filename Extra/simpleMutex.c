#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


#define NTHREADS 5

pthread_mutex_t lock;
sem_t read;
sem_t write;
int counter = 0;


void *printThread(void *x)
{
    pthread_mutex_lock(&lock);
    printf("-- Hi from thread %d!\n", counter++);
    pthread_mutex_unlock(&lock);

    return NULL;
}


int main(int argc, char *argv[])
{
    pthread_t threads[NTHREADS];
    int thread_args[NTHREADS];

    pthread_mutex_init(&lock, NULL);
    sem_init(&read, 0, 0);
    sem_init(&write, 0, 1);
    
    
    /* spawn the threads */
    for (int i = 0; i < NTHREADS; i++) {
        thread_args[i] = i;
        // printf("spawning thread %d\n", i);
        
        pthread_create(&threads[i], NULL, printThread, &thread_args[i]);
    }

    /* wait for threads to finish */
    for (int i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    return 1;
}