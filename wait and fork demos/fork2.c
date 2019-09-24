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
  }
  else
  {
    int wc = wait(NULL);
    printf("Hello, I PID %d am parent of child PID %d\n",
        (int)getpid(), wc);
  }
  return 0;
}
