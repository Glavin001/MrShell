#include <string.h>
#include <stdio.h> // printf
#include <stdlib.h>
#include "tilde.h"

void tildeFinder(char **argv, char *home)
{
    int count = 0;
    int i = 0;
    while (argv[count] != '\0')
    {
        if (argv[count][i] == '~')
        {
            tildeReplacer(argv, count, home, i+1);
        }
        count++;
    }
    return;
}

void tildeReplacer(char **argv, int count, char *home, int position)
{
    char *arg = argv[count];
    char *newArg = (char *) malloc(strlen(arg) + strlen(home));
    strcpy(newArg, home);
    strcat(newArg, &arg[position]);
    argv[count] = newArg;
    return;
}