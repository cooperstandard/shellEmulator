//Project 2 minishell
//Cooper Standard and Henry Jaffray
//Start Structures
//End Structures




//Start Prototypes
void parseArgs(char *buffer, char** args, int argsSize, int *nargs); //bad
void tokenize(); //this is going to be the rewritten version of ^
int executeProg(char* name, char** args);
int inputRedirect(char*** args);
int outputRedirect(char*** args);
void executeProgBackground(char* name, char** args);
char** truncateN(char** input, int size, int n);
void childHandler(pid_t pid);

//End Prototypes