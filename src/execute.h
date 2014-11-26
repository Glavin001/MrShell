#ifndef EXECUTE_H_INCLUDED
#define EXECUTE_H_INCLUDED

void buildTree(node **tree, char **argv, int *map);
void execute(char **argv);
void pipeTree(node *tree, int *fdIn, int *fdOut);
void execTree(node *tree, int *fdIn, int *fdOut);
void execCmd(char **cmd, int *fdIn, int *fdOut);
void pipeTreeToFile(node *tree, int *fdIn, int *fdOut, int oflags);

#endif