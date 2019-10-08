#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// Demonstrates how a parent process can wait for its child to complete.
// Child will always output first since the parent waits after the fork.
// Take away the parent wait call, then the OS will arbitrarily choose
// whether child or parent runs next.  The wait call forces the issue sopen
// the parent always yields after it calls fork.
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
  }
  else // rc indicates this code is running in the parent process
  {
		// block until any of my child processes complete.
		// return value will be the PID of first child to complete.
    int wc = wait(NULL);
    printf("Hello, I PID %d am parent of child PID %d\n",
        (int)getpid(), wc);
  }
  return 0;
}
