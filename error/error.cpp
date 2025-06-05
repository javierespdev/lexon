/*! 
  \file error.cpp
  \brief Code of error recovery functions 
*/


// cerr, endl
#include <iostream>

#include <string>

/*  longjmp */
#include <setjmp.h>

// ERANGE, EDOM
#include <errno.h>

#include "error.hpp"

// Macros for the screen
#include "../includes/macros.hpp"

#include "../includes/globals.hpp"

extern int lineNumber; //!< // Reference to line counter

extern std::string progname; //!<  Reference to program name

extern jmp_buf begin; //!< Used for error recovery 

extern int errno; //!<  ReferenceReference to the global variable that controls errors in the mathematical code

void lexicalWarning(const std::string& filename,
             int line,
             int column,
             const std::string& token,
             const std::string& errorMsg)
{
  std::string sourceLine = sourceLines[line - 1];

  std::cerr << filename << ":" << line << ":" << column << ": " << BIRED <<"Lexical error: " << RESET
            << "'" << token << "'" << std::endl;

  int start = column - (int)token.size() - 1;
  int len = std::min((int)token.size(), (int)sourceLine.size() - start);

  std::string before = sourceLine.substr(0, start);
  std::string highlighted = sourceLine.substr(start, len);
  std::string after = sourceLine.substr(start + len);

  std::cerr << "    " << line << " | " << before << BIRED << highlighted << RESET << after << std::endl;
  std::cerr << "      | " << std::string(start, ' ') << BIRED << "^" << RESET << std::endl;
  std::cerr << BIYELLOW << "    Hint: " << RESET << errorMsg << std::endl;
}

void semanticWarning(const std::string& filename,
             int line,
             int column,
             const std::string& errorMsg,
             const std::string& suggestion)
{
  std::string sourceLine = sourceLines[line - 1];

  std::cerr << filename << ":" << line << ":" << column << ": " << BIRED <<"Semantic error: " << RESET
            << errorMsg << std::endl;

  std::cerr << "    " << line << " | "  << sourceLine << std::endl;
  std::cerr << "      | " << std::endl;
  std::cerr << BIYELLOW << "    Suggestion: " << RESET << suggestion << std::endl;
}


void syntaxWarning(const std::string& filename,
             int line,
             int column,
             const std::string& errorMsg)
{
  std::string sourceLine = sourceLines[line - 1];

  std::cerr << filename << ":" << line << ":" << column << ": " << BIRED <<"Syntax error: " << RESET
            << errorMsg << std::endl;

  std::cerr << "    " << line << " | "  << sourceLine << std::endl;
  std::cerr << "      | " << std::endl;
}

void runtimeWarning(const std::string& filename,
             int line,
             int column,
             const std::string& errorMsg,
             const std::string& suggestion)
{
  std::string sourceLine = sourceLines[line - 1];

  std::cerr << filename << ":" << line << ":" << column << ": " << BIRED <<"Runtime error: " << RESET
            << errorMsg << std::endl;

  std::cerr << "    " << line << " | "  << sourceLine << std::endl;
  std::cerr << "      | " << std::endl;
}

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


void execerror(std::string errorMessage1,std::string errorMessage2)
{
 // syntaxWarning(errorMessage1,errorMessage2); 

 longjmp(begin,0); /* return to a viable state */
}

void fpecatch(int signum)     
{
 execerror("Run time","floating point error");
}

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



