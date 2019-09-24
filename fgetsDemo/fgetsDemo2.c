// Extends fgetsDemo1 to look more like a simple shell that can enter 
// one command after another.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an integer constant for the C preprocessor.
// The preprocessor will substitute the text ARGLEN for the literal 100
#define ARGLEN 100

int main()
{
  // static allocation of an array of char values.
  char  argBuf[ARGLEN];
  
  printf("Enter an argument for a command: ");
	
	// Continue prompting and entering arguments until the user presses ENTER.
  while(fgets(argBuf, ARGLEN, stdin) && *argBuf != '\n')
  {
    printf("You entered argument: %s\n", argBuf);

    printf("Enter an argument for a command: ");
  }

  printf("You entered nothing.  Goodbye.\n");

  // Exit condition normal - value 0.
  exit(0);
}
