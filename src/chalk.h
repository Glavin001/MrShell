#ifndef CHALK_H_INCLUDED
#define CHALK_H_INCLUDED
/* ^^ these are the include guards */

/*
ASCII styles are taken from
https://github.com/sindresorhus/ansi-styles/blob/master/index.js
More info
http://en.wikipedia.org/wiki/ANSI_escape_code#Colors
*/
#define KRESET "\033[0m"

// Colours
#define KNORMAL  "\x1B[0m"
#define KRESETCOLOR "\x1B[39m"
#define KBLACK "\x1B[30m"
#define KRED  "\x1B[31m"
#define KGREEN  "\x1B[32m"
#define KYELLOW  "\x1B[33m"
#define KBLUE  "\x1B[34m"
#define KMAGENTA  "\x1B[35m"
#define KCYAN  "\x1B[36m"
#define KWHITE  "\x1B[37m"
#define KGRAY "\x1B[90m"

// Backgrounds
#define KRESETBG "\x1B[49m"
#define KBLACKBG "\x1B[40m"
#define KREDBG "\x1B[41m"
#define KGREENBG "\x1B[42m"
#define KYELLOWBG "\x1B[43m"
#define KBLUEBG "\x1B[44m"
#define KMAGENTABG "\x1B[45m"
#define KCYANBG "\x1B[46m"
#define KWHITEBG "\x1B[47m"

// Styles
#define KRESETBOLD "\x1B[22m"
#define KBOLD "\x1B[1m"

#define KRESETDIM "\x1B[22m"
#define KDIM "\x1B[2m"

#define KRESETITALIC "\x1B[23m"
#define KITALIC "\x1B[3m"

#define KRESETUNDERLINE "\x1B[24m"
#define KUNDERLINE "\x1B[4m"

#define KRESETINVERSE "\x1B[27m"
#define KINVERSE "\x1B[7m"

#define KRESETHIDDEN "\x1B[28m"
#define KHIDDEN "\x1B[1m"

#define KRESETSTRIKETHROUGH "\x1B[29m"
#define KSTRIKETHROUGH "\x1B[1m"

#endif
