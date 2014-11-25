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
    for (int i=63; i>=0; i--)
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
        for (int i = 0; i < length; i++)
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

void execute(char **argv)
{
    // Create a map of operators from argv
    //  1:  >    2:  >>    3:  |    4:  <::    5:  ::>    6:  :  
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

    // Create an execution tree from map and argv
    node *executionTree = NULL;
    buildTree(&executionTree, argv, map);

    //TODO Run execution tree

    // Pipe testing

    // char *input[3];
    // char *output[2];
    // input[0] = "cat";
    // input[1] = "README.md";
    // input[2] = '\0';
    // output[0] = "wc";
    // output[1] = '\0';    

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

    // close(fdOut[0]);    /* close read end of pipe               */
    // dup2(fdOut[1],1);   /* make 1 same as write-to end of pipe  */

    // printInorder(executionTree);
    // printPostorder(executionTree);
    execTree(executionTree, fdIn, fdOut);

    /* Parent process closes up output side of pipe */
    close(fdOut[1]);
    /* Read in a string from the pipe */
    char readbuffer[1024];
    int nbytes = read(fdOut[0], readbuffer, sizeof(readbuffer));
    printf("Received string: %s\n", readbuffer);
    
    // Delete the tree and return from execute call
    deleteTree(executionTree);
    return;
}


void execTree(node *tree, int *fdIn, int *fdOut)
{
    // Check for tree
    if (tree)
    {
        // Has tree
        if (!tree->isOp)
        {
            printf("Is NOT Operator: ");
            int i=0;
            while (tree->command[i])
            {
                printf("%s ",tree->command[i]);
                i++;
            }
            printf("\n");

            char **cmd = tree->command;
            // What is commented below is a fully working basic shell implementation
            // It will fork/run your commands, but not take into account pipes and 
            // whatnot. Left in for reference & copy/pasting to suit future needs.
            // If testing this out don't forget to comment the return above / move 
            // it below this block   

            // Check for built-in functions
            if (strcmp(cmd[0], "cd") == 0) 
            {
                // Change Directory
                if (chdir(cmd[1]) == 0) {
                    return;
                }
                else 
                {
                    printf("No such file or directory '%s'.\n", cmd[1]);
                    return;
                }
            }

            execCmd(tree->command, fdIn, fdOut);

            return;
        } else
        {
            // Is Operator
            printf("Is Operator: ");
            int i=0;
            while (tree->command[i])
            {
                printf("%s ",tree->command[i]);
                i++;
            }
            printf("\n");
            // Which Operator?
            char *op = tree->command[0];

            // Piping
            if (strcmp(op, "|") == 0) 
            {
                printf("Piping operator\n");

                if (!tree->left->isOp && !tree->right->isOp) 
                {
                    printf("PIPING! %s | %s\n", tree->left->command, tree->right->command);
                    pipeCmds(tree->left->command, tree->right->command, fdIn, fdOut);
                }

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
        fprintf(stderr, "Tree is empty");
    }
}


// This isn't working properly. I'm thinking it has something to
// do with the file descriptors and stdin/out. Although during testing
// the parent always ran first, couldn't figure out why
// This started as a simple test for 1-1 piping
void pipeCmds(char **inputCmd, char **outputCmd, int *fdIn, int *fdOut)
{
    // Piping
    // int fd[2]; // [read, write]
    pid_t pid;

    fprintf(stdout, "child input: %s %s\n", *inputCmd, *(inputCmd+1));
    fprintf(stdout, "parent input (output): %s\n", *outputCmd);

    if ((pid = fork()) < 0) 
    { 
        perror("Fork Failed"); 
        exit(1); 
    }
    else if (pid == 0) // Child
    {
        close(fdIn[0]);    /* close read end of pipe               */

        // Create pipe from inputCmd to outputCmd
        int fdPipe[2]; // [read, write]
        // Create pipe, check for failure
        if (pipe(fdPipe) < 0) 
        { 
            perror("Pipe fdPipe Failed"); 
            exit(1); 
        }
    
        // Execute first
        execCmd(inputCmd, fdIn, fdPipe);

        // Pipe output to input of next command
        close(fdPipe[1]);    /* close write end of pipe              */
        // dup2(fdPipe[0], fdIn[1]);   /* make 0 same as read-from end of pipe */

        // Run output / second command
        execCmd(outputCmd, fdPipe, fdOut);
        return;
    }
    else // Parent
    {
        int wc = wait(NULL);
        return;
    }

}

void execCmd(char **cmd, int *fdIn, int *fdOut)
{
    pid_t pid;
    
    // Fork process, check for failure
    if ((pid = fork()) < 0) 
    { 
        perror("Fork Failed"); 
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
            fprintf(stderr, "*** ERROR: child exec failed: %s\n", *cmd);
            exit(1);
        }
    }
    else //Parent
    {
        close(fdOut[1]);    /* close write end of pipe              */
        int wc = wait(NULL);
        
        fprintf(stdout, "execCmd done");
    }
    return;
}