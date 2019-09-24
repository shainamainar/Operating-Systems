


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{

  char *str = argv[1];



  unsigned int *p = malloc(sizeof(unsigned int));



  printf("PID %d says address of p is 0x%08x\n", getpid(), (unsigned)p);
  *p = 0;
 


 


  while(1)
  {


    printf("PID %d says value p is %u\n", getpid(), *p);
    *p = *p +1;


 

    sleep(3);
  }
  return 0;
}
