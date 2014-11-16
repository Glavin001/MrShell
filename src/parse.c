#include <stdio.h>      /* printf */

void parse(char *line, char **argv)
{
    while (*line != '\0')         /* if not the end of line ....... */
    {
        // printf("Line before : %s\n", line);
        while (*line == ' ' || *line == '\t' || *line == '\n') {
            // printf("Replace white space: %c\n", *line);
            *line++ = '\0';     /* replace white spaces with 0    */
        }
        // printf("Line after: %s\n", line);
        *argv++ = line;          /* save the argument position     */
        while (*line != '\0' && *line != ' ' &&
                *line != '\t' && *line != '\n') {
            if (*line == '\\') {
                // printf("Skip backslash: %c\n", *line);
                // printf("Ignoring next character: %c\n", *(line+1));
                // Rotation String Left and remove the backslash
                char *c = line;
                while (*c != '\0') 
                {
                    *c = *(c+1);
                    c++;
                }
                line++; // Skip the next character
            } else {
                // printf("Skip: %c\n", *line);
                line++;             /* skip the argument until ...    */
            }
        }
    }
    *argv = (char *) '\0';                 /* mark the end of argument list  */
}