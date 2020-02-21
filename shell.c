//shell class
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shell.h"
#include <unistd.h>

int main(){

int count = 2;
char* cArray = (char*) malloc(count *sizeof(char));

 while(cArray == NULL){
     cArray = getcwd(cArray, sizeof(cArray));
     count++;
     free(cArray);
     cArray = (char*) malloc(count *sizeof(char));
 }

printf("%s> \n", cArray);

}


