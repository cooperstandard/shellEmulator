//Project 2 minishell
//Cooper Standard and Henry Jaffray
//Start Structures
//End Structures




//Start Prototypes
void parseArgs(char *buffer, char** args, int argsSize, int *nargs); //bad
void tokenize(); //this is going to be the rewritten version of ^
int executeProg(char* name, char** args);
int executeProgBackground(char* name, char** args);

//End Prototypes