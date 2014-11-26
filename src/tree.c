#include <stdio.h>   // printf, sprintf, perror
#include <stdlib.h>  // strtol, getenv

#include "tree.h"
#include "constants.h"

void insertNode(node **tree, char **command, bool isOperator, bool isFirstCmd)
{
	node *temp = NULL;
    if(!(*tree))
    {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->command = command;
        if (isOperator) temp->isOp = 1;
        else temp->isOp = 0;
        *tree = temp;
        return;
    }
    // If an operator or the first command
    if(isOperator || (!isOperator && isFirstCmd))
    {
        insertNode(&(*tree)->left, command, isOperator, isFirstCmd);
    }
    else if (!isOperator && !isFirstCmd)
    {
        traverseDown(tree, command);
    }
}

void traverseDown(node **tree, char **command)
{
    // If the tree's left node is an operator and the tree's left node's right child is null
    if ((**tree).left->isOp == 1 && (**tree).left->right == NULL)
        traverseDown(&(*tree)->left, command);
    // Else insert to the right child
    else
        insertNode(&(*tree)->right, command, false, false);   
}


void buildTree(node **tree, char **argv, int *map)
{
    // Build Operators Map
    // Iterate thru all args in argv backwards
    int i;
    for (i=ARGV_LENGTH-1; i>=0; i--)
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


void printPreorder(node *tree)
{
	if (tree)
    {
        int i = 0;
        while (tree->command[i])
        {
            printf("%s ",tree->command[i]);
            i++;
        }
        printf("\n");
        printPreorder(tree->left);
        printPreorder(tree->right);
    }
}

void printInorder(node *tree)
{
	if (tree)
    {
        printInorder(tree->left);
        int i = 0;
        while (tree->command[i])
        {
            printf("%s ",tree->command[i]);
            i++;
        }
        printf("\n");
        printInorder(tree->right);
    }
}

void printPostorder(node *tree)
{
	if (tree)
    {
        printPostorder(tree->left);
        printPostorder(tree->right);
        int i = 0;
        while (tree->command[i])
        {
            printf("%s ",tree->command[i]);
            i++;
        }
        printf("\n");
    }
}

void deleteTree(node *tree)
{
	if (tree)
    {
        deleteTree(tree->left);
        deleteTree(tree->right);
        if (tree->command)
            free(tree->command);
        free(tree);
    }
}