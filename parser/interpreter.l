/*! 
  \file interpreter.l
  \brief Lexical or scanner file
*/
%{

/* Standard libraries */
#include <iostream>
#include <cstdlib>
#include <cstring>

/* Project headers */
#include "../includes/macros.hpp"
#include "../ast/ast.hpp"
#include "interpreter.tab.h"
#include "../error/error.hpp"
#include "../table/table.hpp"
#include "../table/numericVariable.hpp"

/* External variables */
extern lp::Table table;        /* Symbol table */
extern int lineNumber;         /* Current line number for error reporting */

%}

/*! \name Regular definitions  */
LETTER                      [a-zA-Z]

DIGIT                       [0-9]

NUMBER1                     {DIGIT}+\.?

NUMBER2                     {DIGIT}*\.{DIGIT}+

NUMBER3                     {DIGIT}+(\.{DIGIT}+)?(E[+\-]?{DIGIT}+)?

IDENTIFIER                  {LETTER}({LETTER}|{DIGIT}|_)*

IDENTIFIER_WRONG1           {LETTER}({LETTER}|{DIGIT}|_)*__({LETTER}|{DIGIT}|_)*

IDENTIFIER_WRONG2           {LETTER}({LETTER}|{DIGIT}|_)*_

IDENTIFIER_WRONG3           (_|{DIGIT})({LETTER}|{DIGIT}|_)*

STRING                      \'([^'\\]|\\.)*\'

COMMENT_IN_ONE_LINE         #[^\n]*

/* States */
%x ERROR
%x COMMENT_STATE

/*! \name Regular expressions  */
%%

    /****** Strings ******/
{STRING}                            { 
                                        yylval.string = strdup(yytext);
                                        return STRING;
                                    }

    /****** Comments ******/
{COMMENT_IN_ONE_LINE}               {}

"(*"                                { BEGIN COMMENT_STATE; }

<COMMENT_STATE>"(*"/(.|\n)          {}

<COMMENT_STATE>"*)"                 { BEGIN 0; }

<COMMENT_STATE>.                    {}

    /****** Control flow keywords ******/
"read"          { return READ; }
"read_string"   { return READ_STRING; }
"print"         { return PRINT; }

"if"            { return IF; }
"then"          { return THEN; }
"else"          { return ELSE; }
"end_if"        { return END_IF; }

"while"         { return WHILE; }
"do"            { return DO; }
"end_while"     { return END_WHILE; }

"repeat"        { return REPEAT; }
"until"         { return UNTIL; }

"for"           { return FOR; }
"end_for"       { return END_FOR; }
"from"          { return FROM; }
"step"          { return STEP; }
"to"            { return TO; }

"switch"        { return SWITCH; }
"case"          { return CASE; }
"default"       { return DEFAULT; }
"end_switch"    { return END_SWITCH; }

    /****** Screen functions ******/
"clear_screen"  { return CLEAR_SCREEN; }
"place"         { return PLACE; }

    /****** Math functions ******/
"sin"           { return SIN; }
"cos"           { return COS; }
"sqrt"          { return SQRT; }
"log"           { return LOG; }
"log10"         { return LOG10; }
"exp"           { return EXP; }
"integer"       { return INTEGER; }
"abs"           { return ABS; }

    /****** Math constants ******/
"pi"            { return PI; }
"e"             { return E; }
"gamma"         { return GAMMA; }
"phi"           { return PHI; }
"deg"           { return DEG; }

    /****** Boolean values ******/
"true"          { return TRUE; }
"false"         { return FALSE; }


[ \t]           {}   /* skip white space and tabular */

\n              { 
                    /* Line counter */
                    lineNumber++; 
                }

";"             {
                    return SEMICOLON;
                }


","             {
                    return COMMA;
                }

    /****** Number ******/
{NUMBER1}|{NUMBER2}|{NUMBER3}  {
                      /* Conversion of type and sending of the numerical value to the parser */
                       yylval.number = atof(yytext); 
                       return NUMBER; 
                    }

    /****** Identifier ******/
{IDENTIFIER_WRONG1} { 
                        /* 
                            An identifier with two underscores is not allowed
                            Change to error state
                        */
                        BEGIN(ERROR); 
                        yymore(); 
                    }

{IDENTIFIER_WRONG2} { 
                        /* 
                            An identifier with an underscore at the end is not allowed
                            Change to error state
                        */
                        BEGIN(ERROR); 
                        yymore(); 
                    }
                    
{IDENTIFIER_WRONG3} { 
                        /* 
                            An identifier with an underscore at the beginning or a digit at the beginning is not allowed
                            Change to error state
                        */
                        BEGIN(ERROR); 
                        yymore(); 
                    }

{IDENTIFIER}        {
                         std::string identifier(yytext);

                        /* 
                          strdup() function returns a pointer to a new string 
                          which  is a duplicate of the string yytext
                        */
                          yylval.string =  strdup(yytext);

                        /* If the identifier is not in the table of symbols then it is inserted */    
                         if (table.lookupSymbol(identifier) == false)
                            {
                                /* 
                                 The identifier is inserted into the symbol table 
                                 as undefined Variable with value 0.0
                                */
                                lp::NumericVariable *n = new lp::NumericVariable(identifier,VARIABLE,UNDEFINED,0.0);

                                /* A pointer to the new NumericVariable is inserted into the table of symbols */
                                table.installSymbol(n);

                                return VARIABLE;
                            }

                        /* 
                            If the identifier is in the table of symbols then its token is returned 
                                The identifier can be a variable or a numeric constant
                        */
                        else 
                            {
                                lp::Symbol    *s = table.getSymbol(identifier);

                                /*  If the identifier is in the table then its token is returned  */
                                return s->getToken();
                            }
                    }

"-"        { return MINUS;  }
"+"        { return PLUS;   }

"*"        { return MULTIPLICATION; }
"/"        { return DIVISION; }
 /*"//"    { return INTEGER_DIVISION; }*/

"("        { return LPAREN; }
")"        { return RPAREN; }

 /*"||"    { return CONCATENATION; }*/

"mod"      { return MODULO; }

"^"        { return POWER; }

":="       { return ASSIGNMENT; }


"="        { return EQUAL; }

"<>"       { return NOT_EQUAL; }

">="       { return GREATER_OR_EQUAL; }

"<="       { return LESS_OR_EQUAL; }

">"        { return GREATER_THAN; }

"<"        { return LESS_THAN; }

"not"      { return NOT; }

"or"       { return OR; }

"and"      { return AND; }

"{"        { return LETFCURLYBRACKET; }

"}"        { return RIGHTCURLYBRACKET; }

<<EOF>> { /* The interpreter finishes when finds the end of file character */
        /*  PLACE(24,10);
            std::cout <<  BICYAN;
             std::cout <<  ">>>>>>> End of program <<<<<<<";
           std::cout << std::endl;
             std::cout << RESET;
          PLACE(25,1);
        */
            return 0;
        }

.                                {     
                                    /* Any other character */
                                    BEGIN(ERROR); 
                                    yymore();  
                                 }

<ERROR>[^0-9+\-*/()\^% \t\n\;a-zA-Z=<>!&]    { yymore(); }

<ERROR>(.|\n)                { 
                                /* Rewind one position */
                                yyless(yyleng-1); 

                                /* Display the error message */
                                warning("Lexical error", yytext);

                                /* Restore the initial state */
                                   BEGIN(INITIAL);
                             }
%%

