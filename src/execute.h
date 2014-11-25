#ifndef EXECUTE_H_INCLUDED
#define EXECUTE_H_INCLUDED

void buildTree(node **tree, char **argv, int *map);
void execute(char **argv);
void pipeCmds(char **input, char **output, int *fd);
void execTree(node *tree, int *fd);

#endif