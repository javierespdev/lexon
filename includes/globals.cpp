#include "globals.hpp"

#include<iostream>

int lineNumber = 1;
int columnNumber = 1;
std::string currentLine = "";
std::string errorMsg = "";
std::string fileName = "";
std::string sourceLine = "";
std::string suggestion = "";
bool interactiveMode;

std::string readLineFromFile(FILE* file, int lineNumber) {

    std::string currentCinLine;

    if(interactiveMode)
    {
        std::getline(std::cin, currentCinLine);
        std::cout << currentCinLine << std::endl;
        return currentCinLine;
    }

    long originalPos = ftell(file);
    if (originalPos == -1L) return "";

    if (fseek(file, 0, SEEK_SET) != 0) return "";

    char buffer[4096];
    int currentLine = 0;
    std::string line;

    while (fgets(buffer, sizeof(buffer), file)) {
        currentLine++;
        if (currentLine == lineNumber) {
            line = buffer;

            while (!line.empty()) {
                char lastChar = line[line.size() - 1];
                if (lastChar == '\n' || lastChar == '\r') {
                    line.resize(line.size() - 1);
                } else {
                    break;
                }
            }
            break;
        }
    }

    fseek(file, originalPos, SEEK_SET);

    return line;
}