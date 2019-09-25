//
//  shell.c
//  Shaina Mae Mainar
//
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


int main(){
  char argBuf[BUFFER_SIZE]; // initial input
  printf(">");
  bool back = false;
    
  while((fgets(argBuf, BUFFER_SIZE, stdin)) && *argBuf != '\n'){
    // remove new line character
    argBuf[strcspn(argBuf, "\n")] = 0;
    int i = 0;
    char* argv[10]; //user arg
    if(strcmp(argBuf, "exit") == 0) exit(0);
    char *token; //individual tokens
    token = strtok(argBuf, " ");
	//add tokens to arguments array
    while(token != NULL){
      argv[i] = token;
      token = strtok(NULL, " ");
      i++;
    } 
	//removing new line characters so execvp doesnt break
    if (argBuf[strlen(argBuf)-1] == '\n')
    argBuf[strlen(argBuf)-1] = '\0';
	//background process
    if(strcmp(argv[i-1], "&") == 0){
      argv[--i] = NULL;
      back = true;
    }
    //fork child
    printf("PID is: %d\n", getpid());
    pid_t pid = fork();
    int status;
	//fork method fails
    if(pid < 0){
      printf("fork fail\n");
      exit(1);
    }
	//child executes
    else if(pid == 0){
      execvp(argv[0], argv);
      perror("execvp fail\n");
      exit(0);
    }
	//parent waits for child
    else{
      while(wait(&status) != pid);
	  //dont wait for background process
      if(!(back)) wait(&status);
	  //remove date from arguments array before taking in new input
      memset(argv, 0, BUFFER_SIZE);
      //free(argv);
      printf(">");
    }
  }
}


