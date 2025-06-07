/*!
    * \file interpreter.l
    * \brief Lexical analyzer for the Lexon interpreter.
    *
    * This file defines the lexical rules and actions for tokenizing the input source code.
    * It handles string literals, comments, operators, grouping symbols, assignment, identifiers,
    * numbers, and error reporting. The scanner also manages line and column tracking for error messages.
    *
    * \date 2025-06-06
*/

%option yylineno

%{

/* Standard libraries */
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
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

/*!
 * \name Regular definitions
 * \brief Definitions for character classes and token patterns.
 */

LETTER                      [a-zA-Z]

DIGIT                       [0-9]

NUMBER1                     {DIGIT}+\.?

NUMBER2                     {DIGIT}*\.{DIGIT}+

NUMBER3                     {DIGIT}+(\.{DIGIT}+)?(E[+\-]?{DIGIT}+)?

NUMBER_WRONG1               {DIGIT}+\.\.+{DIGIT}*

NUMBER_WRONG2               {DIGIT}+(e|E)(e|E)+{DIGIT}*

NUMBER_WRONG3               {DIGIT}+(e|E)(\+|\-)(\+|\-)+{DIGIT}*

IDENTIFIER                  {LETTER}({LETTER}|{DIGIT}|_)*

IDENTIFIER_WRONG1           {LETTER}({LETTER}|{DIGIT}|_)*__({LETTER}|{DIGIT}|_)*

IDENTIFIER_WRONG2           {LETTER}({LETTER}|{DIGIT}|_)*_

IDENTIFIER_WRONG3           (_|{DIGIT})({LETTER}|{DIGIT}|_)*

STRING                      \'([^'\\]|\\.)*\'

COMMENT_IN_ONE_LINE         #[^\n]*

/* States for error and comment handling */
%x ERROR
%x COMMENT_STATE

/*!
 * \name Regular expressions and rules
 * \brief Main lexical rules for tokenizing the input.
 */
%%

    /****** Strings ******/
{STRING}            {
    /*
     * Handles string literals, including escape sequences (\n, \t, \\ etc.).
     * Converts the matched string to a C string and stores it in yylval.string.
     */
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
"++"        {
                columnNumber += yyleng;
                currentLine += yytext;
                return INCREMENT;
          }
"--"        {
                columnNumber += yyleng;
                currentLine += yytext;
                return DECREMENT;
          }
"!"        {
                columnNumber += yyleng;
                currentLine += yytext;
                return FACTORIAL;
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
"+:="       {
                columnNumber += yyleng;
                currentLine += yytext;
                return PLUS_ASSIGNMENT;
          }
"-:="       {
                columnNumber += yyleng;
                currentLine += yytext;
                return MINUS_ASSIGNMENT;
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
    /* Skip white space and tabular characters. */
    columnNumber += yyleng;
    currentLine += yytext;
}

\n              {
    /* Handle new lines: increment line counter and reset column. */
    lineNumber++;
    columnNumber = 1;
    currentLine += yytext;
}

";"             {
    columnNumber += yyleng;
    currentLine += yytext;
    return SEMICOLON;
}

":"             {
    columnNumber += yyleng;
    currentLine += yytext;
    return COLON;
}

","             {
    columnNumber += yyleng;
    currentLine += yytext;
    return COMMA;
}

"+:="     {
    /*
     * Lexical rule for the "+:=" operator, which is a special assignment operator.
     * It is treated as a single token.
     */
    columnNumber += yyleng;
    currentLine += yytext;
    return PLUS_ASSIGNMENT;
}

"-:="     {
    /*
     * Lexical rule for the "-:=" operator, which is a special assignment operator.
     * It is treated as a single token.
     */
    columnNumber += yyleng;
    currentLine += yytext;
    return MINUS_ASSIGNMENT;
}

    /****** Number ******/
{NUMBER_WRONG1} {
    /*
     * Lexical error: detected a number with multiple decimal points.
     * Example: "12..34"
     */
    columnNumber += yyleng;
    currentLine += yytext;
    errorMsg = "Not valid number with multiple decimal points detected";
    BEGIN(ERROR);
    yymore();
}

{NUMBER_WRONG2} {
    /*
     * Lexical error: detected a number with repeated exponent characters.
     * Example: "5ee10"
     */
    columnNumber += yyleng;
    currentLine += yytext;
    errorMsg = "Not valid number with repeated exponent characters detected";
    BEGIN(ERROR);
    yymore();
}

{NUMBER_WRONG3} {
    /*
     * Lexical error: detected a number with multiple consecutive signs in exponent.
     * Example: "3e++5"
     */
    columnNumber += yyleng;
    currentLine += yytext;
    errorMsg = "Not valid number with multiple consecutive signs in exponent detected";
    BEGIN(ERROR);
    yymore();
}

{NUMBER1}|{NUMBER2}|{NUMBER3}  {
    /*
     * Converts the matched numeric string to a double and stores it in yylval.number.
     */
    yylval.number = atof(yytext);
    columnNumber += yyleng;
    currentLine += yytext;
    return NUMBER;
}

    /****** Identifier ******/
{IDENTIFIER_WRONG1} {
    /*
     * An identifier with two underscores is not allowed.
     * Switch to error state and set error message.
     */
    columnNumber += yyleng;
    currentLine += yytext;
    errorMsg = "Not valid identifier with double underscore";
    BEGIN(ERROR);
    yymore();
}

{IDENTIFIER_WRONG2} {
    /*
     * An identifier with an underscore at the end is not allowed.
     * Switch to error state and set error message.
     */
    columnNumber += yyleng;
    currentLine += yytext;
    errorMsg = "Not valid identifier with underscore at the end";
    BEGIN(ERROR);
    yymore();
}

{IDENTIFIER_WRONG3} {
    /*
     * An identifier with an underscore or digit at the beginning is not allowed.
     * Switch to error state and set error message.
     */
    columnNumber += yyleng;
    currentLine += yytext;
    errorMsg = "Not valid identifier with underscore at the beginning or a digit at the beginning";
    BEGIN(ERROR);
    yymore();
}

{IDENTIFIER} {
    /*
     * Converts the input text (yytext) to lowercase and stores it in 'identifier'.
     * If the identifier is not in the symbol table, it is inserted as an undefined variable.
     * Otherwise, returns the token for the existing symbol.
     */
    std::string identifier;
    for (int i = 0; yytext[i] != '\0'; ++i)
    {
        identifier += std::tolower(yytext[i]);
    }
    yylval.string = strdup(identifier.c_str());
    if (table.lookupSymbol(identifier) == false)
    {
        lp::NumericVariable *n = new lp::NumericVariable(identifier, VARIABLE, UNDEFINED, 0.0);
        table.installSymbol(n);
        columnNumber += yyleng;
        currentLine += yytext;
        return VARIABLE;
    }
    else
    {
        lp::Symbol *s = table.getSymbol(identifier);
        columnNumber += yyleng;
        currentLine += yytext;
        return s->getToken();
    }
}

. {
    /* Any other character: treat as error and accumulate for error reporting. */
    currentLine += yytext;
    columnNumber += yyleng;
    BEGIN(ERROR);
    yymore();
}

<ERROR>([^0-9+\-*/()\^% \t\n\;a-zA-Z=<>!&]) { 
    yymore(); 
    currentLine += yytext;
    }

<ERROR>(.|\n) {
    /*
     * Handles error state: rewinds one position, displays the error message,
     * and restores the initial state.
     */
    yyless(yyleng-1);
    lexicalWarning(fileName, lineNumber, columnNumber, yytext, errorMsg);
    BEGIN(INITIAL);
}
%%