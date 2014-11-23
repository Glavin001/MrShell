#include <stdio.h>   // printf, snprintf
#include <stdlib.h>  // getenv
#include <unistd.h>  // fork, wait, execvp, chdir, pid_t
#include <string.h>  // strcmp, strncpy, strcat, strlen
#include <pthread.h> //


// void *execute(void *cmd_void_ptr)
// {
//     // struct commandArgs *cmd = (struct commandArgs *)cmd_void_ptr;
//     // char **argv = cmd->argv;
//     char **argv = (char **) cmd_void_ptr;
//     printf("Command: %s\n", argv[0]);
//     if (execvp(*argv, argv) < 0) {     
//         /* execute the command  */
//         printf("*** ERROR: exec failed\n");
//         exit(1);
//     }
//     return 0;
// }


void execute(char **argv)
{
    // Create bitmaps
    int pipes[64] = {0};
    int redirectNew[64] = {0};
    int redirectAppend[64] = {0};
    int extremeStart[64] = {0};
    int extremeEnd[64] = {0};
    int extremeMiddle[64] = {0};
    int count = 0;
    while(1) 
    {
        if (argv[count] == '\0' && argv[count+1] == '\0') break;
        else
        {
            if (strcmp(argv[count], ">") == 0) 
            {
                redirectNew[count] = 1;
                printf("> at argv[%d]\n", count);
            }
            else if (strcmp(argv[count], ">>") == 0) 
            {
                redirectAppend[count] = 1;
                printf(">> at argv[%d]\n", count);
            }
            else if (strcmp(argv[count], "|") == 0) 
            {
                pipes[count] = 1;
                printf(" | at argv[%d]\n", count);
            }
            else if (strcmp(argv[count], "<::") == 0) 
            {
                extremeStart[count] = 1;
                printf(" <:: at argv[%d]\n", count);
            }
            else if (strcmp(argv[count], "::>") == 0) 
            {
                extremeEnd[count] = 1;
                printf(" ::> at argv[%d]\n", count);
            }
            else if (strcmp(argv[count], ":") == 0) 
            {
                extremeMiddle[count] = 1;
                printf(" : at argv[%d]\n", count);
            }
            // else if (strcmp(argv[count], "") == 0) {}
        }
        count++;
    }

    // Check for built-in functions
    if (strcmp(argv[0], "cd") == 0) 
    {
        // If using shortcut ~ for home, fix up path
        // if (argv[1][0] == '~')
        // {
        //     // Get the current users home directory
        //     char home[256];
        //     snprintf(home, sizeof home, "%s%s%s", "/Users/", getenv("USER"), "/");

        //     // If deeper than home, make path
        //     if (argv[1][1] == '/')
        //     {
        //         char path[strlen(argv[1]) - 1];
        //         strncpy(path, &argv[1][2], strlen(argv[1]) - 1);
        //         strcat(home, path);
        //     }
        //     argv[1] = home;
        // }

        // Change Directory
        if (chdir(argv[1]) == 0) return;
        else 
        {
            printf("No such file or directory '%s'.\n", argv[1]);
            return;
        }
    }

    pid_t pid;
    // Fork, if error exit
    if ((pid = fork()) < 0) 
    {   
        printf("*** ERROR: forking child process failed.\n");
        exit(1);
    }
    else if (pid == 0) // Child process, execute command
    {
        if (execvp(*argv, argv) < 0) 
        {
            printf("*** ERROR: exec failed.\n");
            exit(1);
        }
    }
    else // Parent process
    {
        // Wait for child
        int wc = wait(NULL);
        if (wc == -1)
        {
            printf("*** Error: wait failed.\n");
            exit(1);
        }
    }
}