#include <stdio.h>      /* printf */

#include "constants.h"
#include "chalk.h"

// === Helpers ===
void printWelcome ()
{
  printf("%s%s%s", KYELLOW, WELCOME_MESSAGE, KNORMAL);
}

// void log(char *msg, int level)
// {
//     char *msgColour;
//     if (level > 0) {
//         msgColour = KRED;
//     } else {
//         msgColour = KNORMAL;
//     }
//     printf("-mrsh: %s%s%s", msgColour, msg, KNORMAL);
// }