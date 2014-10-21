# Directories
SRCDIR = src
BLDDIR = build

all: $(SRCDIR)/mrsh.c $(SRCDIR)/mrsh.h $(BLDDIR)/mrsh.lex.yy.c
	cc $(SRCDIR)/mrsh.c $(BLDDIR)/mrsh.lex.yy.c -ll -o $(BLDDIR)/mrsh

$(BLDDIR)/mrsh.lex.yy.c: $(SRCDIR)/mrsh.l
	lex -o $(BLDDIR)/mrsh.lex.yy.c $(SRCDIR)/mrsh.l

clean:
	rm -f $(BLDDIR)/mrsh
	rm -f $(BLDDIR)/mrsh.lex.yy.c
