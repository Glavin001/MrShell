#ifndef EXECUTE_H_INCLUDED
#define EXECUTE_H_INCLUDED

#include <stdbool.h>
#include "tree.h"

void execute(char **argv);
void pipeTree(node *tree, int *fdIn, int *fdOut, int *status);
void execTree(node *tree, int *fdIn, int *fdOut, int *status);
void execCmd(char **cmd, int *fdIn, int *fdOut, bool showErrors, int *status);
void pipeTreeToFile(node *tree, int *fdIn, int *status, int oflags);
void execAndTree(node *tree, int *fdIn, int *fdOut, int *status);

#endif