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
            } 
        }
    }

    // Commands
    int count = 0;
    while (argv[count] != '\0')
    {
        // printf("Build commands iteration: %d.  Map: %d.  argv: %s\n", count, map[count], argv[count]);
        if (count == 0 && map[count] == 0)
        {
            insertNode(tree, argv[count], false, true);
        }
        else if (map[count] == 0)
        {
            insertNode(tree, argv[count], false, false);
        }
        count++;
    }
}

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

    // Create Tree
    node *root;
    buildTree(&root, argv, map);
    printf("Printing the command tree\n");
    printf("Preorder\n");
    printPreorder(root);
    printf("Inorder\n");
    printInorder(root);
    printf("Postorder\n");
    printPostorder(root);


    // Create run order
    // count = 0;
    // int lastToken = count;
    // // int nextToken;
    // char *input[64];
    // int currentInput = 0;
    // char *output[64];
    // int currentOutput = 0;
    // while (1)
    // {
    //     if (argv[count] == '\0' && argv[count+1] == '\0') break;
    //     else
    //     {
    //         // Pipe
    //         if (map[count] == 3)
    //         {
    //             //Get input from lastToken -> pipe
    //             for (int i=lastToken; i<count; i++)
    //             {
    //                 input[currentInput] = argv[i];
    //                 currentInput++;
    //             }
    //             //Get output from from pipe -> nextToken
    //             for (int i=count+1; map[i]==0; i++)
    //             {
    //                 output[currentOutput] = argv[i];
    //                 currentOutput++;
    //             }
    //             mrshPipe(input, output);
    //             printf("After mrshPipe call");
    //         }
    //     }
    //     count++;
    // }
    
    deleteTree(root);
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