#include <stdio.h>   // printf, sprintf, perror
#include <stdlib.h>  // strtol, getenv
#include <unistd.h>  // getcwd
#include <string.h>  // strcmp
#include <pthread.h>
#include <stdbool.h>

#include <readline/readline.h> // readline
#include <readline/history.h>  // add_history

#include "tree.h"    // Execution tree
#include "common.h"  // printWelcome
#include "parse.h"   // parse
#include "execute.h" // execute
#include "chalk.h"   // color constants

int main (void)
{
    printWelcome();

    char *line;      // Stores the user's current entered line
    char *argv[64];  // Stores the current line split into args  
    
    char cwd[1024];  // Stores the current workind directory
    char promptMessage[1024]; // Stores the entire prompt line

    // Main prompt loop
    while (1)
    {
        // fprintf(stderr, "\nGET NEW INPUT\n");

        // Get Current Working Directory
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            // Get current user
            char *user = getenv("USER");
            if(user == NULL) 
            {
                exit(1);
            }

            // Prompt User for input
            sprintf(promptMessage, 
                    "%s%s%s@%s%s%s%s", 
                    KRED, user, KNORMAL, 
                    KBLUE, cwd, KNORMAL, 
                    "$ ");
            line = readline(promptMessage);

            // fprintf(stderr, "\nLINE: %s\n", line);

            if (line == NULL)
            {
                perror("READLINE ERROR!");
                exit(1);
            }

            // Add the line to history
            if (line[0]!=0)
            {
                add_history(line);
            }

            // Parse the current line and store in argv
            //printf("Line: %s\n", line);
            parse(line, argv); /* parse the line */

            // int i;
            // for (i=0; i<40; i++)
            // {
            //     fprintf(stderr, "Argv: %i %s\n", i, argv[i]);
            // }

            //TODO Either in parse.c or a new file/header altogether(uses argv)
            //     check for ~ and replace with home directory -> getenv("HOME");

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
