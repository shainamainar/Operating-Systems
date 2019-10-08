// waitdemo2.c from Understanding UNIX/LINUX Programming by Bruce Molay pages 269-270
// Demonstrates how to send an exit code value from completing child back to parent.
// The exit value is an integer, whose bits encode three important pieces of information:
// a) exit code value - A value of 0 denotes an error-free exit.
// b) signal value - ID number of the signal call that forced child to terminate
// c) core dump value - Information about the core dump when child caused a crash.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
  printf("Hello world PID %d\n", (int)getpid());
  int rc = fork();
  if(rc < 0)
  {
    fprintf(stderr, "fork failed\n");
    exit(1);
  }
  else if(rc == 0)
  { 
    printf("Hello, I am child PID %d\n", (int)getpid());
    sleep(3);
		// Communicate how I exited to my parent.
		// In UNIX convention, a non-zero value denotes an error.
    exit(17);
  }
  else // parent runs this code...
  {
		// Integer variable to receive status result code from exiting child.
    int childStatus;
    // wait returns the PID of the first completed child.
    int wc = wait(&childStatus);
    printf("Hello, I PID %d am parent of child PID %d\n",
        (int)getpid(), wc);

    // Let's decode the childStatus returned by the child's call to exit.
		// Shift bits 8 positions to the left (low-order end) to isolate the high-order 8-bits
    int high8 = childStatus >> 8;
		// Bitwise AND to clear out all bit values to 0 except the low-order 7 bits.
    int low7 = childStatus & 0x7F;
		// Bitwise AND to clear out all bit values to 0 except the 8th bit.
    int bit7 = childStatus & 0x80;
		// Print individual parts of unpacked child exit return value.
    printf("Child exitValue %d  signalValue %d  coreDumpValue %d\n",
        high8, low7, bit7);  
  }
  return 0;
}
