#include <stdio.h>   // printf, sprintf, perror
#include <stdlib.h>  // strtol, getenv

#include "tree.h"

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