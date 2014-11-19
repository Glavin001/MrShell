#include <stdio.h>   // printf
#include <stdlib.h>  // strtol
#include <unistd.h>  // fork, wait, execvp, chdir, pid_t
#include <string.h>  // strcmp
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
    // Check for built-in functions
    if (strcmp(argv[0], "cd") == 0) 
    {
        // Change Directory
        if (chdir(argv[1]) == 0) 
        {
            return;
        } 
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