//readyQ.c
//implementation of readyq functions

#include "ReadyQueue.h"

// Q - pointer to a ReadyQueue
// post-conditon: sets numProcesses = 0
void empty(ReadyQueue* Q){
	Q->numProcesses = 0;
}

// Q - pointer to a ReadyQueue
// returns true if queue is empty - contains no processes; else, false.
bool isEmpty(ReadyQueue* Q){
	return Q->numProcesses == 0;

}

// Q - pointer to a ReadyQueue
// returns true if queue is full - contains MAX_Q_LEN processes; else, false.
bool isFull(ReadyQueue* Q){
	return Q->numProcesses >= MAX_Q_LEN;
}

// Q - pointer to a ReadyQueue
// returns number of processes stored in the queue.
//TODO: this one
int size(ReadyQueue* Q);


// Q - pointer to a ReadyQueue assume to be initialized
// process - pointer to a PCB
// post-condition: if Q is not full, then insert process
// into next open processList array slot, increment
// numProcesses, and return true; else, return false.
bool insert(ReadyQueue* Q, PCB* process){
	if (Q != NULL && !isFull(Q)){
		Q->processList[Q->numProcess] = *process; //need actual data not pointer. so dereferencing pointer
		Q->numProcess++;
		//assume #define TRUE 1 has been done
		return TRUE;
	}
	else
	return FALSE;
}

// Q - pointer to a ReadyQueue
// post-condition: Sorts contents of queue into
// increasing order of remainingTime.  PCB with lowest
// remainingTime will occupy list slot index 0.
//TODO
void sort(ReadyQueue* Q);

//TODO
// Q - pointer to a ReadyQueue
// post-condition: prints out information for each PCB in the queue.
void print(ReadyQueue* Q);


//pre-con: assume first PCB has completed and size of Q is > 1
//post-con: shift all other PCB one slot to left decrement numProcesses by 1
void removeFrontPCB(ReadyQueue* Q){
	if(Q->numProcesses > 1){
		//loop to copy shift second element into first slot,
		//third element into second slot, ...
		for(int i=0; i < (Q->numProcesses - 1); i++){
			Q->processList[i] = Q->processList[i+1];
		}
	}
	//decrement numProcesses by 1
	if(!isEmpty(Q))
	Q->numProcesses--;
}

//TODO
//Q - pointer to a ReadyQueue
//post -con: if Q is not empty, then call runProcess fucntion on first PCB in the queue
//Run first process in Q to completion. Shift all remaining PCBs one array slot forward
//so second is now first
void runFCFS(ReadyQueue* Q){
	if(!isEmpty(Q)){
		PCB* process = &(Q->processList[0]);
		runProcess(process, process->remainingTime);
		
		//Completed process, so print message
		//remove completed front of queue message
		printf("process completed");
		removeFrontPCB(Q);
	}
}
