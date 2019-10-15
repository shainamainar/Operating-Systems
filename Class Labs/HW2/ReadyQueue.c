//readyQ.c
//implementation of readyq functions

#include "ReadyQueue.h"
#include<stdio.h>
#include"stdbool.h"
int numProcesses;

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
int size(ReadyQueue* Q){
	return Q->numProcesses;
}


// Q - pointer to a ReadyQueue assume to be initialized
// process - pointer to a PCB
// post-condition: if Q is not full, then insert process
// into next open processList array slot, increment
// numProcesses, and return true; else, return false.
bool insert(ReadyQueue* Q, PCB* process){
  // if pointers are not NULL and Q is not full then...
  if (Q != NULL && process != NULL && !isFull(Q) )
  {
    // Know Q is not full
    // Copy values from given process into array slot's PCB
    Q->processList[Q->numProcesses] = *process;
    Q->numProcesses++;
    // Assume #define TRUE  1 has been done somewhere
    return true;
  }
  else
    return false;
}

// Q - pointer to a ReadyQueue
// post-condition: Sorts contents of queue into
// increasing order of remainingTime.  PCB with lowest
// remainingTime will occupy list slot index 0.

void sort(ReadyQueue* Q){
 // ? Somepoint print message saying process exited

  if(Q->numProcesses > 1)
  {
    // Loop to copy shift second element into first slot,
    // third element into second slot, ...
    for(int i = 0; i < (Q->numProcesses-1); i++)
       Q->processList[i] = Q->processList[i+1];
  }

  if(!isEmpty(Q))
    // decrement numProcesses by 1
    Q->numProcesses--;
}


// Q - pointer to a ReadyQueue
// post-condition: prints out information for each PCB in the queue.
void print(ReadyQueue* Q){
	for(int i = 0; i < Q->numProcesses; i++){
		
		printf("PID: %d, Total time: %d, Remaining Time: %d", Q->processList[i].pid, Q->processList[i].totalTime, Q->processList[i].remainingTime);
	}
}


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


//Q - pointer to a ReadyQueue
//post -con: if Q is not empty, then call runProcess fucntion on first PCB in the queue
//Run first process in Q to completion. Shift all remaining PCBs one array slot forward
//so second is now first
int runFCFS(ReadyQueue* Q){
	int timeRun;
   if(!isEmpty(Q))
   {
      // Get pointer to first process in Q
      PCB* process = &( Q->processList[0] );
		
			
      // FCFS - assume process runs to completion
      int timeRun = runProcess(process, process->remainingTime);
	  Q->time = Q->time + timeRun;
       // Print message indicating when a process runs
       // Example:
       // TIME 0   PID 1    RUNS FOR   2
			 // Use globalTime to show current time

      // If process has <= 0 remainingTime ten remove completed front of Q process and
		   // Print message if process completes
       // TIME 2   PID 1    COMPLETE
      // printf("Time %d Completed PID %d\n", Q->time, process->pid);
			
   }
   return Q->time;
}

// Q - pointer to a ReadyQueue
// post-condition: if Q is not empty, then call sort to arrange the
// Q in ascending order of time time remaining to complete.
// Run first process in Q to completion.  Shift all remaining
// PCBs one array slot forward so second is now first.
// Return number of units of time that first process ran
int runSRTF(ReadyQueue* Q){
	int timeRun;
	if(!isEmpty(Q)){
		sort(Q);
		PCB* process = &(Q->processList[0]);
		timeRun = runProcess(process, process->remainingTime);
		Q->time += timeRun;
		removeFrontPCB(Q);
	}
	return Q->time;
}

// Q - pointer to a ReadyQueue
// post-condition: if Q is not empty, then call runProcess function
// on first PCB in the queue.  After running the process, move it
// to the rear of the Q
// Return number of units of time that first process ran
int runRoundRobin(ReadyQueue* Q, int timeSlice){
	int timeRun;
	if(!isEmpty(Q)){
		PCB* process = &(Q->processList[0]);
		timeRun = runProcess(process, timeSlice);
		removeFrontPCB(Q);
		insert(Q, process);
		Q->time += timeRun;
	}
	return Q->time;

}
