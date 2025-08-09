/*! 
  \file interpreter.cpp
  \brief Main program
*/

/*!
 \mainpage Flex and Bison: example 17
 \author   
 \date     2018 - 4 - 26
 \version  1.0
 \note Novelties
	+ AST: intermidiate code
	+ New statements: if, while, block
*/




#include <stdio.h>
#include <string>

//

/////////////////////////////
/* 
  AST class
  IMPORTANT: must be written before interpreter.tab.h
*/
#include "ast/ast.hpp"
#include "includes/globals.hpp"
////////////////////////////////////////

#include "./parser/interpreter.tab.h"

int control = 0; //!< To control the interactive mode in "if" and "while" sentences 

std::string progname; //!<  Program name

typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(const char *str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

//


//////////////////////////////////////////////

// Use for recovery of runtime errors 
#include <setjmp.h>
#include <signal.h>

// Error recovery functions 
#include "error/error.hpp"


lp::AST *root; //!< Root of the abstract syntax tree AST
///////////////////////////////////////////// 

//////////////////////////////////////////////

#include "table/init.hpp"


/*
 jhmp_buf
    This is an array type capable of storing the information of a calling environment to be restored later.
   This information is filled by calling macro setjmp and can be restored by calling function longjmp.
*/
extern jmp_buf begin; //!<  It enables recovery of runtime errors 

//////////////////////////////////////////////

#include "table/table.hpp"

lp::Table table; //!< Table of Symbols



// cout.precision
#include <iostream>
#include <fstream>
//////////////////////////////////////////////////

//! \name Main program

/*! 
	\brief  Main function
	\param  argc: number of command line parameters
	\param  argv: values of command line parameters
	\return int
	\note   C++ requires that main returns an int value
	\sa     yyparse, yylex
*/
int main(int argc, char *argv[])
{
    yydebug = 0;

    // Copy the name of the interpreter 
    progname = argv[0];

    // Number of decimal places
    std::cout.precision(7);

    // Table of symbols initialization
    init(table);

    // Sets a viable state to continue after a runtime error
    setjmp(begin);

    // The name of the function to handle floating-point errors is set
    signal(SIGFPE, fpecatch);

    if (argc == 2) 
    {
        std::string filename = argv[1];

        if (filename.size() < 3 || filename.substr(filename.size() - 2) != ".p") {
            std::cerr << "Error: The input file must have a '.p' extension." << std::endl;
            return 1;
        }

        yyin = fopen(argv[1], "r");

        if (!yyin) {
            std::cerr << "Error: The file '" << argv[1] << "' does not exist or cannot be opened." << std::endl;
            return 1;
        }

        interactiveMode = false;

        std::ifstream file(argv[1]);
        std::string line;
        while (std::getline(file, line)) {
            sourceLines.push_back(line);
        }
        file.close();

        yyparse();

        if (root != NULL) {
            // root->printAST();
            root->evaluate();
        }
    }
    else if (argc == 1)
    {
        interactiveMode = true;
        yyparse();
    }
    else
    {
        std::cerr << "Usage: " << progname << " [input_file.p]" << std::endl;
        std::cerr << "Run as './interpreter.exe' for interactive mode or './interpreter.exe <file.p>' to execute a program file." << std::endl;
    }

    return 0;
}