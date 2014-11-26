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
            // printf("Tilde found at position %i in argv %i\n", i, count);
            tildeReplacer(argv, count, home, i+1);
        }
        // printf("After char: %c\n", argv[count][i]);
        // printf("After arg: %s\n", argv[count]);
        count++;
    }
    return;
}

void tildeReplacer(char **argv, int count, char *home, int position)
{
    char *arg = argv[count];
    // printf("home: %s\n", home);
    // printf("before newArg init\n");
    char *newArg = (char *) malloc(strlen(arg) + strlen(home));
    // printf("before strcpy\n");
    strcpy(newArg, home);
    // printf("before strcat\n");
    strcat(newArg, &arg[position]);
    // printf("newarg: %s\n", newArg);
    // printf("before arg=newArg\n");
    argv[count] = newArg;
    // printf("after arg: %s\n", arg);
    // printf("after argv[count]: %s\n", argv[count]);
    return;
}