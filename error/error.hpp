/*! 
  \file error.hpp
  \brief Prototypes of error recovery functions 
*/

#ifndef _ERROR_HPP_
#define _ERROR_HPP_

#include <string>

/*! 
	\brief  Parser error recovery function
	\return void
	\param  errorMessage: Parser error message
	\sa     warning
*/
void yyerror(std::string errorMessage);

/*!
  \brief Shows a lexical warning message with detailed information.

  \param filename    Name of the source file where the error occurred.
  \param line        Line number of the error location.
  \param column      Column number (character position) where the error starts or ends.
  \param token       The lexical token that caused the warning.
  \param errorMsg    Description of the lexical error or warning message.

  \sa yyerror, parserWarning
*/
void lexicalWarning(const std::string& filename,
             int line,
             int column,
             const std::string& token,
             const std::string& errorMsg);


/*!
  \brief Shows a semantic error message with detailed information.

  \param filename    Name of the source file where the error occurred.
  \param line        Line number of the error location.
  \param column      Column number (character position) where the error occurred.
  \param errorMsg    Description of the parser error.
  \param suggestion  A hint or suggestion to help fix the error.

  \sa lexicalWarning, yyerror
*/
void semanticWarning(const std::string& filename,
             int line,
             int column,
             const std::string& errorMsg,
             const std::string& suggestion);

void runtimeWarning(const std::string& filename,
             int line,
             int column,
             const std::string& errorMsg,
             const std::string& suggestion);


/*! 
	\brief  Run time error recovery function
	\return void
	\param  errorMessage1: first error message
	\param  errorMessage2: second error message
	\sa     warning, longjmp
*/
void execerror(std::string errorMessage1,std::string errorMessage2);


/*! 
	\brief  Run time error recovery function
	\return void
	\param  p 
	\sa     warning
*/
void fpecatch(int p);

/*! 
	\brief  Control EDOM or ERANGE errors
	\param  d: double
	\param  s: 
	\return If an EDOM or ERANGE error has occurred, an error message is displayed; otherwise it returns the value "d"
	\sa     execerror
*/
double errcheck(double d, std::string s);


#endif 
