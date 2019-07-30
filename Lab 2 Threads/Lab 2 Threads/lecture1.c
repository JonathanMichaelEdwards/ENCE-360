#include <stdio.h>
#include <pthread.h>


void *secondThread(void *ptr) {
    int i = 0;
    while (i < 1000) i++;

    printf("%s\n", (char*) ptr);

    return NULL;
}


int main()
{
    pthread_t thread1, thread2;
    char *message1 = "Thread 1";
    char *message2 = "Thread 2";
    
    int thread_return1, thread_return2;

    /* Create two independent threads each of which will execute  a function 
    and print a message*/
    thread_return1 = pthread_create( &thread1, NULL, (void*)&secondThread, (void*) message1);
    thread_return2 = pthread_create( &thread2, NULL, (void*)&secondThread, (void*) message2);
    
    
    /* Wait till threads are complete before main continues. */

    // for (int i = 0; i < 2; i++) {
    //     // pthread_join(thread2, NULL);
    pthread_join( thread2, NULL); 
    pthread_join(thread1, (void**) &thread_return1);
    //     pthread_join(thread2, (void**) thread2);
    // }
    // pthread_join(thread1, (void**) thread1);

    
    puts("done!!");
   
    return 0;
}