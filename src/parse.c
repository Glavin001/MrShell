#include <stdio.h> // printf
#include <stdlib.h>
#include <string.h>
#include "tilde.h"   // tilde detection/replacement

void parse(char *origLine, char **argv)
{

    // Duplicate `line`
    char *line;
    line = (char *) malloc(strlen(origLine) + 1);
    strcpy(line, origLine); // see the below edit

    char beginQuote = '\0';
    char **av = argv;

    // While not the end of line
    while (*line != '\0')
    {
        // printf("Top of while loop\n");
        
        // While there are spaces, tabs or new lines replace with null
        // printf("Line before nested while loop 1: %s\n", line);
        while (*line == ' ' || *line == '\t' || *line == '\n') 
        {
            // printf("Replace space, tab, or new line: %c\n", *line);
            *line++ = '\0';
        }
        // printf("Line after nested while loop 1: %s\n", line);
        
        // save the position of argument
        *av++ = line;

        // while not null, space, tab, or new line
        while (*line != '\0' && *line != ' ' &&
                *line != '\t' && *line != '\n')
        {
            // If backslash skip a character (allows user to have spaces in filenames)
            if (*line == '\\') 
            {
                // printf("Skip backslash: %c\n", *line);
                // printf("Ignoring next character: %c\n", *(line+1));
                
                // Rotation String Left and remove the backslash
                char *c = line;
                while (*c != '\0') 
                {
                    *c = *(c+1);
                    c++;
                }
                line++;
            }
            else if (*line == '"' || *line == '\'')
            {
                // fprintf(stderr, "Begin quote: %s\n", line);
                beginQuote = *line;

                // Rotation String Left and remove the quotation char
                char *c = line;
                while (*c != beginQuote 
                    || c == line)
                {
                    // fprintf(stderr, "before char: %s\n", c);
                    *c = *(c+1);
                    // fprintf(stderr, "after char: %s\n", c);
                    c++;
                }
                // fprintf(stderr, "End quote: %s\n", c);
                c--;
                line = c;
                // fprintf(stderr, "End line: %s\n", line);

                // Rotation String Left and remove the quotation char
                while (*c != '\0')
                {
                    // fprintf(stderr, "befor char: %s\n", c);
                    *c = *(c+2);
                    // fprintf(stderr, "after char: %s\n", c);
                    c++;
                }
                // fprintf(stderr, "End c: '%s', line: '%s'\n", c, line);
                beginQuote = '\0'; // Reset

            }
            // Otherwise skip through until end of argument
            else
            {
                // printf("Skip: %c\n", *line);
                line++;
            }
        }
    }
    // Null terminate the argument list
    *av = (char *) '\0';

    // Process Args and replace if necessary
    char* homeDir = getenv("HOME"); // Get the home directory
    tildeFinder(argv, homeDir);

    // TODO: Variables, such as $(ENVVAR)

}