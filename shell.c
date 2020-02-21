//shell class
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"


int main(){
    int done = 0;
    while (!done) { //program run loop, need to set up exit commands until then use keyboard interrupt to exit

        int count = 1;
        char* cwd = (char*) malloc(count * sizeof(char));
        while(getcwd(cwd, count) == NULL){
            count++;
            free(cwd);
            cwd = (char*) malloc(count * sizeof(char));
        }

        printf("%s> ", cwd);
        int length = (count * 2) + 32; //this is arbitratry but I dont think it needs to be any bigger. If steve says otherwise can change
        char* input = (char*) malloc(length * sizeof(char));
        fgets(input, length + 1, stdin); //array is now formatted like "what was typed but always terminated with \n" followed by \0 until the array is full
        //printf("%s", input); // this just prints out what ^ read. once commands are working only print this if the input doesnt match a command
        int* nTokens;
        int maxTokens = 5; //maximum number of tokens (i.e. "mv -v ~ /" is 4 tokens"). five is probably enough but we can adjust if needed
        char* tokens[maxTokens];
        parseArgs(input, tokens, maxTokens, nTokens);
        printf("%s", tokens[0]);
        

    }
    
}






void parseArgs(char *buffer, char** args, int argsSize, int *nargs) { //this is the code from the assignment, rewrite for extra credit
// buffer is the input string of characters
// args is the output array of arguments.  It has already been created with argsSize slots.
// nargs as the number filled in that is passed back
    char *bufArgs[argsSize];
    char **cp;
    char *wbuf;
    int i, j;

    wbuf=buffer; 
    bufArgs[0]=buffer;
    args[0]=buffer;

    for(cp=bufArgs; (*cp=strsep(&wbuf, " \n\t")) != NULL ;){ //this is disgusting
        if ((*cp != '\0') && (++cp >= &bufArgs[argsSize]))
            break;
    }

    for (j=i=0; bufArgs[i]!=NULL; i++){
        if(strlen(bufArgs[i])>0)
            args[j++]=bufArgs[i];
    }

    // Add the NULL as the end argument because we need that for later
    *nargs=j;
    args[j]=NULL;
}


void tokenize(){ // put the rewritten version of parseArgs here


}