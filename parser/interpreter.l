/*! 
  \file interpreter.l
  \brief Lexical or scanner file
*/
%option yylineno 
%{

/* Standard libraries */
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>

/* Project headers */
#include "../includes/macros.hpp"
#include "../ast/ast.hpp"
#include "interpreter.tab.h"
#include "../error/error.hpp"
#include "../table/table.hpp"
#include "../table/numericVariable.hpp"
#include "../includes/globals.hpp"

/* External variables */
extern lp::Table table;        /* Symbol table */

#include <cstdio>
#include <string>

%}

%option yylineno

%{

/* Standard libraries */
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>

/* Project headers */
#include "../includes/macros.hpp"
#include "../ast/ast.hpp"
#include "interpreter.tab.h"
#include "../error/error.hpp"
#include "../table/table.hpp"
#include "../table/numericVariable.hpp"
#include "../includes/globals.hpp"

/* External variables */
extern lp::Table table;        /* Symbol table */

#include <cstdio>
#include <string>

#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;

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
{STRING}            {
                        std::string result;
                        for (size_t i = 1; i < yyleng - 1; ++i)
                        {
                            if (yytext[i] == '\\' && i + 1 < yyleng - 1)
                            {
                                switch (yytext[i + 1])
                                {
                                    case 'n': result += '\n'; break;
                                    case 't': result += '\t'; break;
                                    case 'r': result += '\r'; break;
                                    case '\'': result += '\''; break;
                                    default:
                                        result += '\\';
                                        result += yytext[i + 1];
                                        break;
                                }
                                ++i;
                            }
                            else
                            {
                                result += yytext[i];
                            }
                        }

                        yylval.string = strdup(result.c_str());
                        columnNumber += yyleng;
                        currentLine += yytext;
                        return STRING;
                    }

    /****** Comments ******/
{COMMENT_IN_ONE_LINE}               {}

"(*"                                { BEGIN COMMENT_STATE; }

<COMMENT_STATE>"(*"/(.|\n)          {}

<COMMENT_STATE>"*)"                 { BEGIN 0; }

<COMMENT_STATE>.                    {}

    /****** Numeric operators ******/
"-"        {
                columnNumber += yyleng;
                currentLine += yytext;
                return MINUS;
          }
"+"        {
                columnNumber += yyleng;
                currentLine += yytext;
                return PLUS;
          }
"*"        {
                columnNumber += yyleng;
                currentLine += yytext;
                return MULTIPLICATION;
          }
"/"        {
                columnNumber += yyleng;
                currentLine += yytext;
                return DIVISION;
          }
"//"       {
                columnNumber += yyleng;
                currentLine += yytext;
                return INTEGER_DIVISION;
          }
"^"        {
                columnNumber += yyleng;
                currentLine += yytext;
                return POWER;
          }

    /****** Grouping symbols ******/
"("        {
                columnNumber += yyleng;
                currentLine += yytext;
                return LPAREN;
          }
")"        {
                columnNumber += yyleng;
                currentLine += yytext;
                return RPAREN;
          }
"{"        {
                columnNumber += yyleng;
                currentLine += yytext;
                return LETFCURLYBRACKET;
          }
"}"        {
                columnNumber += yyleng;
                currentLine += yytext;
                return RIGHTCURLYBRACKET;
          }

    /****** Assignment ******/
":="       {
                columnNumber += yyleng;
                currentLine += yytext;
                return ASSIGNMENT;
          }

    /****** String operators ******/
"||"       {
                columnNumber += yyleng;
                currentLine += yytext;
                return CONCATENATION;
          }

    /****** Comparison operators ******/
"="        {
                columnNumber += yyleng;
                currentLine += yytext;
                return EQUAL;
          }
"<>"       {
                columnNumber += yyleng;
                currentLine += yytext;
                return NOT_EQUAL;
          }
">="       {
                columnNumber += yyleng;
                currentLine += yytext;
                return GREATER_OR_EQUAL;
          }
"<="       {
                columnNumber += yyleng;
                currentLine += yytext;
                return LESS_OR_EQUAL;
          }
">"        {
                columnNumber += yyleng;
                currentLine += yytext;
                return GREATER_THAN;
          }
"<"        {
                columnNumber += yyleng;
                currentLine += yytext;
                return LESS_THAN;
          }

[ \t]           {
                    columnNumber += yyleng;
                    currentLine += yytext;
              }   /* skip white space and tabular */

\n              {
                    lineNumber++;
                    columnNumber = 1;
                    currentLine = "";
              }

";"             {
                    columnNumber += yyleng;
                    currentLine += yytext;
                    return SEMICOLON;
                }


","             {
                    columnNumber += yyleng;
                    currentLine += yytext;
                    return COMMA;
                }

    /****** Number ******/
{NUMBER1}|{NUMBER2}|{NUMBER3}  {
                      /* Conversion of type and sending of the numerical value to the parser */
                       yylval.number = atof(yytext); 
                       columnNumber += yyleng;
                       currentLine += yytext;
                       return NUMBER; 
                    }

    /****** Identifier ******/
{IDENTIFIER_WRONG1} { 
                        /* 
                            An identifier with two underscores is not allowed
                            Change to error state
                        */
                        columnNumber += yyleng;
                        currentLine += yytext;
                        errorMsg = "Not valid identifier with double underscore";
                        BEGIN(ERROR); 
                        yymore(); 
                    }

{IDENTIFIER_WRONG2} { 
                        /* 
                            An identifier with an underscore at the end is not allowed
                            Change to error state
                        */
                        columnNumber += yyleng;
                        currentLine += yytext;
                        errorMsg = "Not valid identifier with underscore at the end";
                        BEGIN(ERROR); 
                        yymore(); 
                    }
                    
{IDENTIFIER_WRONG3} { 
                        /* 
                            An identifier with an underscore at the beginning or a digit at the beginning is not allowed
                            Change to error state
                        */
                        columnNumber += yyleng;
                        currentLine += yytext;
                        errorMsg = "Not valid identifier with underscore at the beginning or a digit at the beginning";
                        BEGIN(ERROR); 
                        yymore(); 
                    }

{IDENTIFIER}        {
                        /* 
                            Convert the input text (yytext) to lowercase and store it in 'identifier'
                        */
                        std::string identifier;

                        for (int i = 0; yytext[i] != '\0'; ++i)
                        {
                            identifier += std::tolower(yytext[i]);
                        }

                        /* 
                          strdup() function returns a pointer to a new string 
                          which  is a duplicate of the string yytext
                        */
                          yylval.string =  strdup(identifier.c_str());

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

                                columnNumber += yyleng;
                                currentLine += yytext;
                                return VARIABLE;
                            }

                        /* 
                            If the identifier is in the table of symbols then its token is returned 
                                The identifier can be a variable or a numeric constant
                        */
                        else 
                            {
                                lp::Symbol    *s = table.getSymbol(identifier);

                                columnNumber += yyleng;
                                currentLine += yytext;
                                /*  If the identifier is in the table then its token is returned  */
                                return s->getToken();
                            }
                    }

.                                {
                                    currentLine += yytext;
                                    columnNumber += yyleng;
                                    BEGIN(ERROR);
                                    yymore();
                                 }

<ERROR>([^0-9+\-*/()\^% \t\n\;a-zA-Z=<>!&])    { yymore(); }


<ERROR>(.|\n)                { 
                                /* Rewind one position */
                                yyless(yyleng-1);

                                /* Display the error message */
                                lexicalWarning(fileName, lineNumber, columnNumber, yytext, errorMsg);

                                /* Restore the initial state */
                                BEGIN(INITIAL);
                             }
%%