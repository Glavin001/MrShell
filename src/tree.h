#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

struct tree_node {
	char **command;
    struct tree_node *left;
    struct tree_node *right;
};
typedef struct tree_node node;

void insertNode(node **tree, char *command, bool isOperator, bool isFirstCmd);
void printPreorder(node *tree);
void printInorder(node *tree);
void printPostorder(node *tree);
void deleteTree(node *tree);

#endif