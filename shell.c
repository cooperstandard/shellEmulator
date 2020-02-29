//shell class
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "shell.h"


int main(){
    int done = 0;
    signal(SIGCHLD, SIG_IGN); //reap zombies automatically I think
    while (!done) { //program run loop, need to set up exit commands until then use keyboard interrupt to exit
        int count = 1;
        char* cwd = (char*) malloc(count * sizeof(char));
        while(getcwd(cwd, count) == NULL){
            count++;
            free(cwd);
            cwd = (char*) malloc(count * sizeof(char));
        }

        printf("%s> ", cwd);
        int length = (count * 2) + 32; //this is arbitratry but I dont think it needs to be any bigger. If steve says otherwise can change]
        char* input = (char*) malloc(length * sizeof(char));
        fgets(input, length + 1, stdin); //array is now formatted like "what was typed but always terminated with \n" followed by \0 until the array is full
        //printf("%s", input); // this just prints out what ^ read. once commands are working only print this if the input doesnt match a command
        int maxTokens = 5; //maximum number of tokens (i.e. "mv -v ~ /" is 4 tokens"). five is probably enough but we can adjust if needed
        char** tokens = (char**) malloc((maxTokens)*sizeof(char*));
        int nTokens = 1;
        
        for(int i = 0; i < maxTokens; i++) {
            tokens[i] = (char*)malloc(64*sizeof(char));
        }

        int background;
        parseArgs(input, tokens, maxTokens, &nTokens);
        if (strcmp(tokens[nTokens - 1], "&\0") == 0) {
            background = 1;
            nTokens--; //don't want to pass the & as an arguement
        } else  {
            background = 0;
        }
        //printf("%s", tokens[0]);


        if (strcmp(tokens[0],"exit\0") == 0) {
            exit(0);
        } else if (strcmp(tokens[0], "cd\0") == 0) {
            if(chdir(tokens[1])!= 0) {
                printf("'%s' is not a valid directory \n", tokens[1]);
            } 
        } else if (!background) {
             executeProg(tokens[0], tokens);
        } else {
            executeProgBackground(tokens[0], tokens);
        }
        //free all malloced things that we dont want to persist
    }   
}

int executeProg(char* name, char** args){
    int status;
    int pid = fork();
    int rc;

    if(pid!= 0){ //parent
        
        while(wait(&status) != pid);
        //pid_t result =  waitpid(pid, &status, 0); //blocking
        //kill(pid, 3);
       // sleep(10);
    } else {  //child
       
        args[0] = name;
        rc =  execvp(args[0], args);
        kill(pid, SIGINT);
    }
    return rc;
}

void executeProgBackground(char* name, char** args){
    int status;
    int pid = fork();
    

    if(pid!= 0){ //parent
        //while(wait(&status) != pid);
        //waitpid(pid, &status, WNOHANG);

        //sleep(10);

    } else {  //child
        execvp(args[0], args);
        //exit(0);
    }
}




// buffer is the input string of characters
// args is the output array of arguments.  It has already been created with argsSize slots.
// nargs as the number filled in that is passed back
void parseArgs(char *buffer, char** args, int argsSize, int *nargs) {
  char *bufArgs[argsSize];
  char **cp;
  char *wbuf;
  int i, j;

  wbuf=buffer;
  bufArgs[0]=buffer;
  args[0]=buffer;

  for(cp=bufArgs; (*cp=strsep(&wbuf, " \n\t")) != NULL ;){
    if ((*cp != '\0') && (++cp >= &bufArgs[argsSize]))
      break;
  }

  for (j=i=0; bufArgs[i]!=NULL; i++){
    if(strlen(bufArgs[i])>0)
      strcpy(args[j++],bufArgs[i]);
  }

  // Add the NULL as the end argument because we need that for later
  *nargs=j;
  args[j]=NULL;
}


void tokenize(char *input, char** tokens, int maxTokens, int *nTokens){ // put the rewritten version of parseArgs here


}

void childHandler(pid_t pid) {


}

