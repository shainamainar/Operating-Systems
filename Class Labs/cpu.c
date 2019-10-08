

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{

  char *str = argv[1];
  while(1)
  {
    printf("%s\n", str);
    sleep(1);
  }
  return 0;
}
