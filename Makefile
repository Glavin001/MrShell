#
# The following defines a variable named "program_NAME" with a value of "myprogram". By convention,
# a lowercase prefix (in this case "program") and an uppercased suffix (in this case "NAME"), separated
# by an underscore is used to name attributes for a common element. Think of this like
# using program.NAME, program.C_SRCS, etc. There are no structs in Make, so we use this convention
# to keep track of attributes that all belong to the same target or program.  
#
program_NAME := mrsh

MKDIR_P = mkdir -p

# Directories
SRCDIR = src
BLDDIR = build

# This is a list of all files in the current directory ending in ".c". The $(wildcard) is a globbing expression. This similar to how the shell expands *.c
program_C_SRCS := $(wildcard $(SRCDIR)/*.c)

# This is a list of all files in the current directory ending in ".cpp". The $(wildcard) is used to expand *.cpp to match all files ending in *.cpp in the current directory.
program_CXX_SRCS := $(wildcard *.cpp)

# This names all C object files that we are going to build. It uses a substitution expression, which simply replaces ".c" with ".o"
program_C_OBJS := ${program_C_SRCS:.c=.o}

# This names all C++ object files that we are going to build. It simply uses text substitution to replace ".cpp" with ".o" for all the ".cpp" source files.
program_CXX_OBJS := ${program_CXX_SRCS:.cpp=.o}

# This is simply a list of all the ".o" files, both from C and C++ source files.
program_OBJS := $(program_C_OBJS) $(program_CXX_OBJS)

# This is a place holder. If you used program_INCLUDE_DIRS := ./include, then headers in "./include" would be found with #include <>
program_INCLUDE_DIRS :=

# This is a place holder. If you used program_LIBRARY_DIRS := ./lib, then libraries in "./lib" would be found by the linker.
program_LIBRARY_DIRS :=

# This is a place holder. If you used program_LIBRARIES := boost_signals, then libboost_signals would be linked in.
program_LIBRARIES := readline


# This adds -I$(includedir) for every include directory given in $(program_INCLUDE_DIRS)... so if you used ./include, it would expand to -I./include
# Remember that CPPFLAGS is the C preprocessor flags, so anything that compiles a C or C++ source file into an object file will use this flag.
CPPFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))

# This adds -L$(librarydir) for every library directory given in $(program_LIBRARY_DIRS)... so if you used ./lib, it would expand to -L./lib
# Since the LDFLAGS are used when linking, this will cause the appropriate flags to be passed to the linker.
LDFLAGS += $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))

# This adds -l$(library) for every library given in $(program_LIBRARIES), so if you used boost_signals, it would expand to -lboost_signals
LDFLAGS += $(foreach library,$(program_LIBRARIES),-l$(library))

# This indicates that "all", "clean", and "distclean" are "phony targets". Therefore, "make all", "make clean", and "make distclean"
# should execute the content of their build rules, even if a newer file named "all", "clean", or "distclean" exists.
.PHONY: all clean distclean

# This is first build rule in the makefile, and so executing "make" and executing "make all" are the same.
# The target simply depends on $(program_NAME), which expands to "myprogram", and that target is given below:
all: $(program_NAME)

#
# The program depends on the object files (which are automatically built using the predefined build rules... nothing needs to be given explicitly for them).
# The build rule $(LINK.cc) is used to link the object files and output a file with the same name as the program. Note that LINK.cc makes use of CXX,
# CXXFLAGS, LDFLAGS, etc. On my own system LINK.cc is defined as: $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH),
# so if CXXFLAGS, CPPFLAGS, LDFLAGS, and TARGET_ARCH are undefined, but CXX is g++, then it will expand to g++ $(program_OBJS) -o $(program_NAME).
#
$(program_NAME): $(program_OBJS) directories
	$(LINK.cc) $(program_OBJS) -o $(BLDDIR)/$(program_NAME)

# Note that the line that starts with $(LINK.cc) is indented with a single tab. This is very important! Otherwise, it will not work.

directories:
	$(MKDIR_P) $(BLDDIR)

#
# This target removes the built program and the generated object files. The @ symbol indicates that the line should be run silently, and the -
# symbol indicates that errors should be ignored (i.e., if the file already doesn't exist, we don't really care, and we should continue executing subsequent commands)
#
clean:
	@- $(RM) $(BLDDIR)/$(program_NAME)
	@- $(RM) -r $(BLDDIR)
	@- $(RM) $(program_OBJS)


#
# The distclean target depends on the clean target (so executing distclean will cause clean to be executed), but we don't add anything else.
#
distclean: clean