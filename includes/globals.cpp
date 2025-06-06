#include "globals.hpp"

#include<iostream>

int lineNumber = 1;
int columnNumber = 1;
std::string currentLine = "";
std::string errorMsg = "";
std::string fileName = "";
std::vector<std::string> sourceLines;
std::string suggestion = "";
bool interactiveMode;
std::string currentInteractiveLine = "";