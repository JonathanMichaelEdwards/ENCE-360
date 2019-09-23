// C program to demonstrate working of Semaphores 
#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 


sem_t mutex; 


void *thread1(void *arg) 
{ 
	//wait 
	sem_wait(&mutex); 
	printf("\nEntered 1..\n"); 

	//critical section 
	sleep(4); 
	
	//signal 
	printf("\nJust Exiting 1...\n"); 
	sem_post(&mutex); 

	return NULL;
} 


void *thread2(void *arg) 
{ 
	//wait 
	sem_wait(&mutex); 
	printf("\nEntered 2..\n"); 

	//critical section 
	sleep(4); 
	
	//signal 
	printf("\nJust Exiting 2...\n"); 
	sem_post(&mutex); 

	return NULL;
} 


int main() 
{ 
	pthread_t t1, t2; 
	sem_init(&mutex, 0, 1); 

	pthread_create(&t1, NULL, thread1, NULL); 
	sleep(2); 
	pthread_create(&t2, NULL, thread2, NULL); 

	pthread_join(t1,NULL); 
	pthread_join(t2,NULL); 

	sem_destroy(&mutex); 

	return 0; 
} 
