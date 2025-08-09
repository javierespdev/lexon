# Makefile for Lexon error module

NAME=error

# C++ compiler
CPP = g++

# Compiler flags:
# -c: Compile only, do not link
# -g: Debug info
# -Wall: Enable all warnings
# -ansi: Use ANSI standard
# -O2: Optimization level 2
CFLAGS = -c -g -Wall -ansi -O2

# Object files to build
OBJECTS = $(NAME).o

# Project header dependencies
INCLUDES = $(NAME).hpp ../includes/macros.hpp

# Predefined macros:
# $@: target name
# $^: all dependencies
# $<: first dependency

#######################################################
# Main build rule: build all object files
all: $(OBJECTS)

#######################################################
# Build the error recovery object file
$(NAME).o: $(NAME).cpp $(INCLUDES)
	@echo "Compiling $<"
	@$(CPP) $(CFLAGS) $<
	@echo

#######################################################
# Clean up all generated files in the error directory
clean:
	@echo
	@echo "Deleting in subdirectory error"
	@rm -f $(OBJECTS) *~
	@echo