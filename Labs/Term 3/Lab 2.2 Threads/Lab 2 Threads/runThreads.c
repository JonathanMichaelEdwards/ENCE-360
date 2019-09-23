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
    void *status = 0;
    int arg[n];
    int sum = 0;

    // Create the threads
    for (int i = 0; i < n; i++) {
        arg[i] = i;
        pthread_create(&threads[i], NULL, (void*)&runMe, &arg[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], &status);
        sum += *((int*)status);
    }

    return sum;
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