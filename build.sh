#/bin/bash

echo "Lexing grammar"
lex -o mrsh.lex.yy.c mrsh.l

echo "Compiling Lex output"
cc mrsh.lex.yy.c -ll -o mrsh.out

echo "Cleaning up"
rm mrsh.lex.yy.c

echo "Done!"
return 0;
