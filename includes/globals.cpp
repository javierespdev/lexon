/*! 
 * \file globals.cpp
 * \brief Definition of global variables used throughout the interpreter.
 */

#include "globals.hpp"
#include <iostream>

/**
 * @var int lineNumber
 * @brief Tracks the current line number being processed.
 */
int lineNumber = 1;

/**
 * @var int columnNumber
 * @brief Tracks the current column number being processed.
 */
int columnNumber = 1;

/**
 * @var std::string currentLine
 * @brief Stores the current line of input being processed.
 */
std::string currentLine = "";

/**
 * @var std::string errorMsg
 * @brief Stores the most recent error message.
 */
std::string errorMsg = "";

/**
 * @var std::string fileName
 * @brief Name of the file currently being processed.
 */
std::string fileName = "";

/**
 * @var std::vector<std::string> sourceLines
 * @brief Stores all lines of the source file for reference and error reporting.
 */
std::vector<std::string> sourceLines;

/**
 * @var std::string suggestion
 * @brief Stores suggestions or hints for error recovery or user feedback.
 */
std::string suggestion = "";

/**
 * @var bool interactiveMode
 * @brief Indicates if the interpreter is running in interactive mode.
 */
bool interactiveMode;