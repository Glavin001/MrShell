# Directories
SRCDIR = src
BLDDIR = build

all: $(SRCDIR)/mrsh.c
	gcc -Wall -Wextra -o $(BLDDIR)/mrsh $(SRCDIR)/mrsh.c

clean:
	rm -f $(BLDDIR)/mrsh
