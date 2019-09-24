//imported libraries
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h>
#include <stdbool.h>

#define BUFFER_SIZE 64
#define MAX_CMD 10


void shell(){
  char in[BUFFER_SIZE];
  char *cmd[MAX_CMD]; 
  bool isBackground = false;
  int i = 0;
  printf(">");
  while(fgets(in, BUFFER_SIZE, stdin) && strcmp (in, "exit\n") != 0){
    char *tokens = strtok(in, " ");
    in[i] = tokens;
    i += 1;
    while(tokens != NULL){
      tokens = strtok (NULL, " ");
      in[i] = tokens;
    }
    if(strcmp(in[i-2], "&") == 0){
      in[i-2] = NULL;
      isBackground = true;
    }
  }
  
}

int main(){

  shell();
  return EXIT_SUCCESS;
}

