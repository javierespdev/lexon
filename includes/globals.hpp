#ifndef _GLOBALS_HPP
#define _GLOBALS_HPP

#include <string>
#include <vector>

extern int lineNumber;
extern int columnNumber;
extern std::string currentLine;
extern std::string errorMsg;
extern std::string fileName;
extern std::vector<std::string> sourceLines;
extern std::string suggestion;
extern FILE * yyin;
extern bool interactiveMode;

#endif // _GLOBALS_HPP