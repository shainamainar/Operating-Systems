#include<stdio.h>
#include<assert.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

/*
* To compile: run "gcc sem1.c -lpthread"
* To execute: run "./a.out"
*/

// Declaring global variables
#define MAX_BUFFER_SIZE 20
int buffer[MAX_BUFFER_SIZE];
int fillIndex = 0;
int useIndex = 0;
int i = 0;
// Declaring semaphores
sem_t full; //determines if buffer is full
sem_t empty; // determines if buffer is empty
sem_t mutex; //controls access to the buffer

//helper method: adds to the buffer
void put(int value){
	buffer[fillIndex] = value;
	fillIndex = (fillIndex + 1);
}
//helper method: gets value from the buffer
int get(){
	int tmp = buffer[useIndex];
	useIndex = (useIndex + 1);
	return tmp;
}
//adds to the buffer using semaphores
void *producer(void *arg){
	sem_wait(&empty);
	//sem_wait(&mutex);
	put(i);
	//sem_post(&mutex);
	sem_post(&full);
	printf("Adding %d to buffer.\n", i);
	i++;

	
}
//takes from the buffer using semaphores
void *consumer(void *arg){

	sem_wait(&full);
	//sem_wait(&mutex);
	int tmp = get();
	//sem_post(&mutex);
	sem_post(&empty);
	printf("Taking %d from buffer.\n", tmp);
}

//driver method
int main(int argc, char *argv[]){
	pthread_t p1, p2, p3; //declare threads
	sem_init(&empty, 0, MAX_BUFFER_SIZE); //buffer is empty and holds MAX_BUFFER_SIZE
	sem_init(&full, 0, 0); //there is nothing in the buffer initially
	sem_init(&mutex, 0, 1); // mutex = 1 because only one at a time can hold the lock
	
	//create multiple threads


	printf("-----Creating threads %d-----\n", i);
	pthread_create(&p1, NULL, producer, "Producer"); //create producer thread
	sleep(1);
	pthread_create(&p2, NULL, producer, "Producer 2"); //create consumer thread
	pthread_create(&p3, NULL, consumer, "consumer");
	pthread_join(p1, NULL); 
	pthread_join(p2, NULL);
	pthread_join(p3, NULL);
	printf("\n");

	printf("\n");
	printf("-----Results-----\n");
	printf("Producer total: %d\n", fillIndex);
	printf("Consumer total: %d\n", useIndex);
		
	for (int j = 0; j < sizeof(buffer)/sizeof(int); j++){
		printf("Buffer at index %d is %d\n", j, buffer[j]);
	}
	//house keeping
	sem_destroy(&empty);
	sem_destroy(&full);
	sem_destroy(&mutex);
	return 0;
	
}

