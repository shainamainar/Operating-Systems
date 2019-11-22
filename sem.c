#include<stdio.h>
#include<assert.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

// Declaring global variables
#define MAX_BUFFER_SIZE 10
int buffer[MAX_BUFFER_SIZE];
int fillIndex = 0;
int useIndex = 0;

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
	int i;
	for (i = 0; i < MAX_BUFFER_SIZE; i++){
		sem_wait(&empty);
		sem_wait(&mutex);
		put(i);
		sem_post(&mutex);
		sem_post(&full);
		printf("Adding %d to buffer.\n", i);
	}
	
}
//takes from the buffer using semaphores
void *consumer(void *args){
	int i;
	for(i = 0; i < MAX_BUFFER_SIZE; i++){
		sem_wait(&full);
		sem_wait(&mutex);
		int tmp = get();
		sem_post(&mutex);
		sem_post(&empty);
		printf("Taking %d from buffer.\n", tmp);
	}
}

//driver method
int main(int argc, char *argv[]){
	sem_init(&empty, 0, MAX_BUFFER_SIZE); //buffer is empty and holds MAX_BUFFER_SIZE
	sem_init(&full, 0, 0); //there is nothing in the buffer initially
	sem_init(&mutex, 0, 1); // mutex = 1 because only one at a time can hold the lock
	
	pthread_t p1, p2;
	printf("-----Creating threads-----\n");
	pthread_create(&p1, NULL, producer, "Producer");
	sleep(2);
	pthread_create(&p2, NULL, consumer, "Consumer");
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	sem_destroy(&empty);
	sem_destroy(&full);
	sem_destroy(&mutex);
	printf("-----Both threads finished.-----\n");
	printf("Producer total: %d\n", fillIndex);
	printf("Consumer total: %d\n", useIndex);
	/*for (int i = 0; i < MAX_BUFFER_SIZE; i++){
		printf("Value at index %d: %d\n", i, buffer[i]);
	}*/
	return 0;
	
}

