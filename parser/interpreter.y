/*!
    * \file interpreter.y
    * \brief Grammar and parser rules for the Lexon interpreter.
    *
    * This file defines the context-free grammar, semantic actions, and AST construction
    * for the Lexon language. It handles control flow, expressions, assignments, I/O,
    * and error recovery, building the abstract syntax tree (AST) for execution.
    *
    * \author Lexon Project
    * \date 2025-06-06
 */

%{

/* Standard libraries */
#include <iostream>
#include <string>

/* Math library */
#include <math.h>

/* Recovery of runtime errors */
#include <setjmp.h>
#include <signal.h>

/* Error recovery functions */
#include "../error/error.hpp"

/* Macros for the screen */
#include "../includes/macros.hpp"

/* AST class */
#include "../ast/ast.hpp"

/* Table of symbol */
#include "../table/table.hpp"
#include "../table/numericVariable.hpp"
#include "../table/logicalVariable.hpp"
#include "../table/numericConstant.hpp"
#include "../table/logicalConstant.hpp"
#include "../table/builtinParameter1.hpp"
#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter2.hpp"
#include "../table/init.hpp"

/*! 
    \brief  Lexical or scanner function
    \return int
    \note   C++ requires that yylex returns an int value
    \sa     yyparser
*/
int yylex();

extern int lineNumber; //!< External line counter

extern bool interactiveMode; //!< Control the interactive mode of execution of the interpreter

extern int control; //!< External: to control the interactive mode in "if" and "while" sentences 

extern std::string progname; //!<  Program name

extern int yylineno;

/*
    This is an array type capable of storing the information of a calling environment to be restored later.
    This information is filled by calling macro setjmp and can be restored by calling function longjmp.
*/
jmp_buf begin; //!<  It enables recovery of runtime errors 

extern lp::Table table; //!< Extern Table of Symbols

extern lp::AST *root; //!< External root of the abstract syntax tree AST

%}

/*
 * In case of a syntactic error, more information is shown
 */
%define parse.error verbose

/*
 * Initial grammar symbol
 */
%start program

/*
 * Data type YYSTYPE: defines the types for semantic values used in the grammar.
 */
%union {
  double number;              //!< Numeric values
  char * string;              //!< String values
  bool logic;                 //!< Boolean values
  lp::ExpNode *expNode;       //!< Expression nodes
  std::list<lp::ExpNode *>  *parameters; //!< List of expression nodes
  std::list<lp::Statement *> *stmts;     //!< List of statement nodes
  lp::Statement *st;         //!< Statement node
  lp::AST *prog;             //!< Program (AST root)
  lp::CaseStmt * caseStm;    //!< Case statement node
  std::list<lp::CaseStmt *> *caselistStm; //!< List of case statements
}

%locations

/*
 * Type declarations for non-terminal symbols
 */
%type <expNode> exp cond
%type <parameters> listOfExp  restOfListOfExp
%type <stmts> stmtlist
%type <st> stmt asgn print read if while block repeat for place switch
%type <prog> program
%type <caseStm> case
%type <caselistStm> caselist

/* Tokens for control flow constructs */
%token IF ELSE WHILE FOR REPEAT UNTIL SWITCH CASE DEFAULT END_SWITCH
%token THEN END_IF DO END_WHILE
%token END_FOR FROM STEP TO

/* Tokens for input/output operations */
%token PRINT READ READ_STRING

/* Tokens for block delimiters and separators */
%token LETFCURLYBRACKET RIGHTCURLYBRACKET SEMICOLON COLON COMMA

/* Tokens for screen control / positioning */
%token CLEAR_SCREEN PLACE

/* Tokens for mathematical functions */
%token RANDOM

/* Tokens with semantic values */
%token <number> NUMBER         /* Numeric literals */
%token <string> STRING         /* Strings literals */
%token <logic> BOOL            /* Boolean literals */
%token <string> VARIABLE       /* Variable identifiers */
%token <string> UNDEFINED      /* Undefined identifiers */
%token <string> CONSTANT       /* Constant values */
%token <string> BUILTIN        /* Builtin function names */

/* Operator precedences and associativity */
%right ASSIGNMENT              /* Assignment operator (=) */
%left OR                       /* Logical OR */
%left AND                      /* Logical AND */

/* Relational operators */
%nonassoc GREATER_OR_EQUAL LESS_OR_EQUAL GREATER_THAN LESS_THAN EQUAL NOT_EQUAL

/* Logical NOT operator */
%left NOT

 /* Addition and subtraction */
%left PLUS MINUS

/* Multiplication, division, modulo, integer division, concatenation */
%left MULTIPLICATION DIVISION MODULO INTEGER_DIVISION CONCATENATION

/* Parentheses */
%left LPAREN RPAREN

/* Unary operators */
%nonassoc UNARY

/* Exponentiation */
%right POWER

%%
//!
//! \name Grammar rules
//!

program : stmtlist
          { 
            // Create a new AST from the list of statements
            $$ = new lp::AST($1); 
            // Assign the AST to the root pointer
            root = $$; 
            // End of parsing
          }
;

stmtlist:
    /* Empty: epsilon rule */
    { 
      // Create an empty list of statements
      $$ = new std::list<lp::Statement *>(); 
    }
  | stmtlist stmt 
    { 
      // Add the new statement to the list
      $$ = $1;
      $$->push_back($2);
      // If in interactive mode, evaluate statements immediately
      if (interactiveMode == true && control == 0)
      {
        for(std::list<lp::Statement *>::iterator it = $$->begin(); it != $$->end(); it++)
        {
          (*it)->evaluate();
        }
        // Clear the AST code, as it has already run in interactive mode
        $$->clear();
      }
    }
  | stmtlist error 
    { 
      // On error, just copy up the statement list
      $$ = $1;
      // Discard the previous look-ahead token
      yyclearin; 
    }
;

stmt:
    SEMICOLON
      {
        // Empty statement: ";"
        // Update lineNumber for error control
        lineNumber = @1.first_line;
        // Create a new empty statement node
        $$ = new lp::EmptyStmt(lineNumber); 
      }
    | asgn SEMICOLON
      {
        // Assignment statement
        lineNumber = @1.first_line;
      }
    | print SEMICOLON
      {
        // Print statement
        lineNumber = @1.first_line;
      }
    | read SEMICOLON
      {
        // Read statement
        lineNumber = @1.first_line;
      }
    | if
      {
        // If statement
        lineNumber = @1.first_line;
      }
    | while
      {
        // While statement
        lineNumber = @1.first_line;
      }
    | repeat
      {
        // Repeat statement
        lineNumber = @1.first_line;
      }
    | for
      {
        // For statement
        lineNumber = @1.first_line;
      }
    | block
      {
        // Block statement
        lineNumber = @1.first_line;
      }
    | CLEAR_SCREEN SEMICOLON
      {
        // Clear screen statement
        lineNumber = @1.first_line;
        $$ = new lp::ClearScreenStmt();
      }
    | place SEMICOLON
      {
        // Place statement
        lineNumber = @1.first_line;
        $$ = $1;
      }
    | switch SEMICOLON
      {
        // Switch statement
        lineNumber = @1.first_line;
      }
;

block: LETFCURLYBRACKET stmtlist RIGHTCURLYBRACKET
        {
            // Block of statements delimited by curly brackets
            lineNumber = @1.first_line;
            $$ = new lp::BlockStmt($2, lineNumber);
        }
;

controlSymbol:
    /* Epsilon rule for controlling interactive mode in if/while */
    {
        control++;
    }
;

if:
    IF controlSymbol cond THEN stmtlist END_IF
    {
        // If statement without else
        lineNumber = @1.first_line;
        $$ = new lp::IfStmt($3, $5, lineNumber);
        control--;
    }
  | IF controlSymbol cond THEN stmtlist ELSE stmtlist END_IF
    {
        // If-else statement
        lineNumber = @1.first_line;
        $$ = new lp::IfStmt($3, $5, $7, lineNumber);
        control--;
    }
;

place:
    PLACE LPAREN exp COMMA exp RPAREN
    {
        // Place statement for screen positioning
        lineNumber = @1.first_line;
        $$ = new lp::PlaceStmt($3, $5, lineNumber);
    }
;

while: WHILE controlSymbol cond DO stmtlist END_WHILE
    {
        // While loop
        lineNumber = @1.first_line;
        $$ = new lp::WhileStmt($3, $5, lineNumber);
        control--;
    }
;

repeat: REPEAT controlSymbol stmtlist UNTIL cond
    {
        // Repeat-until loop
        lineNumber = @1.first_line;
        $$ = new lp::RepeatStmt($3, $5, lineNumber);
        control--;
    }
;

for:
    FOR VARIABLE FROM exp TO exp DO controlSymbol stmtlist END_FOR
    {
        // For loop without step
        lineNumber = @1.first_line;
        $$ = new lp::ForStmt(std::string($2), $4, $6, $9, lineNumber);
        control--;
    }
  | FOR VARIABLE FROM exp TO exp STEP exp DO controlSymbol stmtlist END_FOR
    {
        // For loop with step
        lineNumber = @1.first_line;
        $$ = new lp::ForStmt(std::string($2), $4, $6, $8, $11, lineNumber);
        control--;
    }
;

case: CASE exp COLON stmtlist
    {
        // Case statement for switch
        lineNumber = @1.first_line;
        $$ = new lp::CaseStmt($2, $4, lineNumber);
    }

caselist:
    /* Empty list of case statements */
    {
        $$ = new std::list<lp::CaseStmt *>();
    }
  | caselist case
    {
        // Add case to the list
        $$ = $1;
        $$->push_front($2);
    }
;

switch:
    SWITCH controlSymbol LPAREN exp RPAREN caselist DEFAULT COLON stmtlist END_SWITCH
    {
        // Switch statement with default case
        lineNumber = @1.first_line;
        $$ = new lp::SwitchStmt($4, $6, $9, lineNumber);
    }
  | SWITCH controlSymbol LPAREN exp RPAREN caselist END_SWITCH
    {
        // Switch statement without default case
        lineNumber = @1.first_line;
        $$ = new lp::SwitchStmt($4, $6, lineNumber);
    }
;

cond:
    LPAREN exp RPAREN
    {
        // Parenthesized condition
        $$ = $2;
    }
;

asgn:
    VARIABLE ASSIGNMENT exp
    {
        // Assignment to variable
        lineNumber = @1.first_line;
        $$ = new lp::AssignmentStmt($1, $3, lineNumber);
    }
  | VARIABLE ASSIGNMENT asgn
    {
        // Multiple assignment to variable
        lineNumber = @1.first_line;
        $$ = new lp::AssignmentStmt($1, (lp::AssignmentStmt *) $3, lineNumber);
    }
  | CONSTANT ASSIGNMENT exp
    {
        // Error: assignment to constant
        execerror("Semantic error in assignment: it is not allowed to modify a constant ", $1);
    }
  | CONSTANT ASSIGNMENT asgn
    {
        // Error: multiple assignment to constant
        execerror("Semantic error in multiple assignment: it is not allowed to modify a constant ", $1);
    }
;

print:
    PRINT exp
    {
        // Print statement
        lineNumber = @1.first_line;
        $$ = new lp::PrintStmt($2, lineNumber);
    }
;

read:
    READ LPAREN VARIABLE RPAREN
    {
        // Read statement for variable
        lineNumber = @1.first_line;
        $$ = new lp::ReadStmt($3, lineNumber);
    }
  | READ_STRING LPAREN VARIABLE RPAREN
    {
        // Read string statement for variable
        lineNumber = @1.first_line;
        $$ = new lp::ReadStringStmt($3, lineNumber);
    }
  | READ LPAREN CONSTANT RPAREN
    {
        // Error: read into constant
        execerror("Semantic error in \"read statement\": it is not allowed to modify a constant ", $3);
    }
;

exp:
    NUMBER
    {
        // Numeric literal
        lineNumber = @1.first_line;
        $$ = new lp::NumberNode($1, lineNumber);
    }
  | STRING
    {
        // String literal
        lineNumber = @1.first_line;
        $$ = new lp::StringNode($1, lineNumber);
    }
  | exp PLUS exp
    {
        // Addition
        lineNumber = @2.first_line;
        $$ = new lp::PlusNode($1, $3, lineNumber);
    }
  | exp MINUS exp
    {
        // Subtraction
        lineNumber = @2.first_line;
        $$ = new lp::MinusNode($1, $3, lineNumber);
    }
  | exp MULTIPLICATION exp
    {
        // Multiplication
        lineNumber = @2.first_line;
        $$ = new lp::MultiplicationNode($1, $3, lineNumber);
    }
  | exp DIVISION exp
    {
        // Division
        lineNumber = @2.first_line;
        $$ = new lp::DivisionNode($1, $3, lineNumber);
    }
  | exp INTEGER_DIVISION exp
    {
        // Integer division
        lineNumber = @2.first_line;
        $$ = new lp::IntegerDivisionNode($1, $3, lineNumber);
    }
  | exp CONCATENATION exp
    {
        // String concatenation
        lineNumber = @2.first_line;
        $$ = new lp::ConcatenationNode($1, $3, lineNumber);
    }
  | LPAREN exp RPAREN
    {
        // Parenthesized expression
        lineNumber = @1.first_line;
        $$ = $2;
    }
  | PLUS exp %prec UNARY
    {
        // Unary plus
        lineNumber = @1.first_line;
        $$ = new lp::UnaryPlusNode($2, lineNumber);
    }
  | MINUS exp %prec UNARY
    {
        // Unary minus
        lineNumber = @1.first_line;
        $$ = new lp::UnaryMinusNode($2, lineNumber);
    }
  | exp MODULO exp
    {
        // Modulo operation
        lineNumber = @2.first_line;
        $$ = new lp::ModuloNode($1, $3, lineNumber);
    }
  | exp POWER exp
    {
        // Exponentiation
        lineNumber = @2.first_line;
        $$ = new lp::PowerNode($1, $3, lineNumber);
    }
  | VARIABLE
    {
        // Variable reference
        lineNumber = @1.first_line;
        $$ = new lp::VariableNode($1, lineNumber);
    }
  | CONSTANT
    {
        // Constant reference
        lineNumber = @1.first_line;
        $$ = new lp::ConstantNode($1, lineNumber);
    }
  | BUILTIN LPAREN listOfExp RPAREN
    {
        // Builtin function call
        lineNumber = @1.first_line;
        lp::Builtin *f = (lp::Builtin *) table.getSymbol($1);
        if (f->getNParameters() == (int) $3->size())
        {
            switch(f->getNParameters())
            {
                case 0:
                    $$ = new lp::BuiltinFunctionNode_0($1, lineNumber);
                    break;
                case 1:
                    $$ = new lp::BuiltinFunctionNode_1($1, $3->front(), lineNumber);
                    break;
                case 2:
                    {
                        lp::ExpNode *e1 = $3->front();
                        $3->pop_front();
                        lp::ExpNode *e2 = $3->front();
                        $$ = new lp::BuiltinFunctionNode_2($1, e1, e2, lineNumber);
                    }
                    break;
                default:
                    execerror("Syntax error: too many parameters for function ", $1);
            }
        }
        else
            execerror("Syntax error: incompatible number of parameters for function", $1);
    }
  | exp GREATER_THAN exp
    {
        // Greater than comparison
        lineNumber = @2.first_line;
        $$ = new lp::GreaterThanNode($1, $3, lineNumber);
    }
  | exp GREATER_OR_EQUAL exp
    {
        // Greater or equal comparison
        lineNumber = @2.first_line;
        $$ = new lp::GreaterOrEqualNode($1, $3, lineNumber);
    }
  | exp LESS_THAN exp
    {
        // Less than comparison
        lineNumber = @2.first_line;
        $$ = new lp::LessThanNode($1, $3, lineNumber);
    }
  | exp LESS_OR_EQUAL exp
    {
        // Less or equal comparison
        lineNumber = @2.first_line;
        $$ = new lp::LessOrEqualNode($1, $3, lineNumber);
    }
  | exp EQUAL exp
    {
        // Equality comparison
        lineNumber = @2.first_line;
        $$ = new lp::EqualNode($1, $3, lineNumber);
    }
  | exp NOT_EQUAL exp
    {
        // Not equal comparison
        lineNumber = @2.first_line;
        $$ = new lp::NotEqualNode($1, $3, lineNumber);
    }
  | exp AND exp
    {
        // Logical AND
        lineNumber = @2.first_line;
        $$ = new lp::AndNode($1, $3, lineNumber);
    }
  | exp OR exp
    {
        // Logical OR
        lineNumber = @2.first_line;
        $$ = new lp::OrNode($1, $3, lineNumber);
    }
  | NOT exp
    {
        // Logical NOT
        lineNumber = @1.first_line;
        $$ = new lp::NotNode($2, lineNumber);
    }
  | RANDOM LPAREN exp COMMA exp RPAREN
    {
        // Random number generation
        lineNumber = @1.first_line;
        $$ = new lp::RandomNode($3, $5, lineNumber);
    }
;

listOfExp:
    /* Empty list of numeric expressions */
    {
        // Create a new list of expressions
        $$ = new std::list<lp::ExpNode *>();
    }
  | exp restOfListOfExp
    {
        // Add expression to the list
        $$ = $2;
        $$->push_front($1);
    }
;

restOfListOfExp:
    /* Empty list of numeric expressions */
    {
        // Create a new list of expressions
        $$ = new std::list<lp::ExpNode *>();
    }
  | COMMA exp restOfListOfExp
    {
        // Add expression to the list
        $$ = $3;
        $$->push_front($2);
    }
;
%%