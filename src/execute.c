/* strtol example */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* strtol */
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void execute(char **argv)
{
     pid_t  pid;
     if ((pid = fork()) < 0) {     /* fork a child process           */
          printf("*** ERROR: forking child process failed\n");
          exit(1);
     }
     else if (pid == 0) {          /* for the child process:         */
          if (execvp(*argv, argv) < 0) {     /* execute the command  */
               printf("*** ERROR: exec failed\n");
               exit(1);
          }
     }
     else {                                  /* for the parent:      */
          /* wait for completion  */
          int wc = wait(NULL); //is child finished?
          if (wc == -1)
          {
            printf("*** Error: wait failed");
            exit(1);
          }
     }
}