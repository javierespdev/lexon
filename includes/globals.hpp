/*! 
 * \file globals.hpp
 * \brief Declaration of global variables used throughout the interpreter.
 */
#ifndef _GLOBALS_HPP
#define _GLOBALS_HPP

#include <string>
#include <vector>

/**
 * @brief Tracks the current line number being processed.
 */
extern int lineNumber;

/**
 * @brief Tracks the current column number being processed.
 */
extern int columnNumber;

/**
 * @brief Stores the current line of input being processed.
 */
extern std::string currentLine;

/**
 * @brief Stores the most recent error message.
 */
extern std::string errorMsg;

/**
 * @brief Name of the file currently being processed.
 */
extern std::string fileName;

/**
 * @brief Stores all lines of the source file for reference and error reporting.
 */
extern std::vector<std::string> sourceLines;

/**
 * @brief Stores suggestions or hints for error recovery or user feedback.
 */
extern std::string suggestion;

/**
 * @brief File pointer to the input stream for the parser.
 */
extern FILE * yyin;

/**
 * @brief Indicates if the interpreter is running in interactive mode.
 */
extern bool interactiveMode;

#endif // _GLOBALS_HPP