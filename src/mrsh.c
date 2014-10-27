/* strtol example */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* strtol */
#include <unistd.h>
#include <string.h>
#include <pthread.h>


const char *WELCOME_MESSAGE =
"                     ____     __               ___    ___     \n"
" /'\\_/`\\            /\\  _`\\  /\\ \\             /\\_ \\  /\\_ \\      \n"
"/\\      \\   _ __    \\ \\,\\L\\_\\\\ \\ \\___       __\\//\\ \\ \\//\\ \\     \n"
"\\ \\ \\__\\ \\ /\\`'__\\   \\/_\\__ \\ \\ \\  _ `\\   /'__`\\\\ \\ \\  \\ \\ \\    \n"
" \\ \\ \\_/\\ \\\\ \\ \\/      /\\ \\L\\ \\\\ \\ \\ \\ \\ /\\  __/ \\_\\ \\_ \\_\\ \\_  \n"
"  \\ \\_\\\\ \\_\\\\ \\_\\      \\ `\\____\\\\ \\_\\ \\_\\\\ \\____\\/\\____\\/\\____\\ \n"
"   \\/_/ \\/_/ \\/_/       \\/_____/ \\/_/\\/_/ \\/____/\\/____/\\/____/ \n"
"                                                                \n"
"    0100110101110010 0101001101101000011001010110110001101100  \n"
"\n"
"                 Created by the Pipe Brothers                  \n"
"\n"
"An extreme shell for people who really know how to pipe.    \n"
"\n"
"=============================================================\n"
"\n";


// === Structs ===
// struct commandArgs {
//     int argc;
//     //const char **argv;
//     char *argv[64];
// };

// === Helpers ===
void printWelcome ()
{
  printf("%s", WELCOME_MESSAGE);
}

void parse(char *line, char **argv)
{
     while (*line != '\0') {       /* if not the end of line ....... */ 
          while (*line == ' ' || *line == '\t' || *line == '\n')
               *line++ = '\0';     /* replace white spaces with 0    */
          *argv++ = line;          /* save the argument position     */
          while (*line != '\0' && *line != ' ' && 
                 *line != '\t' && *line != '\n') 
               line++;             /* skip the argument until ...    */
     }
     *argv = (char *) '\0';                 /* mark the end of argument list  */
}

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

// void *execute(void *cmd_void_ptr)
// {
//     // struct commandArgs *cmd = (struct commandArgs *)cmd_void_ptr;
//     // char **argv = cmd->argv;
//     char **argv = (char **) cmd_void_ptr;
//     printf("Command: %s\n", argv[0]);
//     if (execvp(*argv, argv) < 0) {     
//         /* execute the command  */
//         printf("*** ERROR: exec failed\n");
//         exit(1);
//     }
//     return 0;
// }


// === Main ===
/**
Start of program

@param argc argument count
@param argv argument vector
@return an integer indicating success or failure.
*/
int main (void) //(int argc, const char** argv)
{

  printWelcome();

  char  line[1024];             /* the input line                 */
  char  *argv[64];              /* the command line argument      */
  // struct commandArgs cmd;
  // pthread_t run_thread;

  while(1) 
  {

      printf("MrShell$ ");     /*   display a prompt             */
      if ( fgets(line, sizeof(line), stdin) ) /*   read in the command line     */
        {
            size_t len = strlen(line);
            if (len != 0 && line[len-1] == '\n')
                line[--len] = '\0';
            // printf("%s\n", line);
        }
      //printf("Line: %s\n", line);
      parse(line, argv);       /*   parse the line              */
      //printf("Argv: %s\n", argv[0]);
      if (strcmp(argv[0], "exit") == 0)  /* is it an "exit"?     */
      {
           exit(0);            /*   exit if it is                */
      } else if (strcmp(line, "") == 0)
      {
        printf("...\n");
      }
      else {
          execute(argv);           /* otherwise, execute the command */
      }
      // /* create a second thread which executes inc_x(&x) */
      // if(pthread_create(&run_thread, NULL, execute, (void *)argv))
      // {
      //   fprintf(stderr, "Error creating thread\n");
      //   return 1;
      // }

      // /* wait for the second thread to finish */
      // if(pthread_join(run_thread, NULL)) 
      // {
      //   fprintf(stderr, "Error joining thread\n");
      //   return 2;
      // }

      printf("\n");

  }

  printf("\nGoodbye!\n");

  return 0;
}
