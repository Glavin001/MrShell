#include <stdio.h>   // printf, snprintf
#include <stdlib.h>  // getenv
#include <unistd.h>  // fork, wait, execvp, chdir, pid_t
#include <string.h>  // strcmp, strncpy, strcat, strlen
#include <pthread.h> //
#include <stdbool.h>

#include "tree.h"
#include "execute.h"

void buildTree(node **tree, char **argv, int *map)
{
    // Build Operators Map
    // Iterate thru all args in argv backwards
    int i;
    for (i=63; i>=0; i--)
    {
        // Check if arg is an operator
        if (map[i] != 0)
        {
            // Is an Operator
            //  1:  >    2:  >>    3:  |    4:  <::    5:  ::>    6:  :  
            char **command = malloc(2 * sizeof(char*));
            command[0] = argv[i];
            command[1] = NULL;
            insertNode(tree, command, true, false);
        }
    }

    // Commands
    int count = 0;
    while (argv[count] != '\0')
    {
        bool isFirstCmd = (count == 0) ? true : false;
        
        // if an operator skip this iteration
        if (map[count] != 0)
        {
            count++;
            continue;
        }

        // Count how many 'flags' are in this command
        int length = 0;
        while (map[count] == 0)
        {
            length++;
            count++;
        }
        // Allocate space for the command
        char **command = malloc ( (length + 1) * sizeof(char *));

        // Add each command/flag from argv to command
        int i;
        for (i = 0; i < length; i++)
            command[i] = argv[count - length + i];
        // Null terminate the command
        command[length] = NULL;

        // If first, insert left, else insert acording to algorithm in tree
        if (isFirstCmd)
            insertNode(tree, command, false, true);
        else
            insertNode(tree, command, false, false);  
    }
}

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
            if (argv[count+1] == '\0') 
            {
                // fprintf(stderr, "break buildMap\n");
                break;
            }
            // fprintf(stderr, "Continuing");

            count++;
            continue;
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
            // else if (strcmp(argv[count], "") == 0) {}
        }
        count++;
    }
}

void execute(char **argv)
{
    // fprintf(stderr, "Execute!\n");

    int map[64] = {0};
    buildMap(map, argv);

    // fprintf(stderr, "Map built\n");

    if (strcmp(argv[0], "cd") == 0) 
    {
         // Change Directory
         if (chdir(argv[1]) == 0) return;
         else 
         {
             printf("No such file or directory '%s'.\n", argv[1]);
         }
    }
    // Create an execution tree from map and argv
    node *executionTree = NULL;
    buildTree(&executionTree, argv, map);

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
    execTree(executionTree, fdIn, fdOut);
    
    // fprintf(stderr, "Done executing\n");

    // Delete the tree and return from execute call
    deleteTree(executionTree);

    // fprintf(stderr, "Done deleting\n");

    return;
}

void execTree(node *tree, int *fdIn, int *fdOut)
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
                // Change Directory
                if (chdir(cmd[1]) != 0) 
                {
                    fprintf(stderr, "No such file or directory '%s'.\n", cmd[1]);
                }
                return;
            }

            execCmd(tree->command, fdIn, fdOut);

            return;
        } else //node is an operator
        {

            // Which Operator?
            char *op = tree->command[0];

            // Piping
            if (strcmp(op, "|") == 0) 
            {
                 fprintf(stderr, "Piping operator\n");

                if (!tree->left->isOp && !tree->right->isOp) 
                {
                    // fprintf(stderr, "PIPING! %s | %s\n", tree->left->command, tree->right->command);
                    pipeCmds(tree->left->command, tree->right->command, fdIn, fdOut);
                    // fprintf(stderr, "DONE PIPINGG\n");
                }
                else
                {
                    //Recurse down the tree
                    execTree(tree->left, fdIn, fdOut);
                }
                return;
            }
            else
            {
                fprintf(stderr, "Unsupported Operator: %s\n", op);
                return;
            }

            // execTree(tree->left, fd);
            // execTree(tree->right, fd);
        }
    }
    else
    {
        fprintf(stderr, "Tree is empty.\n");
    }
}


// Simple 1-1 piping
void pipeCmds(char **inputCmd, char **outputCmd, int *fdIn, int *fdOut)
{
     fprintf(stdout, "inputCmd: %s\n", *inputCmd);
     fprintf(stdout, "outputCmd: %s\n", *outputCmd);

    close(fdIn[0]);    /* close read end of pipe               */

    // Create pipe from inputCmd to outputCmd
    int fdPipe[2]; // [read, write]
    // Create pipe, check for failure
    if (pipe(fdPipe) < 0) 
    { 
        perror("Pipe fdPipe Failed\n"); 
        exit(1); 
    }

    // Execute first
    // fprintf(stderr, "Execute inputCmd\n");
    execCmd(inputCmd, fdIn, fdPipe);
    // fprintf(stderr, "Done execute inputCmd\n");

    // Pipe output to input of next command
    close(fdPipe[1]);    /* close write end of pipe              */
    // dup2(fdPipe[0], fdIn[1]);   /* make 0 same as read-from end of pipe */

    // Run output / second command
    // fprintf(stderr, "Execute outputCmd\n");
    execCmd(outputCmd, fdPipe, fdOut);
    // fprintf(stderr, "Done execute outputCmd\n");

}

void execCmd(char **cmd, int *fdIn, int *fdOut)
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
        if (wait(NULL) == -1)
        {
            printf("*** Error: wait failed. This may get confusing\n");         
        }
        
        // fprintf(stdout, "execCmd done\n");
    }
    return;
}