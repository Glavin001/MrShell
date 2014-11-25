#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

struct tree_node {
	char **command;
	int isOp;
    struct tree_node *left;
    struct tree_node *right;
};
typedef struct tree_node node;

void insertNode(node **tree, char **command, bool isOperator, bool isFirstCmd);
void traverseDown(node **tree, char **command);
void printPreorder(node *tree);
void printInorder(node *tree);
void printPostorder(node *tree);
void deleteTree(node *tree);

#endif