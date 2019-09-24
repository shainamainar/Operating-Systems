#include <stdio.h>
#include <malloc.h>
#include <string.h>

int main(void)
{
    char buffer[15]; // static allocated array of characters.  It is called static allocation since at compile-time, we know the size to allocate.
    // We must include one extra character for the end of string terminator '\0'

    // Copy message into buffer.
    strcpy(buffer, "Hello World!!!");  //<---------

    printf("%s\n", buffer);

    return 0;
}


