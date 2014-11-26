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
	char *newArg = "";
	printf("before strcpy\n");
	strcpy(newArg, home);
	printf("before strcat\n");
	strcat(newArg, &arg[position]);
	printf("before arg=newArg\n");
	arg = newArg;
	printf("%s", newArg);
	return;
}