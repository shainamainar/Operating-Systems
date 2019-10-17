//imported libraries
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h>
#include <stdbool.h>
#include<sys/wait.h>
#include<sys/types.h>

#define BUFFER_SIZE 32
#define MAX_CMD 10

//TODO: copy output to file

int main(){
  char argBuf[BUFFER_SIZE];
  printf(">");
  
    
  while((fgets(argBuf, BUFFER_SIZE, stdin)) && *argBuf != '\n'){
    bool back = false;
    int i = 0;
    char* argv[MAX_CMD]; //user arg
    char *token;
    token = strtok(argBuf, " \n");
    while(token != NULL){
      argv[i] = token;
      //printf("%s\n", argv[i]);
      token = strtok(NULL, " \n");
      i++;
    } 
    argv[i] = NULL;
    //printf("%s\n", argv[i-1]);
    if(strcmp(argv[i-1], "&") == 0){
      argv[--i] = NULL;
      back = true;
    }
    if(strcmp(argv[i-1], "exit") == 0) exit(1);
    
    pid_t pid = fork();
    //printf("PID is: %d\n", getpid());
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
      if(back == false) wait(&pid);
      printf(">");
      memset(argv, 0, BUFFER_SIZE);
      //free(argv);
      
    }
   
  }
}


