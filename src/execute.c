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
    // Operators
    for (int i=63; i>=0; i--)
    {
        if (map[i] != 0)
        {
            /*  1:  >
                2:  >>
                3:  |
                4:  <::
                5:  ::>
                6:  :    */
            insertNode(tree, &argv[i], true, false);
            /* No longer necessary???
            switch(map[i])
            {
                case 1:
                    insertNode(tree, ">", true, false);
                    break;
                case 2:
                    insertNode(tree, ">>", true, false);
                    break;
                case 3:
                    insertNode(tree, "|", true, false);
                    break;
                case 4:
                    insertNode(tree, "<::", true, false);
                    break;
                case 5:
                    insertNode(tree, "::>", true, false);
                    break;
                case 6:
                    insertNode(tree, ":", true, false);
                    break;
                default:
                    break;
            } */
        }
    }

    //TODO fix this so the commands are placed properly. Right now everything
    //     but the first command goes right from the node. However they should
    //     fill in the tree's right nodes starting deep left. Likely a combination
    //     of here and in tree.c
    // Commands
    int count = 0;
    while (argv[count] != '\0')
    {
        // printf("Build commands iteration: %d.  Map: %d.  argv: %s\n", count, map[count], argv[count]);
        if (map[count] != 0)
        {
            count++;
            continue;
        }
        //if (map[count] == 0)
        //{
        int length = 0;
        while (map[count] == 0)
        {
            length++;
            count++;
        }
        char **command = malloc (length * sizeof(char *));
        command = &argv[count-length];
        if (count == length)
            insertNode(tree, command, false, true);
        else
            insertNode(tree, command, false, false);  

        //}
    }
}

// Is below even needed anymore? From Glavin's initial work

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
    // Create a map of operators from argv
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
    
    // Print tree for debugging
    printf("Printing the command tree\n");
    printf("Preorder\n");
    printPreorder(executionTree);
    printf("Inorder\n");
    printInorder(executionTree);
    printf("Postorder\n");
    printPostorder(executionTree);

    //TODO Run execution tree
    
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

    printf("input: %s %s\n", input[0], input[1]);
    printf("output: %s %s\n", output[0], output[1]);

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
        printf("Above child execvp\n");
        if (execvp(*input, input) < 0)
        {
            printf("*** ERROR: child exec failed: %s\n", *input);
            exit(1);
        }
        printf("Below child execvp\n");
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
        printf("Above parent execvp\n");
        if (execvp(*output, output) < 0)
        {
            printf("*** ERROR: parent exec failed: %s\n", *output);
            exit(1);
        }
        printf("Below parent execvp\n");
    }
    return;
}