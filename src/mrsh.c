#include <stdio.h>   // printf, sprintf, perror
#include <stdlib.h>  // strtol, getenv
#include <unistd.h>  // getcwd
#include <string.h>  // strcmp
#include <pthread.h>

#include <readline/readline.h> // readline
#include <readline/history.h>  // add_history

//
#include "common.h"  // printWelcome
#include "parse.h"   // parse
#include "execute.h" // execute
#include "chalk.h"   // color constants

// === Structs ===
// struct commandArgs {
//     int argc;
//     //const char **argv;
//     char *argv[64];
// };

int main (void)
{

    printWelcome();

    char *line;
    char *argv[64];              /* the command line argument      */
    // struct commandArgs cmd;
    // pthread_t run_thread;
    char cwd[1024];
    char promptMessage[1024];

    while (1)
    {
        // Get Current Working Directory
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            // Get current user
            char *user = getenv("USER");
            if(user == NULL) 
            {
                exit(1);
            }

            // Prompt User
            sprintf(promptMessage, 
                    "%s%s%s@%s%s%s%s", 
                    KRED, user, KNORMAL, 
                    KBLUE, cwd, KNORMAL, 
                    "$ ");
            line = readline(promptMessage);

            if (line == NULL)
            {
                perror("READLINE ERROR!");
                exit(1);
            }

            // Add the line to history
            if (line[0]!=0) {
                add_history(line);
            }

            //printf("Line: %s\n", line);
            parse(line, argv);       /*   parse the line              */
            //printf("Argv: %s\n", argv[0]);

            // If no parameters restart loop
            if (argv[0] == NULL)
            {
                //printf("Please enter a valid command.\n");
                continue;
            }
            else if (strcmp(line, "exit") == 0 || strcmp(line, "quit") == 0) 
            {
                // If user wishes to exit mrsh break out of loop
                break;
            }
            else // Else execute command
            {
                execute(argv);
            }
        }
        else
        {
            perror("Error: Couldn't get the current directory, weird.");
            exit(1);
        }
    }

    printf("\nMrShell piping out!\n");

    return 0;
}
