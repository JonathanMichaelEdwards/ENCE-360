#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>


int has_run[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


void runMe(int *arg) 
{
    int value = (*arg);
    assert(value >= 0 && value < 5 && "Bad argument passed to 'runMe()!'");
    
    has_run[value] = 1;
    
    int *ret = (int*)malloc(sizeof(int));
    *ret = value * value; 

    pthread_exit((void*)ret);
}


int run_threads(int n) 
{
    pthread_t threads[n];
    int sum;
    void *status = 0;

    // Create the threads
    for (int i = 0; i < n; i++) {
        int *thread = (int*)&threads[i];
        pthread_create((pthread_t*)&thread, NULL, (void*)&runMe, (void*)&sum);
    }

    // Wait for threads to finish
    for (int i = 0; i < n; i++) {
        puts("problem1");
        pthread_join(threads[i], &status);  // problem confused
        puts("problem2");
    }

    return (int)*((int*)&status);
}


int main (int argc, char **argv) 
{ 
  
  int sum = run_threads(5);

  int correct = 0;
  for(int i = 0; i < 5; ++i) {
    if(has_run[i]) correct++;
  }

  printf("%d %d\n", correct, sum);

  return 0;
}