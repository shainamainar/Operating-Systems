//imported libraries
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h>
#include <stdbool.h>

#define BUFFER_SIZE 64
#define MAX_CMD 10


int main(){
  char argBuf[BUFFER_SIZE];
  char* argv[100]; //user arg
  int argc; //arg count
    int i = 0;

    printf(">");
    while(fgets(argBuf, BUFFER_SIZE, stdin)){
      char *token;
      token = strtok(argBuf, " ");
      
      while(token != NULL && (strcmp(token, "exit\n") != 0)){
        argv[i] = token;
        token = strtok(NULL, " ");
        i++;
      }

    }
    argv[i] = NULL;
    argc = i;
    for(i = 0; i < argc; i++){
      printf("%s\n", argv[i]);
    }
  int pid = fork();
  
  
 
}


