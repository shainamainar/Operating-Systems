#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  printf("Hello world PID%d\n", (int)getpid());
  int rc = fork();
  if(rc < 0)
  {
    fprintf(stderr, "fork failed\n");
    exit(1);
  }
  else if(rc == 0)
  { 
    printf("Hello, I am child PID%d\n", (int)getpid());
  }
  else
  {
    printf("Hello, I PID%d am parent of child PID%d\n",
        (int)getpid(), rc);
  }
  return 0;
}
