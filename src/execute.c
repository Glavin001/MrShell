#include <stdio.h>   // printf, snprintf
#include <stdlib.h>  // getenv
#include <unistd.h>  // fork, wait, execvp, chdir, pid_t
#include <string.h>  // strcmp, strncpy, strcat, strlen
#include <pthread.h> // 
#include <fcntl.h>

#include "execute.h"
#include "constants.h"

void buildMap(int *map, char **argv)
{
    // Create a map of operators from argv
    //  1:  >    2:  >>    3:  |    4:  <::    5:  ::>    6:  :  
    int count = 0;
    while(1) 
    {
        // fprintf(stderr, "buildMap %i\n", count);
        if (argv[count] == '\0')
        {
            break;
        }
        else
        {
            // fprintf(stderr, "mapping char: %s %s\n", argv[count], argv[count+1]);

            if (strcmp(argv[count], ">") == 0) 
            {
                map[count] = 1;
                // printf("> at argv[%d]\n", count);
            }
            else if (strcmp(argv[count], ">>") == 0) 
            {
                map[count] = 2;
                // printf(">> at argv[%d]\n", count);
            }
            else if (strcmp(argv[count], "|") == 0) 
            {
                map[count] = 3;
                // printf(" | at argv[%d]\n", count);
            }
            else if (strcmp(argv[count], "<::") == 0) 
            {
                map[count] = 4;
                // printf(" <:: at argv[%d]\n", count);
            }
            else if (strcmp(argv[count], "::>") == 0) 
            {
                map[count] = 5;
                // printf(" ::> at argv[%d]\n", count);
            }
            else if (strcmp(argv[count], ":") == 0) 
            {
                map[count] = 6;
                // printf(" : at argv[%d]\n", count);
            }
            else if (strcmp(argv[count], "&&") == 0) 
            {
                map[count] = 7;
                // printf(" : at argv[%d]\n", count);
            }
            // else if (strcmp(argv[count], "") == 0) {}
        }
        count++;
    }
}

void execute(char **argv)
{
    // fprintf(stderr, "Execute!\n");

    int map[ARGV_LENGTH] = {0};
    buildMap(map, argv);

    // fprintf(stderr, "Map built\n");

    // Create an execution tree from map and argv
    node *executionTree = NULL;

    // fprintf(stderr, "Print tree\n");
    // printPreorder(executionTree);
    // fprintf(stderr, "\n");

    buildTree(&executionTree, argv, map);

    // fprintf(stderr, "Print tree\n");
    // printPreorder(executionTree);
    // fprintf(stderr, "\n");

    // Create pipe file descriptors
    int fdIn[2]; // [read, write]
    int fdOut[2]; // [read, write]

    // Create pipe, check for failure
    if (pipe(fdIn) < 0) 
    { 
        perror("Pipe fdIn Failed"); 
        exit(1); 
    }
    // Create pipe, check for failure
    if (pipe(fdOut) < 0) 
    { 
        perror("Pipe fdOut Failed"); 
        exit(1);
    }

    // The Output of this executionTree should go to stdout
    close(fdOut[0]);    /* close read end of pipe               */
    dup2(1, fdOut[1]);   /* make 1 same as write-to end of pipe  */

    // Execute the tree!
    int status;
    execTree(executionTree, fdIn, fdOut, &status);
    
    // fprintf(stderr, "Done executing\n");

    // Delete the tree and return from execute call
    deleteTree(executionTree);

    return;
}

void execTree(node *tree, int *fdIn, int *fdOut, int *status)
{
    // fprintf(stderr, "execTree %i %i /n", fdOut[0], fdOut[1]);
    // Check for tree
    if (tree)
    {
        // Has tree
        if (!tree->isOp)
        {
            // printf("Is NOT Operator: ");
            // int i=0;
            // while (tree->command[i])
            // {
            //     printf("%s ",tree->command[i]);
            //     i++;
            // }
            // printf("\n");

            char **cmd = tree->command;
            
            // Check for built-in functions
            if (strcmp(cmd[0], "cd") == 0) 
            {
                char *path = cmd[1];
                // Check for null
                if (path == NULL)
                {
                    path = getenv("HOME"); // Get the home directory
                }
                // Change Directory
                if (chdir(path) != 0)
                {
                    fprintf(stderr, "No such file or directory '%s'.\n", cmd[1]);
                }
                return;
            }
            else if (strcmp(cmd[0], "export") == 0)
            {
                // Export
                char *a = cmd[1];
                if (a != NULL) {
                    putenv(a);
                }
                return;
            }

            close(fdIn[1]);    /* close write end of pipe */
            execCmd(tree->command, fdIn, fdOut, true, status);
            // fprintf(stderr, "status: %i\n", *status);

            return;
        }
        else
        {
            // Node is an operator
            // Which Operator?
            char *op = tree->command[0];

            // Piping
            if (strcmp(op, "|") == 0) 
            {
                // fprintf(stderr, "Piping operator\n");

                // Recurse down the tree
                // fprintf(stderr, "recurse down tree\n");

                pipeTree(tree, fdIn, fdOut, status);

                return;
            }
            else if (strcmp(op, ">") == 0)
            {
                // fprintf(stderr, "left: %s\n", tree->left->command[0]);
                // fprintf(stderr, "right: %s\n", tree->right->command[0]);
                pipeTreeToFile(tree, fdIn, status, O_CREAT | O_TRUNC | O_WRONLY);
                return;
            }
            else if (strcmp(op, ">>") == 0)
            {
                pipeTreeToFile(tree, fdIn, status, O_CREAT | O_APPEND | O_WRONLY);
                return;
            }
            else if (strcmp(op, "&&") == 0)
            {
                // fprintf(stderr, "&&");
                execAndTree(tree, fdIn, fdOut, status);
                return;
            }
            else
            {
                fprintf(stderr, "Unsupported Operator: %s\n", op);
                return;
            }
        }
    }
    else
    {
        fprintf(stderr, "MrShell error: Execution Tree is empty. Please check your syntax.\n");
    }
}


void execAndTree(node *tree, int *fdIn, int *fdOut, int *status)
{
    
    // Create pipe, check for failure
    int fdPipe[2]; // [read, write]
    if (pipe(fdPipe) < 0) 
    { 
        perror("Pipe fdPipe Failed\n"); 
        exit(1); 
    }
    execTree(tree->left, fdIn, fdPipe, status);
    close(fdPipe[1]);    /* close write end of pipe */

    if (*status == 0)
    {
        execTree(tree->right, fdPipe, fdOut, status);
        close(fdOut[1]);    /* close write end of pipe */    
    }
    else
    {
        // fprintf(stderr, "Command errored: %i\n", *status);
    }

}


// Piping Tree
void pipeTree(node *tree, int *fdIn, int *fdOut, int *status)
{
    
    // Create pipe, check for failure
    int fdPipe[2]; // [read, write]
    if (pipe(fdPipe) < 0) 
    { 
        perror("Pipe fdPipe Failed\n"); 
        exit(1); 
    }
    execTree(tree->left, fdIn, fdPipe, status);
    close(fdPipe[1]);    /* close write end of pipe */
    execTree(tree->right, fdPipe, fdOut, status);
    close(fdOut[1]);    /* close write end of pipe */

}

void pipeTreeToFile(node *tree, int *fdIn, int *status, int oflags)
{
    // Create pipe, check for failure
    int fdPipe[2]; // [read, write]
    if (pipe(fdPipe) < 0) 
    { 
        perror("Pipe fdPipe Failed\n"); 
        exit(1); 
    }

    char *filePath = tree->right->command[0];
    // fprintf(stderr, "filepath: %s\n", filePath);

    int fd = open(filePath, oflags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd < 0) {
        perror("fp");
        fprintf(stderr, "ERROR: Write error occured to file '%s'\n", filePath);
        exit(1);
    }

    // The Output of this executionTree should go to stdout
    close(fdPipe[0]);    /* close read end of pipe               */
    dup2(fd, fdPipe[1]);   /* make 1 same as write-to end of pipe  */

    execTree(tree->left, fdIn, fdPipe, status);

}

void execCmd(char **cmd, int *fdIn, int *fdOut, bool showErrors, int *status)
{
    pid_t pid;
    
    // Fork process, check for failure
    if ((pid = fork()) < 0) 
    { 
        perror("Fork Failed\n"); 
        exit(1);
    }
    else if (pid == 0) //Child
    {
        
        close(fdIn[1]);    /* close write end of pipe              */
        dup2(fdIn[0],0);   /* make 0 same as read-from end of pipe */

        close(fdOut[0]);    /* close read end of pipe               */
        dup2(fdOut[1],1);   /* make 1 same as write-to end of pipe  */

        if (!showErrors)
        {
            int devNull = open("/dev/null", O_WRONLY);
            dup2(devNull, 2);
        }

        //Run command, check for error
        if (execvp(*cmd, cmd) < 0)
        {
            fprintf(stderr, "*** ERROR: command not found: %s\n", *cmd);
            // exit child
            _exit(1);
        }
    }
    else //Parent
    {
        close(fdOut[1]);    /* close write end of pipe              */
        
        // Try to wait for child
        if (wait(status) == -1)
        {
            printf("*** Error: wait failed. This may get confusing\n");         
        }
        // fprintf(stdout, "execCmd done\n");
    }
    return;
}