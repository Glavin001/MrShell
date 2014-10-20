#/bin/bash

echo "Lexing grammar"
lex -o shell.lex.yy.c shell.l

echo "Compiling Lex output"
cc shell.lex.yy.c -ll -o shell.out

echo "Done!"
