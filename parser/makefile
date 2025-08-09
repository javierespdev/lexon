# Makefile for Lexon parser and scanner

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

# Flex: Fast lexical analyzer generator
LEX = flex

# Bison: GNU parser generator (Yacc replacement)
YACC = bison

# Bison options:
# -d: Generate header file
# -t: Enable debugging traces
# -g: Generate a Graphviz .gv file for the grammar
YFLAGS = -d -t -g

# Object files to build
OBJECTS = $(NAME).tab.o lex.yy.o

# Project header dependencies
INCLUDES = ../error/error.hpp ../includes/macros.hpp \
	../table/table.hpp ../table/numericVariable.hpp \
	../table/init.hpp \
	../table/numericConstant.hpp \
	../table/builtinParameter1.hpp \
	../table/builtinParameter0.hpp ../table/builtinParameter2.hpp

#######################################################
# Main build rule: build all object files
all: $(OBJECTS)

#######################################################
# Build the lexical analyzer object file
lex.yy.o: lex.yy.c $(NAME).tab.h
	$(CPP) $(CFLAGS) -Wno-unused-function -Wno-sign-compare $<

# Generate the lexical analyzer source file
lex.yy.c: $(NAME).l $(NAME).tab.h $(INCLUDES)
	@echo "Generating: $@"
	@$(LEX) $<
	@echo

# Build the parser object file
$(NAME).tab.o: $(NAME).tab.c $(NAME).tab.h $(INCLUDES)
	@echo "Compiling: $<"
	@$(CPP) $(CFLAGS) $<
	@echo

# Generate the parser source and header files
$(NAME).tab.c $(NAME).tab.h: $(NAME).y $(INCLUDES)
	@echo "Generating: $(NAME).tab.c $(NAME).tab.h"
	@$(YACC) $(YFLAGS) $<
	@echo

#######################################################
# Generate the parser output file to show conflicts, if any
$(NAME).output: $(NAME).y $(INCLUDES)
	@echo "Generating: $@"
	@$(YACC) -v $<
	@echo

#######################################################
# Clean up all generated files in the parser directory
clean:
	@echo
	@echo "Deleting in subdirectory parser"
	@rm -f $(OBJECTS) $(NAME).tab.[ch] lex.yy.c $(NAME).gv $(NAME).dot $(NAME).output *~
	@echo