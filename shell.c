//imported libraries
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#define clear() printf("\033[H\033[J")
#define BUFFER_SIZE 1024
#define TOK_BUFF 64
#define TOK_DELIM " \t\r\n\a"





char **sh_tok(char *line){
    int buffer_size = TOK_BUFF;
    int pos = 0;
    char **tokens = malloc(buffer_size * sizeof(char*));
    char *token;
    
    if(!tokens){
        fprintf(stderr, "sh: allocation error\n");
        exit(EXIT_FAILURE);

    }
    token = strtok(line, TOK_DELIM);
    while(token != NULL){
       tokens[pos] = token;
       pos++;
       if(pos >= buffer_size){
           buffer_size += TOK_BUFF;
           tokens = realloc(tokens, buffer_size * sizeof(char*));
           if(!tokens){
               fprintf(stderr, "sh: allocation error\n");
               exit(EXIT_FAILURE);
           }       

       } 
       token = strtok(NULL, TOK_DELIM);
       
    }
    tokens[pos] = NULL;
    return tokens;

}

void sh(void){
    char *line;
    char **args;
    int status;

    do{
        printf("> ");
        line = NULL;
        ssize_t buffer_size = 0;
        getline(&line, &buffer_size, stdin);
        args = sh_tok(line);
        status = sh_execute(args);

        free(line);
        free(args);
        
    } while(status);

}



int main(int argc, char **argv){
    sh();
    return EXIT_SUCCESS;
}
