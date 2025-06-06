/*! 
  \file error.hpp
  \brief Prototypes for error recovery and reporting functions for the interpreter.
*/
#ifndef _ERROR_HPP_
#define _ERROR_HPP_

#include <string>

/**
 * @brief Reports a parser error with a custom message.
 * @param errorMessage Parser error message.
 * @return void
 * @sa warning
 */
void yyerror(std::string errorMessage);

/**
 * @brief Shows a lexical warning message with detailed information.
 * @param filename Name of the source file where the error occurred.
 * @param line Line number of the error location.
 * @param column Column number (character position) where the error starts or ends.
 * @param token The lexical token that caused the warning.
 * @param errorMsg Description of the lexical error or warning message.
 * @sa yyerror, parserWarning
 */
void lexicalWarning(const std::string& filename,
             int line,
             int column,
             const std::string& token,
             const std::string& errorMsg);

/**
 * @brief Shows a semantic error message with detailed information and suggestion.
 * @param filename Name of the source file where the error occurred.
 * @param line Line number of the error location.
 * @param column Column number (character position) where the error occurred.
 * @param errorMsg Description of the parser error.
 * @param suggestion A hint or suggestion to help fix the error.
 * @sa lexicalWarning, yyerror
 */
void semanticWarning(const std::string& filename,
             int line,
             int column,
             const std::string& errorMsg,
             const std::string& suggestion);

/**
 * @brief Shows a runtime error message with detailed information and suggestion.
 * @param filename Name of the source file where the error occurred.
 * @param line Line number of the error location.
 * @param column Column number (character position) where the error occurred.
 * @param errorMsg Description of the runtime error.
 * @param suggestion A hint or suggestion to help fix the error.
 */
void runtimeWarning(const std::string& filename,
             int line,
             int column,
             const std::string& errorMsg,
             const std::string& suggestion);

/**
 * @brief Handles execution errors and performs a long jump for error recovery.
 * @param errorMessage1 First error message.
 * @param errorMessage2 Second error message.
 * @return void
 * @sa warning, longjmp
 */
void execerror(std::string errorMessage1, std::string errorMessage2);

/**
 * @brief Signal handler for floating point exceptions.
 * @param p Signal number.
 * @return void
 * @sa warning
 */
void fpecatch(int p);

/**
 * @brief Checks for EDOM or ERANGE errors after a computation and handles them.
 * @param d Computed value (double).
 * @param s Context or function name.
 * @return The computed value if no error, otherwise triggers error handling.
 * @sa execerror
 */
double errcheck(double d, std::string s);

#endif