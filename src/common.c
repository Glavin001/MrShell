#include <stdio.h>   // printf
#include <string.h>
#include <ctype.h>
#include "welcome.h" // welcome screen constants
#include "chalk.h"   // color constants

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