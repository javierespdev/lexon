/*! 
  \file error.cpp
  \brief Implementation of error recovery and reporting functions for the interpreter.
*/

// Standard C++ libraries
#include <iostream>
#include <string>
#include <setjmp.h>
#include <errno.h>
#include <iomanip>
#include <sstream>
#include <cstdlib>

// Project-specific headers
#include "error.hpp"
#include "../includes/macros.hpp"
#include "../includes/globals.hpp"

extern int lineNumber; //!< Reference to line counter
extern std::string progname; //!< Reference to program name
extern jmp_buf begin; //!< Used for error recovery
extern int errno; //!< Reference to the global variable that controls errors in the mathematical code

/**
 * @brief Counts the number of digits in an integer.
 * @param number The integer whose digits are to be counted.
 * @return The number of digits in the integer.
 */
int countDigits(int number) {
    if (number == 0) return 1;
    int digits = 0;
    while (number != 0) {
        number /= 10;
        ++digits;
    }
    return digits;
}

/**
 * @brief Prints a formatted lexical warning message with context and highlighting.
 * @param filename Name of the source file.
 * @param line Line number where the warning occurred.
 * @param column Column number where the warning occurred.
 * @param token The token that caused the warning.
 * @param errorMsg Description of the lexical error.
 */
void lexicalWarning(const std::string& filename,
             int line,
             int column,
             const std::string& token,
             const std::string& errorMsg)
{
  std::string sourceLine = "";
  if (line - 1 >= 0 && (size_t)(line - 1) < sourceLines.size())
    sourceLine = sourceLines[line - 1];
  else if (interactiveMode && !currentLine.empty()) {
    // Extract the specific line from currentLine corresponding to 'line'
    std::istringstream iss(currentLine);
    std::string tempLine;
    int current = 1;
    while (std::getline(iss, tempLine)) {
        if (current == line) {
            sourceLine = tempLine;
            break;
        }
        ++current;
    }
  }

  std::cerr << filename << ":" << line << ":" << column << ": " << BIRED <<"Lexical error: " << RESET
            << "'" << token << "'" << std::endl;

  int start = column - (int)token.size() - 1;
  if (start < 0) start = 0;
  int len = std::min((int)token.size(), (int)sourceLine.size() - start);
  std::string before = sourceLine.substr(0, start);
  std::string highlighted = sourceLine.substr(start, len);
  std::string after = sourceLine.substr(start + len);
  int lineWidth = countDigits(line);

  std::cerr << " " << std::setw(lineWidth) << line << " | " << before << BIRED << highlighted << RESET << after << std::endl;
  std::cerr << " " << std::setw(lineWidth) << "" << " | " << std::string(start, ' ') << BIRED << "^" << RESET << std::endl;
  std::cerr << BIYELLOW << "    Hint: " << RESET << errorMsg << std::endl;
  currentLine = "";

  exit(EXIT_FAILURE);
}

/**
 * @brief Prints a formatted semantic warning message with context and suggestion.
 * @param filename Name of the source file.
 * @param line Line number where the warning occurred.
 * @param column Column number where the warning occurred.
 * @param errorMsg Description of the semantic error.
 * @param suggestion Suggestion to resolve the warning.
 */
void semanticWarning(const std::string& filename,
             int line,
             int column,
             const std::string& errorMsg,
             const std::string& suggestion)
{
  std::string sourceLine = "";
  if (line - 1 >= 0 && (size_t)(line - 1) < sourceLines.size())
    sourceLine = sourceLines[line - 1];
  else if (interactiveMode && !currentLine.empty()) {
    // Extract the specific line from currentLine corresponding to 'line'
    std::istringstream iss(currentLine);
    std::string tempLine;
    int current = 1;
    while (std::getline(iss, tempLine)) {
        if (current == line) {
            sourceLine = tempLine;
            break;
        }
        ++current;
    }
  }

  std::cerr << filename << ":" << line << ":" << column << ": " << BIRED <<"Semantic error: " << RESET
            << errorMsg << std::endl;

  int lineWidth = countDigits(line);
  std::cerr << " " << std::setw(lineWidth) << line << " | " << sourceLine << std::endl;
  std::cerr << " " << std::setw(lineWidth) << ""   << " | " << std::endl;
  std::cerr << BIYELLOW << "    Suggestion: " << RESET << suggestion << std::endl;
  currentLine = "";

  exit(EXIT_FAILURE);
}

/**
 * @brief Prints a formatted syntax warning message with context.
 * @param filename Name of the source file.
 * @param line Line number where the warning occurred.
 * @param column Column number where the warning occurred.
 * @param errorMsg Description of the syntax error.
 */
void syntaxWarning(const std::string& filename,
             int line,
             int column,
             const std::string& errorMsg)
{
  std::string sourceLine = "";
  if (line - 1 >= 0 && (size_t)(line - 1) < sourceLines.size())
    sourceLine = sourceLines[line - 1];
  else if (interactiveMode && !currentLine.empty()) {
    // Extract the specific line from currentLine corresponding to 'line'
    std::istringstream iss(currentLine);
    std::string tempLine;
    int current = 1;
    while (std::getline(iss, tempLine)) {
        if (current == line) {
            sourceLine = tempLine;
            break;
        }
        ++current;
    }
  }

  std::cerr << filename << ":" << line << ":" << column << ": " << BIRED <<"Syntax error: " << RESET
            << errorMsg << std::endl;
  std::cerr << "    " << line << " | "  << sourceLine << std::endl;
  currentLine = "";

  exit(EXIT_FAILURE);
}

/**
 * @brief Prints a formatted runtime warning message with context and suggestion.
 * @param filename Name of the source file.
 * @param line Line number where the warning occurred.
 * @param column Column number where the warning occurred.
 * @param errorMsg Description of the runtime error.
 * @param suggestion Suggestion to resolve the warning.
 */
void runtimeWarning(const std::string& filename,
             int line,
             int column,
             const std::string& errorMsg,
             const std::string& suggestion)
{
  std::string sourceLine = "";
  if (line - 1 >= 0 && (size_t)(line - 1) < sourceLines.size())
    sourceLine = sourceLines[line - 1];
  else if (interactiveMode && !currentLine.empty()) {
    // Extract the specific line from currentLine corresponding to 'line'
    std::istringstream iss(currentLine);
    std::string tempLine;
    int current = 1;
    while (std::getline(iss, tempLine)) {
        if (current == line) {
            sourceLine = tempLine;
            break;
        }
        ++current;
    }
  }

  std::cerr << filename << ":" << line << ":" << column << ": " << BIRED <<"Runtime error: " << RESET
            << errorMsg << std::endl;
  std::cerr << "    " << line << " | "  << sourceLine << std::endl;
  std::cerr << "      | " << std::endl;
}

/**
 * @brief Handles syntax errors from the parser and prints a custom error message.
 * @param errorMessage The error message from the parser.
 */
void yyerror(std::string errorMessage)
{
    // Custom syntax error message
    std::string toRemove = "syntax error, ";
    size_t pos = errorMessage.find(toRemove);

    if (pos != std::string::npos) {
        errorMessage.erase(pos, toRemove.length());
    }

    syntaxWarning(fileName, lineNumber, columnNumber, errorMessage);
}

/**
 * @brief Handles execution errors and performs a long jump for error recovery.
 * @param errorMessage1 Main error message.
 * @param errorMessage2 Additional error message.
 */
void execerror(std::string errorMessage1,std::string errorMessage2)
{
 longjmp(begin,0); /* return to a viable state */
}

/**
 * @brief Signal handler for floating point exceptions.
 * @param signum Signal number.
 */
void fpecatch(int signum)     
{
 execerror("Run time","floating point error");
}

/**
 * @brief Checks for mathematical errors after a computation and handles them.
 * @param d The computed value.
 * @param s The context or function name.
 * @return The computed value if no error, otherwise triggers error handling.
 */
double errcheck(double d, std::string s)
{
  if (errno==EDOM)
    {
     errno=0;
     std::string msg("Runtime error --> argument out of domain");
     std::cout << msg << std::endl;
     execerror(s,msg);
    }
   else if (errno==ERANGE)
           {
            std::string msg("Runtime error --> result out of range");
            errno=0;
            execerror(s,msg);
           }

 return d;
}