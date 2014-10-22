/* strtol example */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* strtol */
#include <unistd.h>

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
  "An extreme shell for people who really know how to pipe.    \n";

// === Helpers ===
void printWelcome ()
{
  printf("%s", WELCOME_MESSAGE);
}

// === Main ===
/**
Start of program

@param argc argument count
@param argv argument vector
@return an integer indicating success or failure.
*/
int main (int argc, const char** argv)
{

  printWelcome();

  return 0;
}
