# Makefile for Lexon main program and modules

NAME=interpreter

# C++ compiler
CPP = g++

# Compiler flags:
# -c: Compile only, do not link
# -g: Debug info
# -Wall: Enable all warnings
# -ansi: Use ANSI standard
# -O2: Optimization level 2
CFLAGS = -c -g -Wall -ansi -O2

# Flex library for lexical analysis
LFLAGS = -lfl

# Object files for main and modules
OBJECTS = $(NAME).o includes/globals.o
OBJECTS-PARSER = parser/*.o
OBJECTS-ERROR = error/*.o
OBJECTS-TABLE = table/*.o
OBJECTS-AST = ast/*.o

# Project header dependencies
INCLUDES = ./parser/interpreter.tab.h ./error/error.hpp \
	./table/table.hpp ./includes/globals.hpp \
	./table/init.hpp \
	./ast/ast.hpp

# Predefined macros:
# $@: target name
# $^: all dependencies
# $<: first dependency

#######################################################
# Main build rule: build the executable and all modules
$(NAME).exe : parser-dir error-dir table-dir ast-dir $(OBJECTS)
	@echo "Generating $(NAME).exe"
	@$(CPP) $(OBJECTS) $(OBJECTS-PARSER) $(OBJECTS-ERROR) $(OBJECTS-TABLE) $(OBJECTS-AST) \
	$(LFLAGS) -o $(NAME).exe

# Compile the main program
$(NAME).o: $(NAME).cpp parser-dir ast-dir $(INCLUDES)
	@echo "Compiling $<"
	@$(CPP) $(CFLAGS) $<
	@echo

# Build parser module
parser-dir:
	@echo "Accessing directory parser"
	@echo
	@make -C parser/
	@echo

# Build error module
error-dir:
	@echo "Accessing directory error"
	@echo
	@make -C error/
	@echo

# Build table module
table-dir:
	@echo "Accessing directory table"
	@echo
	@make -C table/
	@echo

# Build AST module
ast-dir:
	@echo "Accessing directory ast"
	@echo
	@make -C ast/
	@echo

#######################################################
# Generate parser output file (for conflict analysis)
$(NAME).output:
	@echo "Generating: $@"
	@make -C parser/ $@
	@echo

#######################################################
# Generate documentation using Doxygen
# Requires a Doxyfile in the project root
# Output will be in the html/ directory
# Usage: make doc

doc: Doxyfile
	doxygen

#######################################################
# Clean up all generated files and directories
clean:
	@echo "Deleting html"
	@rm -rf html
	@echo "Deleting $(OBJECTS) $(NAME).exe *~"
	@rm -f $(OBJECTS) $(NAME).exe *~
	@echo
	@make -C parser/ clean
	@echo
	@make -C error/ clean
	@echo
	@make -C table/ clean
	@echo
	@make -C ast/ clean
	@echo