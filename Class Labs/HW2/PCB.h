#if !defined(PCB_HDR)
#define PCB_HDR

typedef struct {
  int pid;
  int totalTime;
  int remainingTime;
} PCB;

// process - Pointer to a PCB
// post-condition: assigns all attributes to have value 0.
void initProcess(PCB* process);

// post-condion: assigned PCB totalTime to given totalRunTime and
// remainingTime to same value, assigns pid value
void initProcessValues(PCB* process, int pid, int totalRunTime);

// process - Pointer to a PCB
// runTime - Number of seconds to run this process on CPU
// post-condition: Decrease process remainingTime by 
// runTime only if runTime is >= remainingTime; else,
// decrease process remainingTime by remainingTime (zero it out),
// if remainingTime < runTime
// Return number of units of time actually run by the given process.
int runProcess(PCB* process, int runTime);

#endif

