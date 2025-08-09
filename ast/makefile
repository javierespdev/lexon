# Makefile for Lexon AST module

NAME=ast

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
INCLUDES = $(NAME).hpp \
	../parser/interpreter.tab.h \
	../includes/macros.hpp ../error/error.hpp \
	../table/table.hpp ../table/numericConstant.hpp \
	../table/builtinParameter0.hpp ../table/builtinParameter1.hpp ../table/builtinParameter2.hpp

# Predefined macros:
# $@: target name
# $^: all dependencies
# $<: first dependency

#######################################################
# Main build rule: build all object files
all: $(OBJECTS)

#######################################################
# Build the AST object file
$(NAME).o: $(NAME).cpp $(INCLUDES)
	@echo "Compiling $<"
	@$(CPP) $(CFLAGS) $<
	@echo

#######################################################
# Clean up all generated files in the ast directory
clean:
	@echo
	@echo "Deleting in subdirectory ast"
	@rm -f $(OBJECTS) *~
	@echo