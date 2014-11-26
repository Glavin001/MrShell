#include <stdio.h>   // printf, sprintf, perror
#include <stdlib.h>  // strtol, getenv
#include <unistd.h>  // getcwd
#include <string.h>  // strcmp
#include <pthread.h>
#include <stdbool.h> // bool

#include <readline/readline.h> // readline
#include <readline/history.h>  // add_history

#include "tree.h"      // Execution tree
#include "common.h"    // printWelcome
#include "parse.h"     // parse
#include "execute.h"   // execute
#include "chalk.h"     // color constants
#include "constants.h" // constants
#include "tilde.h"     // homefinder

int main (void)
{
    printWelcome();

    char *line;                                 // Stores the user's current entered line
    char *argv[ARGV_LENGTH];                    // Stores the current line split into args   
    char cwd[CWD_LENGTH];                       // Stores the current workind directory
    char promptMessage[PROMPT_MESSAGE_LENGTH];  // Stores the entire prompt line

    // Main prompt loop
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

            // Check for home directory in cwd, replace with ~
            homeReplacer(cwd);

            // Check for git repo & prompt for input
            char *gitBranch = (char *) malloc( GIT_BRANCH_LENGTH * sizeof(char *));
            if (getCurrentGitBranch(gitBranch) == 0) 
            {
                // No branch found
                // Prompt User for input
                sprintf(promptMessage, 
                        "%s%s%s @ %s%s%s%s", 
                        KRED, user, KNORMAL, 
                        KGREEN, cwd, KNORMAL, 
                        "\n$ ");
            }
            else
            {
                // Git Branch found
                // Prompt User for input
                sprintf(promptMessage,
                        "%s%s%s @ %s%s%s%s git(%s)%s%s", 
                        KRED, user, KNORMAL, 
                        KGREEN, cwd, KNORMAL, 
                        KCYAN, gitBranch, KNORMAL,
                        "\n$ ");
            }
            free(gitBranch);

            // Get the input
            line = readline(promptMessage);
            if (line == NULL)
            {
                perror("READLINE ERROR!");
                exit(1);
            }

            // fprintf(stderr, "\nLINE BEFOR TRIM: '%s'\n", line);
            trimwhitespace(line);
            // fprintf(stderr, "\nLINE AFTER TRIM: '%s'\n", line);

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
            free(line);
        }
        else
        {
            perror("Error: Couldn't get the current directory, weird.");
            exit(1);
        }
    }

    printf("\n%sM%sr%sS%sh%se%sl%sl %spiping out!\n", KRED, KGREEN, KYELLOW, KBLUE, KMAGENTA, KCYAN, KWHITE, KNORMAL);

    return 0;
}
