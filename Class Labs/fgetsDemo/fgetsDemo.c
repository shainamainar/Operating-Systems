// Example of using fgets to read a string from keyboard input.
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
	// Call fgets
	// First argument - the array to receive the input string
	// Second argument - maximum number of characters argBuf can hold without overflow.
	// Third argument - input source, stdin represents the keyboard.
	// If you press ENTER without entering anything, the result is only the newline character.
  if(fgets(argBuf, ARGLEN, stdin) && *argBuf != '\n')
    printf("You entered argument: %s\n", argBuf);
  else
    printf("You entered nothing.  Goodbye.\n");

  // Exit condition normal - value 0.
  exit(0);
}
