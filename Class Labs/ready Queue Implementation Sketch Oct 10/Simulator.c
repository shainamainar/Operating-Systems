// Simulator.c
// Main to run an OS CPU schedule simulator
// Example 1 - FCFS
//#include any headers needed
//
//PCB ReadyQueue modules

#include "PCB.h"
#include "ReadyQueue.h"
#include <stdio.h>

void main(){
	//Declare and init a PCB
	// Example: PID 1, total run time 10
	//not a pointer
	PCB a;
	initProcessValues(&a, 1, 10);
	// Confirm init - print PID 1 TimeRemaining 10
	//would be a->pid if PCB* a
	printf("PID %d TimeLeft %d\n", a.pid, a.remainingTime);
	
	//initialize readyQueue insert PCB
	ReadyQueue Q;
	//init to empty
	//pass by ref because we want to change the actual ReadyQueue
	empty(&Q);
	//Test isEmpty(), isFull, size
	printf("Q is empty: %d\n", isEmpty(&Q));
	printf("Q is full: %d\n", isFull(&Q));
	printf("Q size: %d\n", size(&Q));
	//insert process A into Q
	
	printf("Is sucessful: %d\n", insert(&Q, &a));
	print(&Q);
	
	runFCFS(&Q);
	
}
