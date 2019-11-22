#include<stdio.h>
#include<assert.h>
#include<pthread.h>
#include<semaphore.h>

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
	fillIndex = (fillIndex + 1) % MAX_BUFFER_SIZE;
}
//helper method: gets value from the buffer
int get(){
	int tmp = buffer[useIndex];
	useIndex = (useIndex + 1) % MAX_BUFFER_SIZE;
	return tmp;
}
//adds to the buffer using semaphores
void *producer(void *arg){
	int i;
	for (i = 0; i < loops; i++){
		Sem_wait(&empty);
		Sem_wait(&wait);
		put(i);
		Sem_post(&mutex);
		Sem_post(&full);
	}
	
}
//takes from the buffer using semaphores
void *consumer(void *args){
	int i;
	for(i = 0; i < loops; i++){
		Sem_wait(&full);
		Sem_wait(&mutex);
		int tmp = get();
		Sem_post(&mutex);
		Sem_post(&empty);
		printf("%d\n", tmp);
	}
}

//driver method
int main(int argc, char *argv[]){
	Sem_init(&empty, 0, MAX_BUFFER_SIZE); //buffer is empty and holds MAX_BUFFER_SIZE
	Sem_init(&full, 0, 0); //there is nothing in the buffer initially
	Sem_init(&mutex, 0, 1); // mutex = 1 because only one at a time can hold the lock
	
	pthread_t p1, p2;
	printf("Creating thread...");
	Pthread_create(&p1, NULL, producer, "Producer");
	Pthread_create(&p2, NULL, consumer, "Consumer");
	Pthread_join(p1, NULL);
	Pthread_join(p2, NULL);
	printf("Both threads finished.");
	return 0;
	
}

