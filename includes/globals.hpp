#ifndef _GLOBALS_HPP
#define _GLOBALS_HPP

#include <string>

extern int lineNumber;
extern int columnNumber;
extern std::string currentLine;
extern std::string errorMsg;
extern std::string fileName;
extern std::string sourceLine;
extern std::string suggestion;
extern FILE * yyin;
extern bool interactiveMode;

extern std::string readLineFromFile(FILE* file, int lineNumber);

#endif // _GLOBALS_HPP