#include <stdio.h>      /* printf */

#include "constants.h"
#include "chalk.h"

// === Helpers ===
void printWelcome ()
{
  printf("%s%s%s", KYELLOW, WELCOME_MESSAGE, KNORMAL);
}
