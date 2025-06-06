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
        yyin = fopen(argv[1], "r");
        fileName = argv[1];
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
    else
    {
        interactiveMode = true;
        std::string block, line;
        bool esperando_bloque = false;
        while (true) {
            std::cout << (block.empty() ? "> " : (esperando_bloque ? "| " : "> "));
            if (!std::getline(std::cin, line)) break;
            if (line.empty() && block.empty()) continue;

            if (!block.empty()) block += "\n";
            block += line;
            currentInteractiveLine = block;
            sourceLines.push_back(line); // Guarda solo la línea actual para historial

            // Detecta si estamos esperando un bloque (switch, if, while, for, repeat, {)
            if ((block.find("switch") != std::string::npos && line != "end_switch") ||
                (block.find("if") != std::string::npos && line != "end_if") ||
                (block.find("while") != std::string::npos && line != "end_while") ||
                (block.find("for") != std::string::npos && line != "end_for") ||
                (block.find("repeat") != std::string::npos && line != "until") ||
                (block.find("{") != std::string::npos && line != "}") ) {
                esperando_bloque = true;
            }
            // Si la línea actual es un cierre de bloque, ya puedes parsear
            if (line == "end_switch" || line == "end_if" || line == "end_while" ||
                line == "end_for" || line == "until" || line == "}") {
                esperando_bloque = false;
            }

            if (!esperando_bloque) {
                YY_BUFFER_STATE buffer = yy_scan_string((block + "\n").c_str());
                yyparse();
                yy_delete_buffer(buffer);
                block.clear();
            }
        }
        return 0;
    }

    return 0;
}