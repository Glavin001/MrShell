#ifndef EXECUTE_H_INCLUDED
#define EXECUTE_H_INCLUDED

void buildTree(node **tree, char **argv, int *map);
void execute(char **argv);
void mrshPipe(char **input, char **output);

#endif