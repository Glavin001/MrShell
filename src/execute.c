#include <stdio.h>   // printf, snprintf
#include <stdlib.h>  // getenv
#include <unistd.h>  // fork, wait, execvp, chdir, pid_t
#include <string.h>  // strcmp, strncpy, strcat, strlen
#include <pthread.h> //

#include "execute.h"


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
    // Create map
    /*
        1:  >
        2:  >>
        3:  |
        4:  <::
        5:  ::>
        6:  :
    */
    int map[64] = {0};
    int count = 0;
    while(1) 
    {
        if (argv[count] == '\0' && argv[count+1] == '\0') break;
        else
        {
            if (strcmp(argv[count], ">") == 0) 
            {
                map[count] = 1;
                printf("> at argv[%d]\n", count);
            }
            else if (strcmp(argv[count], ">>") == 0) 
            {
                map[count] = 2;
                printf(">> at argv[%d]\n", count);
            }
            else if (strcmp(argv[count], "|") == 0) 
            {
                map[count] = 3;
                printf(" | at argv[%d]\n", count);
            }
            else if (strcmp(argv[count], "<::") == 0) 
            {
                map[count] = 4;
                printf(" <:: at argv[%d]\n", count);
            }
            else if (strcmp(argv[count], "::>") == 0) 
            {
                map[count] = 5;
                printf(" ::> at argv[%d]\n", count);
            }
            else if (strcmp(argv[count], ":") == 0) 
            {
                map[count] = 6;
                printf(" : at argv[%d]\n", count);
            }
            // else if (strcmp(argv[count], "") == 0) {}
        }
        count++;
    }

    // Create run order
    count = 0;
    int lastToken = count;
    // int nextToken;
    char *input[64];
    int currentInput = 0;
    char *output[64];
    int currentOutput = 0;
    while (1)
    {
        if (argv[count] == '\0' && argv[count+1] == '\0') break;
        else
        {
            // Pipe
            if (map[count] == 3)
            {
                //Get input from lastToken -> pipe
                for (int i=lastToken; i<count; i++)
                {
                    input[currentInput] = argv[i];
                    currentInput++;
                }
                //Get output from from pipe -> nextToken
                for (int i=count+1; map[i]==0; i++)
                {
                    output[currentOutput] = argv[i];
                    currentOutput++;
                }
                mrshPipe(input, output);
            }
        }
        count++;
    }
    return;

    

    // // Check for built-in functions
    // if (strcmp(argv[0], "cd") == 0) 
    // {
    //     // If using shortcut ~ for home, fix up path
    //     // if (argv[1][0] == '~')
    //     // {
    //     //     // Get the current users home directory
    //     //     char home[256];
    //     //     snprintf(home, sizeof home, "%s%s%s", "/Users/", getenv("USER"), "/");

    //     //     // If deeper than home, make path
    //     //     if (argv[1][1] == '/')
    //     //     {
    //     //         char path[strlen(argv[1]) - 1];
    //     //         strncpy(path, &argv[1][2], strlen(argv[1]) - 1);
    //     //         strcat(home, path);
    //     //     }
    //     //     argv[1] = home;
    //     // }

    //     // Change Directory
    //     if (chdir(argv[1]) == 0) return;
    //     else 
    //     {
    //         printf("No such file or directory '%s'.\n", argv[1]);
    //         return;
    //     }
    // }

    // pid_t pid;
    // // Fork, if error exit
    // if ((pid = fork()) < 0) 
    // {   
    //     printf("*** ERROR: forking child process failed.\n");
    //     exit(1);
    // }
    // else if (pid == 0) // Child process, execute command
    // {
    //     if (execvp(*argv, argv) < 0) 
    //     {
    //         printf("*** ERROR: exec failed.\n");
    //         exit(1);
    //     }
    // }
    // else // Parent process
    // {
    //     // Wait for child
    //     int wc = wait(NULL);
    //     if (wc == -1)
    //     {
    //         printf("*** Error: wait failed.\n");
    //         exit(1);
    //     }
    // }
}

void mrshPipe(char **input, char **output)
{
    //Piping
    int fd[2];
    pid_t pid;

    // Create pipe, check for failure
    if (pipe(fd) < 0) 
    { 
        perror("Pipe Failed"); 
        exit(1); 
    }
    
    // Fork process, check for failure
    if ((pid = fork()) < 0) 
    { 
        perror("Fork Failed"); 
        exit(1); 
    }
    else if (pid == 0) //Child
    {
        //Close input side of pipe
        close(fd[0]);
        //Make 1 same as output side of pipe
        dup2(fd[1], 1);
        //Close output side of pipe
        close(fd[1]); 
        //Run command, check for error
        if (execvp(*input, input) < 0)
        {
            printf("*** ERROR: child exec failed: %s\n", *input);
            exit(1);
        }
    }
    else //Parent
    {
        int wc = wait(NULL);
        //Close output side of pipe
        close(fd[1]);
        //Make 0 same as input side of pipe
        dup2(fd[0], 0);
        //Close input side of pipe
        close(fd[0]);
        //Run command, check for error
        if (execvp(*output, output) < 0)
        {
            printf("*** ERROR: parent exec failed: %s\n", *output);
            exit(1);
        }
    }
    return;
}