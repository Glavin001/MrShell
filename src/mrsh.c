/* strtol example */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* strtol */
#include <unistd.h>
#include <string.h>
#include <pthread.h>

//
#include "common.h"
#include "parse.h"
#include "execute.h"
#include "chalk.h"

// === Structs ===
// struct commandArgs {
//     int argc;
//     //const char **argv;
//     char *argv[64];
// };

// === Main ===
/**
Start of program

@param argc argument count
@param argv argument vector
@return an integer indicating success or failure.
*/
int main (void) //(int argc, const char** argv)
{

    printWelcome();

    char  line[1024];             /* the input line                 */
    char  *argv[64];              /* the command line argument      */
    // struct commandArgs cmd;
    // pthread_t run_thread;
    char cwd[1024];

    while (1)
    {
        // Get Current Working Directory
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {

            char *user = getenv("USER");
            if(user == NULL) {
                exit(1);
            }
            // Prompt User
            printf("%s%s%s@%s%s%s%s", KRED, user, KNORMAL, KBLUE, cwd, KNORMAL, "$ ");     /*   display a prompt             */

            if ( fgets(line, sizeof(line), stdin) ) /*   read in the command line     */
            {
                size_t len = strlen(line);
                if (len != 0 && line[len - 1] == '\n')
                    line[--len] = '\0';
                // printf("%s\n", line);
            }
            //printf("Line: %s\n", line);
            parse(line, argv);       /*   parse the line              */
            //printf("Argv: %s\n", argv[0]);

            if (argv[0] == NULL)
            {
                //printf("Please enter a valid command.\n");
                continue;
            }
            else if (strcmp(argv[0], "exit") == 0)    /* is it an "exit"?     */
            {
                exit(0);            /*   exit if it is                */
            }
            else
            {
                execute(argv);           /* otherwise, execute the command */
            }
            // /* create a second thread which executes inc_x(&x) */
            // if(pthread_create(&run_thread, NULL, execute, (void *)argv))
            // {
            //   fprintf(stderr, "Error creating thread\n");
            //   return 1;
            // }

            // /* wait for the second thread to finish */
            // if(pthread_join(run_thread, NULL))
            // {
            //   fprintf(stderr, "Error joining thread\n");
            //   return 2;
            // }

            // printf("\n");

        }
        else
        {
            perror("getcwd() error");
            exit(1);
        }


    }

    printf("\nGoodbye!\n");

    return 0;
}
