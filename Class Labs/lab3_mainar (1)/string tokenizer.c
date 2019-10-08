// The tokenizer breaks up a string using blank or white spaces. 

#include <stdio.h>
#include <malloc.h>
#include <string.h>

int main(void)
{
    char* message = strdup("Hello World!!!");
    printf("%s\n", message);
    // malloc returns a void *, which is a pointer to any thing.  Since we will use the memory as a string, we
    // must typecast to the char * type.

    // The notation (char *) means to typecast the void * to a char *
    char* buffer = (char *) malloc(sizeof(char) * strlen(message));
    printf("%s\n", buffer);
    char* tok = strtok(message, " ");
    // Copy message into buffer.
    strcpy(buffer, message);
    while (tok!=NULL){

       printf("%s\n",tok);
       tok = strtok(NULL, " ");
    }

    return 0;
} 

