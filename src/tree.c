#include <stdio.h>   // printf, sprintf, perror
#include <stdlib.h>  // strtol, getenv
#include <stdbool.h>

#include "tree.h"

void insertNode(node **tree, char **command, bool isOperator, bool isFirstCmd)
{
	node *temp = NULL;
    if(!(*tree))
    {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->command = command;
        *tree = temp;
        return;
    }

    if(isOperator || (!isOperator && isFirstCmd))
    {
        insertNode(&(*tree)->left, command, isOperator, isFirstCmd);
    }
    // TODO Fix this, see execute.c
    else if (!isOperator && !isFirstCmd)
    {
        insertNode(&(*tree)->right, command, isOperator, isFirstCmd);
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