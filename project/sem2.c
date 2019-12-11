#include<stdio.h>
#include<assert.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

/*
* To compile: run "gcc sem2.c -lpthread"
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
	sem_wait(&mutex);
	sem_wait(&empty);
	put(i);
	sem_post(&full);
	sem_post(&mutex);
	printf("Adding %d to buffer.\n", i);
	i++;

	
}
//takes from the buffer using semaphores
void *consumer(void *arg){

	sem_wait(&mutex);
	sem_wait(&full);
	int tmp = get();
	sem_post(&empty);
	sem_post(&mutex);
	printf("Taking %d from buffer.\n", tmp);
}

//driver method
int main(int argc, char *argv[]){
	pthread_t p1, p2; //declare threads
	sem_init(&empty, 0, MAX_BUFFER_SIZE); //buffer is empty and holds MAX_BUFFER_SIZE
	sem_init(&full, 0, 0); //there is nothing in the buffer initially
	sem_init(&mutex, 0, 1); // mutex = 1 because only one at a time can hold the lock
	
	//create multiple threads
	for(int i = 0; i < MAX_BUFFER_SIZE; i++){
		printf("-----Creating threads %d-----\n", i);
		pthread_create(&p1, NULL, producer, "Producer"); //create producer thread
		pthread_create(&p2, NULL, consumer, "Consumer"); //create consumer thread
		pthread_join(p1, NULL); 
		pthread_join(p2, NULL);
		printf("\n");
	}
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

