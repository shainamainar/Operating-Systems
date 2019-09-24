//imported libraries
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h>
#include <stdbool.h>

#define BUFFER_SIZE 32
#define MAX_CMD 10

//TODO: put everything in while
//TODO: implement background process

int main(){
  char argBuf[BUFFER_SIZE];
  char* argv[10]; //user arg
  int argc; //arg count
  int i = 0;
  printf(">");
    
  while((fgets(argBuf, BUFFER_SIZE, stdin)) && *argBuf != "\n"){
    if(strcmp(argBuf, "exit\n") == 0) exit(0);
    char *token;
    token = strtok(argBuf, " ");
    while(token != NULL){
       // printf("%s\n", token);
      argv[i] = token;
      token = strtok(NULL, " ");
      i++;
      if (argBuf[strlen(argBuf)-1] == '\n')
      argBuf[strlen(argBuf)-1] = '\0';
    } 
    argv[i] = NULL;
    argc = i;
    for(i = 0; i < argc; i++){
      printf("arg[%d] is ", i);
      printf("%s\n", argv[i]);
    }
    printf("PID is: %d\n", getpid());
    pid_t pid = fork();
    int status;
    if(pid < 0){
      printf("fork fail\n");
      exit(1);
    }
    else if(pid == 0){
      execvp(argv[0], argv);
      perror("execvp fail\n");
      exit(1);
    }
    else{
      while(wait(&status) != pid);
      //free(argv);
      printf(">");
    }
  }
}


