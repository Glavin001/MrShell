#include <stdio.h>   // printf
#include <string.h>
#include <ctype.h>
#include <stdlib.h>  // exit
#include <unistd.h>  // fork, wait, execvp, chdir, pid_t

#include "welcome.h" // welcome screen constants
#include "chalk.h"   // color constants
#include "execute.h"
#include "parse.h"

// === Helpers ===
void printWelcome ()
{
    printf("%s%s%s", KYELLOW, WELCOME_L1_Y, KNORMAL);
    printf("%s%s%s", KBLUE, WELCOME_L1_B, KNORMAL);
    printf("%s%s%s", KCYAN, WELCOME_L1_C, KNORMAL);
    printf("%s%s%s", KWHITE, WELCOME_L1_W, KNORMAL);

    printf("%s%s%s", KRED, WELCOME_L2_R, KNORMAL);
    printf("%s%s%s", KGREEN, WELCOME_L2_G, KNORMAL);
    printf("%s%s%s", KYELLOW, WELCOME_L2_Y, KNORMAL);
    printf("%s%s%s", KBLUE, WELCOME_L2_B, KNORMAL);
    printf("%s%s%s", KMAGENTA, WELCOME_L2_M, KNORMAL);
    printf("%s%s%s", KCYAN, WELCOME_L2_C, KNORMAL);
    printf("%s%s%s", KWHITE, WELCOME_L2_W, KNORMAL);
    
    printf("%s%s%s", KRED, WELCOME_L3_R, KNORMAL);
    printf("%s%s%s", KGREEN, WELCOME_L3_G, KNORMAL);
    printf("%s%s%s", KYELLOW, WELCOME_L3_Y, KNORMAL);
    printf("%s%s%s", KBLUE, WELCOME_L3_B, KNORMAL);
    printf("%s%s%s", KMAGENTA, WELCOME_L3_M, KNORMAL);
    printf("%s%s%s", KCYAN, WELCOME_L3_C, KNORMAL);
    printf("%s%s%s", KWHITE, WELCOME_L3_W, KNORMAL);
    
    printf("%s%s%s", KRED, WELCOME_L4_R, KNORMAL);
    printf("%s%s%s", KGREEN, WELCOME_L4_G, KNORMAL);
    printf("%s%s%s", KYELLOW, WELCOME_L4_Y, KNORMAL);
    printf("%s%s%s", KBLUE, WELCOME_L4_B, KNORMAL);
    printf("%s%s%s", KMAGENTA, WELCOME_L4_M, KNORMAL);
    printf("%s%s%s", KCYAN, WELCOME_L4_C, KNORMAL);
    printf("%s%s%s", KWHITE, WELCOME_L4_W, KNORMAL);
    
    printf("%s%s%s", KRED, WELCOME_L5_R, KNORMAL);
    printf("%s%s%s", KGREEN, WELCOME_L5_G, KNORMAL);
    printf("%s%s%s", KYELLOW, WELCOME_L5_Y, KNORMAL);
    printf("%s%s%s", KBLUE, WELCOME_L5_B, KNORMAL);
    printf("%s%s%s", KMAGENTA, WELCOME_L5_M, KNORMAL);
    printf("%s%s%s", KCYAN, WELCOME_L5_C, KNORMAL);
    printf("%s%s%s", KWHITE, WELCOME_L5_W, KNORMAL);
    
    printf("%s%s%s", KRED, WELCOME_L6_R, KNORMAL);
    printf("%s%s%s", KGREEN, WELCOME_L6_G, KNORMAL);
    printf("%s%s%s", KYELLOW, WELCOME_L6_Y, KNORMAL);
    printf("%s%s%s", KBLUE, WELCOME_L6_B, KNORMAL);
    printf("%s%s%s", KMAGENTA, WELCOME_L6_M, KNORMAL);
    printf("%s%s%s", KCYAN, WELCOME_L6_C, KNORMAL);
    printf("%s%s%s", KWHITE, WELCOME_L6_W, KNORMAL);
    
    printf("%s%s%s", KRED, WELCOME_L7_R, KNORMAL);
    printf("%s%s%s", KGREEN, WELCOME_L7_G, KNORMAL);
    printf("%s%s%s", KYELLOW, WELCOME_L7_Y, KNORMAL);
    printf("%s%s%s", KBLUE, WELCOME_L7_B, KNORMAL);
    printf("%s%s%s", KMAGENTA, WELCOME_L7_M, KNORMAL);
    printf("%s%s%s", KCYAN, WELCOME_L7_C, KNORMAL);
    printf("%s%s%s", KWHITE, WELCOME_L7_W, KNORMAL);

    printf("%s", WELCOME_BLANK);
    
    printf("%s%s%s", KRED, WELCOME_L9_R, KNORMAL);
    printf("%s%s%s", KGREEN, WELCOME_L9_G, KNORMAL);
    printf("%s%s%s", KYELLOW, WELCOME_L9_Y, KNORMAL);
    printf("%s%s%s", KBLUE, WELCOME_L9_B, KNORMAL);
    printf("%s%s%s", KMAGENTA, WELCOME_L9_M, KNORMAL);
    printf("%s%s%s", KCYAN, WELCOME_L9_C, KNORMAL);
    printf("%s%s%s", KWHITE, WELCOME_L9_W, KNORMAL);

    printf("%s", WELCOME_BLANK);

    printf("%s%s%s", KRED, WELCOME_L11_R, KNORMAL);
    printf("%s%s%s", KGREEN, WELCOME_L11_G, KNORMAL);
    printf("%s%s%s", KYELLOW, WELCOME_L11_Y, KNORMAL);
    printf("%s%s%s", KBLUE, WELCOME_L11_B, KNORMAL);
    printf("%s", WELCOME_BLANK);
    printf("%s%s%s", KMAGENTA, WELCOME_L13_M, KNORMAL);
    printf("%s%s%s", KCYAN, WELCOME_L13_C, KNORMAL);
    printf("%s%s%s", KWHITE, WELCOME_L13_W, KNORMAL);
    printf("%s%s%s", KRED, WELCOME_L13_R, KNORMAL);
    printf("%s%s%s", KGREEN, WELCOME_L13_G, KNORMAL);
    printf("%s%s%s", KYELLOW, WELCOME_L13_Y, KNORMAL);
    printf("%s%s%s", KBLUE, WELCOME_L13_B, KNORMAL);

    printf("%s", WELCOME_BLANK);

    printf("%s%s%s", KRED, WELCOME_L15_R, KNORMAL);
    printf("%s%s%s", KGREEN, WELCOME_L15_G, KNORMAL);
    printf("%s%s%s", KYELLOW, WELCOME_L15_Y, KNORMAL);
    printf("%s%s%s", KBLUE, WELCOME_L15_B, KNORMAL);
    printf("%s%s%s", KMAGENTA, WELCOME_L15_M, KNORMAL);
    printf("%s%s%s", KCYAN, WELCOME_L15_C, KNORMAL);
    printf("%s%s%s", KWHITE, WELCOME_L15_W, KNORMAL);
}

// Note: This function returns a pointer to a substring of the original string.
// If the given string was allocated dynamically, the caller must not overwrite
// that pointer with the returned value, since the original pointer must be
// deallocated using the same allocator with which it was allocated.  The return
// value must NOT be deallocated using free() etc.
// Source: http://stackoverflow.com/a/122721/2578205
char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace(*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace(*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;
}

int getCurrentGitBranch(char *buff)
{
    char *cmd = "git symbolic-ref --short -q HEAD";
    char *cmdv[6];

    parse(cmd, cmdv); /* parse the line */

    // fprintf(stderr, "Cmd: '%s %s'\n", cmdv[0], cmdv[1]);

    // Create pipe file descriptors
    int fdIn[2]; // [read, write]
    int fdOut[2]; // [read, write]

    // Create pipe, check for failure
    if (pipe(fdIn) < 0) 
    { 
        perror("Pipe fdIn Failed"); 
        exit(1); 
    }
    // Create pipe, check for failure
    if (pipe(fdOut) < 0) 
    { 
        perror("Pipe fdOut Failed"); 
        exit(1);
    }

    execCmd(cmdv, fdIn, fdOut, false);

    // The Output of this executionTree should go to stdout
    close(fdOut[1]);    /* close write end of pipe               */
    close(fdIn[1]);    /* close write end of pipe               */
    
    int nbytes = read(fdOut[0], buff, sizeof(buff));
    
    close(fdOut[0]);    /* close read end of pipe               */
    close(fdIn[0]);    /* close read end of pipe               */
    
    // printf("Current Git Branch Befor: '%s' '%i'\n", buff, nbytes);
    trimwhitespace(buff);

    // This fixes an error where it returns
    // a branch with a space and a trailing character that
    // breaks the terminal
    // and causes segfaults.
    // This will fillin NULL character for every character
    // after a space, etc.
    char *p = buff;
    // While not the end of line
    bool foundSpace = false;
    while (*p != '\0')
    {
        // printf("Top of while loop\n");
        
        // While there are spaces, tabs or new lines replace with null
        // printf("Line before nested while loop 1: %s\n", p);
        if (foundSpace || *p == ' ' || *p == '\t' || *p == '\n') 
        {
            // printf("Replace space, tab, or new line: %c\n", *p);
            *p++ = '\0';
            foundSpace = true;
        }
        // printf("Line after nested while loop 1: %s\n", p);
        p++;
    }

    // printf("Current Git Branch After: '%s' '%i'\n", buff, nbytes);

    return nbytes;
}