#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>



// Simple Shell Program
#define PROMPT "shell$ "
#define MAX_COMMANDLINE_SIZE 2048
#define MAX_TOKENS 100

// tokenize each commandline arg into seperate tokens
// put these tokens in a different args array
// in the same order in which they are received
char **parse_commandline(char *commandLine, char **args, int *args_count)
{
   char *token;
// dont forget to dereference since arg_counts came in as a pointer
   *args_count = 0;
   token = strtok(commandLine, " \t\n\r");

   while(token != NULL){
    // put the token in the args array
    args[*args_count] = token;
    (*args_count)++;
    token = strtok(NULL, " \t\n\r");
   }
 //   add NULL to the end of args array to indicate there are no more args
    args[*args_count] = NULL;
    return args;
}


int main(void)
{
    // a shell receives command line args from user
    // init a char buffer to hold cmd line args
    char commandLine[MAX_COMMANDLINE_SIZE];
    char *args[MAX_TOKENS];
    int args_count;


    //our shell is loop infiinteily until told to exit
    while(1){
        // print the prompt
        printf("%s", PROMPT);
        // get input from the keyboard fromt he standard input stream
        fgets(commandLine, sizeof(commandLine), stdin);
        // be able to exit the shell
        // to do that let's check for end of file (CTRL+D)
        if(feof(stdin)){
            break;
        }
        // handling parsing the command line args
        parse_commandline(commandLine, args, &args_count);

        for(int i = 0; i <args_count; i++){
            printf("%s\n", args[i]);
        }
         printf("%d\n", args_count);
        //  check if user didnt give any commands:
        if(args_count == 0){
            continue;
        }
        // allow user to exit by typing exit
        if(strcmp(args[0], "exit") ==0){
            break;
        }
        // check if user wants to change directories
        if(strcmp(args[0], "cd") == 0){
            if(chdir(args[1]) < 0){
                fprintf(stderr, "chdir failed\n");
                continue;
            }
            // successfully changed directories
            // wait for next command
            continue;
        }
        // be able to execute arbitrary programs like ls
        // use fork and exec in combination
        pid_t pid = fork();
        if(pid < 0){
            fprintf(stderr, "fork failed \n");
        }
        // child is going to ahead and transform into the specified program
        if(pid == 0){
            // call exec to transform into the specified program
            execvp(args[0], args);
            // exec error check
            fprintf(stderr, "exec failed\n");
            exit(1);
        }else{
            // parent wait son child to finish executing
            waitpid(pid, NULL, 0);
        }
    }

    // we're probably going to need to parse those args
    // shells need to print a prompt
    // we should be able to exit a shell using CTRL+D
    // should be able cd into specified directories
    // will need to fork off child processes to exectue files 
    // should be able to execute arbitrary files (we can use exec for this)
    

    return 0;
}