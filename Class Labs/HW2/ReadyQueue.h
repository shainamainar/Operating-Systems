#if !defined(READY_Q_HDR)
#define READY_Q_HDR

#include "PCB.h"
#define MAX_Q_LEN 100
#include<stdio.h>
#include"stdbool.h"

typedef struct {
  PCB processList[MAX_Q_LEN];
  int numProcesses; 
  int time;
} ReadyQueue;

// Q - pointer to a ReadyQueue
// post-conditon: sets numProcesses = 0
void empty(ReadyQueue* Q);

// Q - pointer to a ReadyQueue
// returns true if queue is empty - contains no processes; else, false.
bool isEmpty(ReadyQueue* Q);

// Q - pointer to a ReadyQueue
// returns true if queue is full - contains MAX_Q_LEN processes; else, false.
bool isFull(ReadyQueue* Q);

// Q - pointer to a ReadyQueue
// returns number of processes stored in the queue.
int size(ReadyQueue* Q);


// Q - pointer to a ReadyQueue
// process - pointer to a PCB
// post-condition: if Q is not full, then insert process
// into next open processList array slot, increment
// numProcesses, and return true; else, return false.
bool insert(ReadyQueue* Q, PCB* process);

// Q - pointer to a ReadyQueue
// post-condition: Sorts contents of queue into
// increasing order of remainingTime.  PCB with lowest
// remainingTime will occupy list slot index 0.
void sort(ReadyQueue* Q);

// Q - pointer to a ReadyQueue
// post-condition: prints out information for each PCB in the queue.
void print(ReadyQueue* Q);

// pre-condition: assume first PCB has completed.
// post-condition: shift all other PCB one slot to left
//                 decrement numProcesses by 1.
void removeFrontPCB(ReadyQueue* Q);

// Q - pointer to a ReadyQueue
// post-condition: if Q is not empty, then call runProcess function
// on first PCB in the queue.  
// Run first process in Q to completion.  Shift all remaining
// PCBs one array slot forward so second is now first.
// Return number of units of time that first process ran
int runFCFS(ReadyQueue* Q);

// Q - pointer to a ReadyQueue
// post-condition: if Q is not empty, then call sort to arrange the
// Q in ascending order of time time remaining to complete.
// Run first process in Q to completion.  Shift all remaining
// PCBs one array slot forward so second is now first.
// Return number of units of time that first process ran
int runSRTF(ReadyQueue* Q);

// Q - pointer to a ReadyQueue
// post-condition: if Q is not empty, then call runProcess function
// on first PCB in the queue.  After running the process, move it
// to the rear of the Q
// Return number of units of time that first process ran
int runRoundRobin(ReadyQueue* Q, int timeSlice);

#endif
