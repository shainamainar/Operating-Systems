#include "PCB.h"
#include<stddef.h>

// process - Pointer to a PCB
// post-condition: assigns all attributes to have value 0.
void initProcess(PCB* process){

	process->pid = 0;
	process->totalTime = 0;
	process->remainingTime = 0;

}

// post-condion: assigned PCB totalTime to given totalRunTime and
// remainingTime to same value, assigns pid value
void initProcessValues(PCB* process, int pid, int totalRunTime){
	process->pid = pid;
	process->totalTime = totalRunTime;
	process->remainingTime = totalRunTime;
}

// process - Pointer to a PCB
// runTime - Number of seconds to run this process on CPU
// post-condition: Decrease process remainingTime by 
// runTime only if runTime is >= remainingTime; else,
// decrease process remainingTime by remainingTime (zero it out),
// if remainingTime < runTime
// Return number of units of time actually run by the given process.
int runProcess(PCB* process, int runTime){
	if(process != NULL){
		if(runTime <(*process).remainingTime){
			(*process).remainingTime -= runTime;
		}
	}
}
