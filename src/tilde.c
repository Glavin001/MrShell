#include <string.h>
#include <stdio.h> // printf
#include "tilde.h"

void tildeFinder(char **argv, char *home)
{
	int count = 0;
	int i = 0;
    while (argv[count] != '\0')
    {
    	for(i = 0; argv[count][i] != '\0'; i++) 
    	{
    		if (argv[count][i] == '~')
    		{
    			printf("Tilde found at position %i in argv %i\n", i, count);
    			tildeReplacer(argv[count], home, i+1);
    		}
    	    // printf("%c\n", argv[count][i]);
    	}
    	count++;
    }
    return;
}

void tildeReplacer(char *arg, char *home, int position)
{
	printf("home: %s\n", home);
	printf("before newArg init\n");
	char newArg[128];
	printf("before strcpy\n");
	strcpy(newArg, home);
	printf("before strcat\n");
	strcat(newArg, &arg[position]);
	printf("newarg: %s\n", newArg);
	printf("before arg=newArg\n");
	arg = newArg;
	return;
}