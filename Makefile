MKDIR_P = mkdir -p

# Directories
SRCDIR = src
BLDDIR = build

all: shell

shell: $(SRCDIR)/mrsh.c directories
	gcc -Wall -Wextra -o $(BLDDIR)/mrsh $(SRCDIR)/mrsh.c

directories:
	$(MKDIR_P) $(BLDDIR)

clean:
	rm -f $(BLDDIR)/mrsh
