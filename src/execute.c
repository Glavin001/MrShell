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

    char *input[2];
    char *output[1];
    input[0] = "cat";
    input[1] = "README.md";
    output[0] = "wc";
    mrshPipe(input, output);
    
    // Delete the tree and return from execute call
    deleteTree(executionTree);
    return;


    // What is commented below is a fully working basic shell implementation
    // It will fork/run your commands, but not take into account pipes and 
    // whatnot. Left in for reference & copy/pasting to suit future needs.
    // If testing this out don't forget to comment the return above / move 
    // it below this block   

    // // Check for built-in functions
    // if (strcmp(argv[0], "cd") == 0) 
    // {
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
    //     // Wait for child to complete
    //     int wc = wait(NULL);
    //     if (wc == -1)
    //     {
    //         printf("*** Error: wait failed.\n");
    //         exit(1);
    //     }
    // }
}

// This isn't working properly. I'm thinking it has something to
// do with the file descriptors and stdin/out. Although during testing
// the parent always ran first, couldn't figure out why
// This started as a simple test for 1-1 piping
void mrshPipe(char **input, char **output)
{
    //Piping
    int fd[2];
    pid_t pid;

    printf("input: %s\n", *input);
    printf("output: %s\n", *output);

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
        // printf("top of child\n");
        //Close input side of pipe
        close(fd[0]);
        //Make the output of the child process be stdout in pipe
        dup2(fd[1], 1);
        //Close output side of pipe
        close(fd[1]); 
        //Run command, check for error
        fprintf(stderr, "Above child execvp\n");
        if (execvp(*input, input) < 0)
        {
            fprintf(stderr, "*** ERROR: child exec failed: %s\n", *input);
            exit(1);
        }
        // printf("Below child execvp\n");
    }
    else //Parent
    {
        // printf("above wait\n");
        int wc = wait(NULL);
        //Close output side of pipe
        close(fd[1]);
        //Make the input of parent process be stdin in pipe
        dup2(fd[0], 0);
        //Close input side of pipe
        close(fd[0]);
        //Run command, check for error
        // printf("Above parent execvp\n");
        if (execvp(*output, output) < 0)
        {
            fprintf(stderr, "*** ERROR: parent exec failed: %s\n", *output);
            exit(1);
        }
        fprintf(stderr, "Below parent execvp\n");
    }
    return;
}