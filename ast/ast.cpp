/*!	
	\file    ast.cpp
	\brief   Code of funcitons of AST clas
	\author  
	\date    2018-12-13
	\version 1.0
*/

#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>
#include <sstream>
#include <cstdlib>
#include <ctime>
// Para usar la funciones pow y std::abs
#include <cmath>

#include "ast.hpp"

#include "../table/table.hpp"

// warning
#include "../error/error.hpp"
#include "../includes/globals.hpp"

// Macros for the screen
#include "../includes/macros.hpp"

// 
#include "../table/numericVariable.hpp"
#include "../table/stringVariable.hpp"
#include "../table/logicalVariable.hpp"

#include "../table/numericConstant.hpp"
#include "../table/logicalConstant.hpp"

#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter1.hpp"
#include "../table/builtinParameter2.hpp"

#include "../parser/interpreter.tab.h"



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

extern lp::Table table; //!< Reference to the Table of Symbols


extern lp::AST *root; //!< Reference to the object at the base of the AST


///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::VariableNode::getType() 
{ 
	// Get the identifier in the table of symbols as Variable
	lp::Variable *var = (lp::Variable *) table.getSymbol(this->_id);

	// Return the type of the Variable
	return var->getType();
}


void lp::VariableNode::printAST() 
{
  std::cout << "VariableNode: " << this->_id;
  std::cout << " (Type: " << this->getType() << ")" << std::endl;
}


double lp::VariableNode::evaluateNumber() 
{ 
	double result = 0.0;

	if (this->getType() == NUMBER)
	{
		// Get the identifier in the table of symbols as NumericVariable
		lp::NumericVariable *var = (lp::NumericVariable *) table.getSymbol(this->_id);

		// Copy the value of the NumericVariable
		result = var->getValue();
	}
	else
	{	
        errorMsg = "Variable is not numeric.";
        suggestion = "Check that the variable is assigned a numeric value before using it in a numeric expression.";
        semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
                 suggestion);
	}

	// Return the value of the NumericVariable
	return result;
}


bool lp::VariableNode::evaluateBool() 
{ 
	bool result = false;

	if (this->getType() == BOOL)
	{
		// Get the identifier in the table of symbols as LogicalVariable
		lp::LogicalVariable *var = (lp::LogicalVariable *) table.getSymbol(this->_id);

		// Copy the value of the LogicalVariable
		result = var->getValue();
	}
	else
	{
        errorMsg = "Variable is not bool.";
        
        suggestion = "Check that the variable is assigned a bool value before using it in a bool expression.";
        semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
                 suggestion);
	}

	// Return the value of the LogicalVariable
	return result;
}


std::string lp::VariableNode::evaluateString() 
{ 
	std::string result;

	if (this->getType() == STRING)
	{
		// Get the identifier in the table of symbols as StringVariable
		lp::StringVariable *var = (lp::StringVariable *) table.getSymbol(this->_id);

		// Copy the value of the StringVariable
		result = var->getValue();
	}
	else
	{
        errorMsg = "Variable is not string.";
        
        suggestion = "Check that the variable is assigned a string value before using it in a string expression.";
        semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
                 suggestion);
	}

	// Return the value of the StringVariable
	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ConstantNode::printAST() 
{
  std::cout << "ConstantNode: " << this->_id;
  std::cout << " (Type: " << this->getType() << ")" << std::endl;
}

int lp::ConstantNode::getType() 
{ 
	// Get the identifier in the table of symbols as Constant
	lp::Constant *var = (lp::Constant *) table.getSymbol(this->_id);

	// Return the type of the Constant
	return var->getType();
}


double lp::ConstantNode::evaluateNumber() 
{ 
	double result = 0.0;

	if (this->getType() == NUMBER)
	{
		// Get the identifier in the table of symbols as NumericConstant
		lp::NumericConstant *constant = (lp::NumericConstant *) table.getSymbol(this->_id);

		// Copy the value of the NumericConstant
		result = constant->getValue();
	}
	else
	{
		errorMsg = "Constant is not numeric.";
		
		suggestion = "Check that the constant is assigned a numeric value before using it in a numeric expression.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
	}

	// Return the value of the NumericVariable
	return result;
}

bool lp::ConstantNode::evaluateBool() 
{ 
	bool result = false;

	if (this->getType() == BOOL)
	{
		// Get the identifier in the table of symbols as LogicalConstant
		lp::LogicalConstant *constant = (lp::LogicalConstant *) table.getSymbol(this->_id);

		// Copy the value of the LogicalConstant
		result = constant->getValue();
	}
	else
	{
		errorMsg = "Constant is not bool.";
		
		suggestion = "Check that the constant is assigned a bool value before using it in a bool expression.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
	}

	// Return the value of the LogicalVariable
	return result;
}


//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
 

int lp::NumberNode::getType()
{
	return NUMBER;
}


void lp::NumberNode::printAST()
{
  std::cout << "NumberNode: " << this->_number << std::endl;
}

double lp::NumberNode::evaluateNumber() 
{ 
    return this->_number; 
}

//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
 

int lp::StringNode::getType()
{
	return STRING;
}

void lp::StringNode::printAST()
{
    std::cout << "StringNode: " << this->_string << std::endl;
}

std::string lp::StringNode::evaluateString()
{
    return this->_string;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
int lp::NumericUnaryOperatorNode::getType()
{
	int result;

	if(this->_exp->getType() == NUMBER)
	{
		result = NUMBER;
	}
	else
	{
		// warning("Runtime error: incompatible types for", "Numeric Unary Operator");
		errorMsg = "Incompatible types for \"Numeric Unary Operator\"";
		
		suggestion = "Check that the expression is assigned a numeric value before using it in a numeric operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::LogicalUnaryOperatorNode::getType()
{
	int result;

	if(this->_exp->getType() == BOOL)
	{
		result = BOOL;
	}
	else
	{
		errorMsg = "Incompatible types for \"Logical Unary Operator\"";
		
		suggestion = "Check that the expression is assigned a boolean value before using it in a logical operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
	}
	
	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::NumericOperatorNode::getType()
{
	int result = 0;
		
	if ( (this->_left->getType() == NUMBER) and (this->_right->getType() == NUMBER) )
		result = NUMBER;
	else
    {
		errorMsg = "Incompatible types for \"Numeric operator\"";
		suggestion = "Check that both operands are numeric before using them in a numeric operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
    }
	return	result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::StringOperatorNode::getType()
{
	int result = 0;
		
	if ( (this->_left->getType() == STRING) and (this->_right->getType() == STRING))
		result = STRING;
	else {
		errorMsg = "Incompatible types for \"String Operator\"";
		
		suggestion = "Check that both operands are strings before using them in a string operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg,
				 suggestion);
        }

	return	result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


int lp::RelationalOperatorNode::getType()
{
	int result = 0;
		
	if ( (this->_left->getType() == NUMBER) and (this->_right->getType() == NUMBER))
		result = BOOL;
	else if ( (this->_left->getType() == BOOL) and (this->_right->getType() == BOOL))
		result = BOOL;
	else
	{
		errorMsg = "Incompatible types for \"Relational Operator\"";
		suggestion = "Check that both operands are of the same type before using them in a relational operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				suggestion);
	}
	return	result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::LogicalOperatorNode:: getType()
{
	int result = 0;
		
	if ( (this->_left->getType() == BOOL) and (this->_right->getType() == BOOL))
	{
		// 
		result = BOOL;
	}
	else
	{
		errorMsg = "Incompatible types for \"Logical Operator\"";
		suggestion = "Check that both operands are boolean before using them in a logical operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
	}

	return	result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::UnaryMinusNode::printAST() 
{
  std::cout << "UnaryMinusNode: -"  << std::endl;
  std::cout << "\t"; 
  this->_exp->printAST();
}

double lp::UnaryMinusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the type of the expression
	if (this->getType() == NUMBER)
	{
		// Minus
		result = - this->_exp->evaluateNumber();
	}
	else
	{
		errorMsg = "Expression is not numeric in UnaryMinusNode.";
		suggestion = "Check that the expression is assigned a numeric value before using it in a numeric operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
	}

  return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::UnaryPlusNode::printAST() 
{
  std::cout << "UnaryPlusNode: +"  << std::endl;
  std::cout << "\t"; 
  this->_exp->printAST();
}

double lp::UnaryPlusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the type of the expression
	if (this->getType() == NUMBER)
	{
		result = this->_exp->evaluateNumber();
	}
	else
	{
		errorMsg = "Expression is not numeric in UnaryPlusNode.";
		suggestion = "Check that the expression is assigned a numeric value before using it in a numeric operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
	}

  return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PlusNode::printAST() 
{
  std::cout << "PlusNode: +"  << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

double lp::PlusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		result = this->_left->evaluateNumber() + this->_right->evaluateNumber();
	}
	else
	{
		errorMsg = "Expressions are not numeric in PlusNode.";
		suggestion = "Check that both expressions are assigned numeric values before using them in a numeric operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
	}

  return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::MinusNode::printAST() 
{
  std::cout << "MinusNode: -"  << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

double lp::MinusNode::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		result = this->_left->evaluateNumber() - this->_right->evaluateNumber();
	}
	else
	{
		errorMsg = "Expressions are not numeric in MinusNode.";
		suggestion = "Check that both expressions are assigned numeric values before using them in a numeric operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
	}

  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::MultiplicationNode::printAST() 
{
  std::cout << "MultiplicationNode: *"  << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

double lp::MultiplicationNode::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		result = this->_left->evaluateNumber() * this->_right->evaluateNumber();
	}
	else
	{
		errorMsg = "Expressions are not numeric in MultiplicationNode.";
		suggestion = "Check that both expressions are assigned numeric values before using them in a numeric operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
	}

  return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::DivisionNode::printAST()
{
  std::cout << "DivisionNode: /" << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

double lp::DivisionNode::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		double leftNumber, rightNumber;

		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();
	
		// The divisor is not zero
    	if(std::abs(rightNumber) > ERROR_BOUND)
		{
				result = leftNumber / rightNumber;
		}
		else
		{
			errorMsg = "Division by zero in DivisionNode.";
			suggestion = "Check that the divisor is not zero before using it in a division operation.";
			semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
					 suggestion);
		}
	}
	else
	{
		errorMsg = "Expressions are not numeric in DivisionNode.";
		suggestion = "Check that both expressions are assigned numeric values before using them in a numeric operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
	}

  return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::IntegerDivisionNode::printAST()
{
  std::cout << "IntegerDivisionNode: /" << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

double lp::IntegerDivisionNode::evaluateNumber() 
{
	double result = 0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		double leftNumber, rightNumber;

		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();
	
		// The divisor is not zero
    	if(std::abs(rightNumber) > ERROR_BOUND)
		{
			int leftInt = static_cast<int>(leftNumber);
			int rightInt = static_cast<int>(rightNumber);

			if (rightInt != 0)
			{
				result = static_cast<double>(leftInt / rightInt);
			}
			else
			{
				errorMsg = "Division by zero in IntegerDivisionNode.";
				
				suggestion = "Check that the divisor is not zero before using it in an integer division operation.";
				semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
						 suggestion);
			}
		}
		else
		{
			// warning("Runtime error", "Division by zero");
			errorMsg = "Division by zero in IntegerDivisionNode.";
			
			suggestion = "Check that the divisor is not zero before using it in an integer division operation.";
			semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
					 suggestion);
		}
	}
	else
	{
		errorMsg = "Expressions are not numeric in IntegerDivisionNode.";
		
		suggestion = "Check that both expressions are assigned numeric values before using them in a numeric operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ConcatenationNode::printAST()
{
  std::cout << "ConcatenationNode: /" << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

std::string lp::ConcatenationNode::evaluateString() 
{
	std::string result;

	// Verifica que ambos operandos sean de tipo STRING
	if (this->getType() == STRING)
	{
		std::string leftStr = this->_left->evaluateString();
		std::string rightStr = this->_right->evaluateString();

		result = leftStr + rightStr;
	}
	else
	{
		errorMsg = "Expressions are not strings in ConcatenationNode.";
		
		suggestion = "Check that both expressions are assigned string values before using them in a string concatenation operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ModuloNode::printAST()
{
  std::cout << "ModuloNode: %" << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

double lp::ModuloNode::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		double leftNumber, rightNumber;

		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();
	
    	if(std::abs(rightNumber) > ERROR_BOUND)
				result = (int) leftNumber % (int) rightNumber;
		else
        {
			// warning("Runtime error", "Division by zero");
			errorMsg = "Division by zero in ModuloNode.";
			
			suggestion = "Check that the divisor is not zero before using it in a modulo operation.";
			semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
					 suggestion);
        }
	}
	else
	{
		errorMsg = "Expressions are not numeric in ModuloNode.";
		
		suggestion = "Check that both expressions are assigned numeric values before using them in a numeric operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
	}

  return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PowerNode::printAST() 
{
  std::cout << "PowerNode: ^"  << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

double lp::PowerNode::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		result = pow(this->_left->evaluateNumber(), this->_right->evaluateNumber());
	}
	else
	{
		errorMsg = "Expressions are not numeric in PowerNode.";
		
		suggestion = "Check that both expressions are assigned numeric values before using them in a power operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
	}

  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
int lp::BuiltinFunctionNode_0::getType()
{
	return	NUMBER;
}


void lp::BuiltinFunctionNode_0::printAST() 
{
  std::cout << "BuiltinFunctionNode_0: "  << std::endl;
  std::cout << "\t";
  std::cout << this->_id << std::endl;
}

double lp::BuiltinFunctionNode_0::evaluateNumber() 
{
	// Get the identifier in the table of symbols as BuiltinParameter0
	lp::BuiltinParameter0 *f = (lp::BuiltinParameter0 *) table.getSymbol(this->_id);

	// Apply the function and copy the result
   	return f->getFunction()();
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::BuiltinFunctionNode_1::getType()
{
	int result = 0;
		
	if (this->_exp->getType() == NUMBER)
		result = NUMBER;
	else
		errorMsg = "Incompatible type for \"BuiltinFunctionNode_1\"";
		
		suggestion = "Check that the expression is assigned a numeric value before using it in a numeric operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);

	return	result;
}

void lp::BuiltinFunctionNode_1::printAST() 
{
  std::cout << "BuiltinFunctionNode_1: "  << std::endl;
  std::cout << "\t";
  std::cout << this->_id << std::endl;  
  std::cout << "\t";
	this->_exp->printAST();
	std::cout << std::endl;
}

double lp::BuiltinFunctionNode_1::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the type of the expression
	if (this->getType() == NUMBER)
	{
		// Get the identifier in the table of symbols as BuiltinParameter1
		lp::BuiltinParameter1 *f = (lp::BuiltinParameter1 *) table.getSymbol( this->_id);

		// Apply the function to the parameter and copy the result
		result = f->getFunction()(this->_exp->evaluateNumber());
	}
	else
	{
		errorMsg = "Incompatible type of parameter for BuiltinFunctionNode_1";
		
		suggestion = "Check that the expression is assigned a numeric value before using it in a numeric operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::BuiltinFunctionNode_2::getType()
{
	int result = 0;
		
	if (this->_exp1->getType() == this->_exp2->getType())
		result = this->_exp1->getType();
	else
		errorMsg = "Incompatible types for \"BuiltinFunctionNode_2\"";
		
		suggestion = "Check that both expressions are assigned values of the same type before using them in a numeric operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);

	return	result;
}


void lp::BuiltinFunctionNode_2::printAST() 
{
  std::cout << "BuiltinFunctionNode_2: " << std::endl;
  std::cout << "\t";
  std::cout << this->_id << std::endl;
  std::cout << "\t";
  this->_exp1->printAST();
  std::cout << "\t";
	this->_exp2->printAST();
	std::cout << std::endl;
}

double lp::BuiltinFunctionNode_2::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		// Get the identifier in the table of symbols as BuiltinParameter2
		lp::BuiltinParameter2 *f = (lp::BuiltinParameter2 *) table.getSymbol(this->_id);

		// Apply the function to the parameters and copy the result
	  	result = f->getFunction()(this->_exp1->evaluateNumber(),this->_exp2->evaluateNumber());
	}
	else
	{
		errorMsg = "Incompatible types of parameters for BuiltinFunctionNode_2";
		
		suggestion = "Check that both expressions are assigned numeric values before using them in a numeric operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
	}

  return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::GreaterThanNode::printAST()
{
  std::cout << "GreaterThanNode: >" << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

bool lp::GreaterThanNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		double leftNumber, rightNumber;
		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		result = (leftNumber > rightNumber);
	}
	else
	{
		errorMsg = "Incompatible types of parameters for operator Greater than";
		
		suggestion = "Check that both expressions are assigned numeric values before using them in a relational operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::GreaterOrEqualNode::printAST()
{
  std::cout << "GreaterOrEqualNode: >= " << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

bool lp::GreaterOrEqualNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		double leftNumber, rightNumber;
		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		result = (leftNumber >= rightNumber);
	}
	else
	{
		errorMsg = "Incompatible types of parameters for operator Greater or equal than";
		
		suggestion = "Check that both expressions are assigned numeric values before using them in a relational operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::LessThanNode::printAST()
{
  std::cout << "LessThanNode: <" << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

bool lp::LessThanNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		double leftNumber, rightNumber;
		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		result = (leftNumber < rightNumber);
	}
	else
	{
		errorMsg = "Incompatible types of parameters for operator Less than";
		
		suggestion = "Check that both expressions are assigned numeric values before using them in a relational operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::LessOrEqualNode::printAST()
{
  std::cout << "LessOrEqualNode: <=" << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

bool lp::LessOrEqualNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		double leftNumber, rightNumber;
		leftNumber = this->_left->evaluateNumber();
		rightNumber = this->_right->evaluateNumber();

		result = (leftNumber <= rightNumber);
	}
	else
	{
		errorMsg = "Incompatible types of parameters for operator Less or equal than";
		
		suggestion = "Check that both expressions are assigned numeric values before using them in a relational operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::EqualNode::printAST()
{
  std::cout << "EqualNode: ==" << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

bool lp::EqualNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		switch(this->_left->getType()){
			case NUMBER:
				double leftNumber, rightNumber;
				leftNumber = this->_left->evaluateNumber();
				rightNumber = this->_right->evaluateNumber();

				// ERROR_BOUND to control the precision of real numbers
				result = ( std::abs(leftNumber - rightNumber) < ERROR_BOUND );
			break;
			case BOOL:
				bool leftBoolean, rightBoolean;
				leftBoolean = this->_left->evaluateBool();
				rightBoolean = this->_right->evaluateBool();

				// 
				result = (leftBoolean == rightBoolean);
				break;
		  default:
				// warning("Runtime error: incompatible types of parameters for ", 
								// "Equal operator");
				errorMsg = "Incompatible types of parameters for Equal operator";
				
				suggestion = "Check that both expressions are assigned values of the same type before using them in a relational operation.";
				semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
						 suggestion);
				break;
		}
	}
	else
	{
		// warning("Runtime error: incompatible types of parameters for ", 
						// "Equal operator");
		errorMsg = "Incompatible types of parameters for Equal operator";
		
		suggestion = "Check that both expressions are assigned values of the same type before using them in a relational operation.";
		
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::NotEqualNode::printAST()
{
  std::cout << "NotEqualNode: !=" << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

bool lp::NotEqualNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		switch(this->_left->getType()){
			case NUMBER:
				double leftNumber, rightNumber;
				leftNumber = this->_left->evaluateNumber();
				rightNumber = this->_right->evaluateNumber();

				// ERROR_BOUND to control the precision of real numbers
				result = ( std::abs(leftNumber - rightNumber) >= ERROR_BOUND );
			break;
			case BOOL:
				bool leftBoolean, rightBoolean;
				leftBoolean = this->_left->evaluateBool();
				rightBoolean = this->_right->evaluateBool();

				// 
				result = (leftBoolean != rightBoolean);
				break;
		  default:
				// warning("Runtime error: incompatible types of parameters for ", 
								// "Not Equal operator");
				errorMsg = "Incompatible types of parameters for Not Equal operator";
				
				suggestion = "Check that both expressions are assigned values of the same type before using them in a relational operation.";
				semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
						 suggestion);
				break;
		}
	}
	else
	{
		// warning("Runtime error: incompatible types of parameters for ", "Not Equal operator");
		errorMsg = "Incompatible types of parameters for Not Equal operator";
		
		suggestion = "Check that both expressions are assigned values of the same type before using them in a relational operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AndNode::printAST()
{
  std::cout << "AndNode: &&" << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

bool lp::AndNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		bool leftBool, rightBool;

		leftBool = this->_left->evaluateBool();
		rightBool = this->_right->evaluateBool();

		result = leftBool and rightBool;
	}
	else
	{
		// warning("Runtime error: incompatible types of parameters for ", "operator And");
		errorMsg = "Incompatible types of parameters for operator And";
		
		suggestion = "Check that both expressions are assigned boolean values before using them in a logical operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::OrNode::printAST()
{
  std::cout << "OrNode: ||" << std::endl;
  std::cout << "\t"; 
	this->_left->printAST();
	std::cout << "\t"; 
	this->_right->printAST();
}

bool lp::OrNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		bool leftBool, rightBool;

		leftBool = this->_left->evaluateBool();
		rightBool = this->_right->evaluateBool();

		result = leftBool or rightBool;
	}
	else
	{
		// warning("Runtime error: incompatible types of parameters for ", "operator Or");
		errorMsg = "Incompatible types of parameters for operator Or";
		
		suggestion = "Check that both expressions are assigned boolean values before using them in a logical operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::NotNode::printAST()
{
  std::cout << "NotNode: !" << std::endl;
  std::cout << "\t";
  this->_exp->printAST();
}

bool lp::NotNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		result = not this->_exp->evaluateBool();
	}
	else
	{
		// warning("Runtime error: incompatible types of parameters for ", "operator Not");
		errorMsg = "Incompatible types of parameters for operator Not";
		
		suggestion = "Check that the expression is assigned a boolean value before using it in a logical operation.";
		semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AssignmentStmt::printAST() 
{
  std::cout << "assignment_node: ="  << std::endl;
  std::cout << "\t";
  std::cout << this->_id << std::endl;
  std::cout << "\t";

  // Check the expression
	if (this->_exp != NULL)
	{
	  this->_exp->printAST();
    std::cout << std::endl;
  }
  // this->_asgn is not NULL: multiple assingment
  else 
    this->_asgn->printAST();

}

void lp::AssignmentStmt::evaluate() 
{
	/* Get the identifier in the table of symbols as Variable */
	/* 
		a = 2;
		a = b = 2;

		a: firstVar
		b: secondVar
	*/
	lp::Variable *firstVar = (lp::Variable *) table.getSymbol(this->_id);

	// Check the expression
	if (this->_exp != NULL)
	{
		// Check the type of the expression of the asgn
		switch(this->_exp->getType())
		{
			case NUMBER:
			{
				double value;
				// evaluate the expression as NUMBER
			 	value = this->_exp->evaluateNumber();

				// Check the type of the first varible
				if (firstVar->getType() == NUMBER)
				{
				  	// Get the identifier in the table of symbols as NumericVariable
					lp::NumericVariable *v = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value to the identifier in the table of symbols
					v->setValue(value);
				}
				// The type of variable is not NUMBER
				else
				{
					// Delete the variable from the table of symbols 
					table.eraseSymbol(this->_id);

					// Insert the variable in the table of symbols as NumericVariable 
					// with the type NUMBER and the value 
					lp::NumericVariable *v = new lp::NumericVariable(this->_id,
											VARIABLE,NUMBER,value);
					table.installSymbol(v);
				}
			}
			break;
			case STRING:
			{
				std::string value = this->_exp->evaluateString();

				if (firstVar->getType() == STRING)
				{
					lp::StringVariable *v = (lp::StringVariable *) table.getSymbol(this->_id);
					v->setValue(value);
				}
				else
				{
					table.eraseSymbol(this->_id);

					lp::StringVariable *v = new lp::StringVariable(this->_id, VARIABLE, STRING, value);
					table.installSymbol(v);
				}
			}
			break;
			case BOOL:
			{
				bool value;
				// evaluate the expression as BOOL
			 	value = this->_exp->evaluateBool();

				if (firstVar->getType() == BOOL)
				{
				  	// Get the identifier in the table of symbols as LogicalVariable
					lp::LogicalVariable *v = (lp::LogicalVariable *) table.getSymbol(this->_id);

					// Assignment the value to the identifier in the table of symbols
					v->setValue(value);
				}
				// The type of variable is not BOOL
				else
				{
					// Delete the variable from the table of symbols 
					table.eraseSymbol(this->_id);

					// Insert the variable in the table of symbols as NumericVariable 
					// with the type BOOL and the value 
					lp::LogicalVariable *v = new lp::LogicalVariable(this->_id,
											VARIABLE,BOOL,value);
					table.installSymbol(v);
				}
			}
			break;

			default:
				errorMsg = "Incompatible type of expression for Assignment";
				
				suggestion = "Check that the expression is assigned a value of the correct type before using it in an assignment operation.";
				semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
						 suggestion);
				break;
		}

	}

	//////////////////////////////////////////////
	// Allow multiple assigment -> a = b = c = 2;

	else // this->_asgn is not NULL
	{
		// IMPORTANT
		//  evaluate the assigment child
		this->_asgn->evaluate();


		/* Get the identifier of the previous asgn in the table of symbols as Variable */
		lp::Variable *secondVar = (lp::Variable *) table.getSymbol(this->_asgn->_id);

		// Get the type of the variable of the previous asgn
		switch(secondVar->getType())
		{
			case NUMBER:
			{
				/* Get the identifier of the previous asgn in the table of symbols as NumericVariable */
				lp::NumericVariable *secondVar = (lp::NumericVariable *) table.getSymbol(this->_asgn->_id);
				// Check the type of the first variable
				if (firstVar->getType() == NUMBER)
				{
				/* Get the identifier of the first variable in the table of symbols as NumericVariable */
				lp::NumericVariable *firstVar = (lp::NumericVariable *) table.getSymbol(this->_id);
				  	// Get the identifier o f the in the table of symbols as NumericVariable
//					lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value of the second variable to the first variable
					firstVar->setValue(secondVar->getValue());

				}
				// The type of variable is not NUMBER
				else
				{
					// Delete the first variable from the table of symbols 
					table.eraseSymbol(this->_id);

					// Insert the first variable in the table of symbols as NumericVariable 
					// with the type NUMBER and the value of the previous variable 
					lp::NumericVariable *firstVar = new lp::NumericVariable(this->_id,
											VARIABLE,NUMBER,secondVar->getValue());
					table.installSymbol(firstVar);
				}
			}
			break;

			case BOOL:
			{
				/* Get the identifier of the previous asgn in the table of symbols as LogicalVariable */
				lp::LogicalVariable *secondVar = (lp::LogicalVariable *) table.getSymbol(this->_asgn->_id);
				// Check the type of the first variable
				if (firstVar->getType() == BOOL)
				{
				/* Get the identifier of the first variable in the table of symbols as LogicalVariable */
				lp::LogicalVariable *firstVar = (lp::LogicalVariable *) table.getSymbol(this->_id);
				  	// Get the identifier o f the in the table of symbols as NumericVariable
//					lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value of the second variable to the first variable
					firstVar->setValue(secondVar->getValue());

				}
				// The type of variable is not BOOL
				else
				{
					// Delete the first variable from the table of symbols 
					table.eraseSymbol(this->_id);

					// Insert the first variable in the table of symbols as NumericVariable 
					// with the type BOOL and the value of the previous variable 
					lp::LogicalVariable *firstVar = new lp::LogicalVariable(this->_id,
											VARIABLE,BOOL,secondVar->getValue());
					table.installSymbol(firstVar);
				}
			}
			break;

			// default:
				// warning("Runtime error: incompatible type of expression for ", "Assigment");
		}
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PrintStmt::printAST() 
{
  std::cout << "printASTStmt: printAST"  << std::endl;
  std::cout << "\t";
  this->_exp->printAST();
  std::cout << std::endl;
}


void lp::PrintStmt::evaluate() 
{

	switch(this->_exp->getType())
	{
		case NUMBER:
				std::cout << this->_exp->evaluateNumber() << std::endl;
				break;
		case BOOL:
			if (this->_exp->evaluateBool())
				std::cout << "true" << std::endl;
			else
				std::cout << "false" << std::endl;
			break;
        case STRING:
			std::cout << this->_exp->evaluateString() << std::endl;
			break;
        case VARIABLE:
            switch (this->_exp->getType())
            {
                case NUMBER:
                    std::cout << this->_exp->evaluateNumber() << std::endl;
                    break;
                case BOOL:
                    std::cout << (this->_exp->evaluateBool() ? "true" : "false") << std::endl;
                    break;
                case STRING:
                    std::cout << this->_exp->evaluateString() << std::endl;
                    break;
                default:
                    std::string errorMsg = "Unknown variable type in print statement.";
                    
                    std::string suggestion = "Check variable type before printing.";
                    semanticWarning(fileName, _lineNumber, columnNumber, errorMsg,  suggestion);
                    break;
            }
            break;
        
		default:
			std::string errorMsg = "Incompatible type for print statement.";
            
            std::string suggestion = "Ensure the expression is a number, boolean, or string.";
            semanticWarning(fileName, _lineNumber, columnNumber, errorMsg,  suggestion);
            break;
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ReadStmt::printAST() 
{
  std::cout << "ReadStmt: read"  << std::endl;
  std::cout << "\t";
  std::cout << this->_id;
  std::cout << std::endl;
}


void lp::ReadStmt::evaluate() 
{   
	double value;
	std::cin >> value;

	/* Get the identifier in the table of symbols as Variable */
	lp::Variable *var = (lp::Variable *) table.getSymbol(this->_id);

	// Check if the type of the variable is NUMBER
	if (var->getType() == NUMBER)
	{
		/* Get the identifier in the table of symbols as NumericVariable */
		lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);
						
		/* Assignment the read value to the identifier */
		n->setValue(value);
	}
	// The type of variable is not NUMBER
	else
	{
		// Delete $1 from the table of symbols as Variable
		table.eraseSymbol(this->_id);

			// Insert $1 in the table of symbols as NumericVariable 
		// with the type NUMBER and the read value 
		lp::NumericVariable *n = new lp::NumericVariable(this->_id, 
									  VARIABLE,NUMBER,value);

		table.installSymbol(n);
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ReadStringStmt::printAST() 
{
  std::cout << "ReadStringStmt: read"  << std::endl;
  std::cout << "\t";
  std::cout << this->_id;
  std::cout << std::endl;
}


void lp::ReadStringStmt::evaluate() 
{   
    std::string value;

    std::cin >> value;

    lp::Variable *var = (lp::Variable *) table.getSymbol(this->_id);

    if (var && var->getType() == STRING)
    {
        lp::StringVariable *strVar = (lp::StringVariable *) var;
        strVar->setValue(value);
    }
    else
    {
        table.eraseSymbol(this->_id);

        lp::StringVariable *strVar = new lp::StringVariable(this->_id, VARIABLE, STRING, value);
        table.installSymbol(strVar);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::EmptyStmt::printAST() 
{
  // std::cout << "EmptyStmt "  << std::endl;
}

void lp::EmptyStmt::evaluate() 
{
  // Empty
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::IfStmt::printAST() 
{
  std::cout << "IfStmt: "  << std::endl;
  // Condition
  std::cout << "\t";
  this->_cond->printAST();

  std::cout << "\t";

    for (std::list<Statement*>::iterator stmtIter = _stmt1->begin(); stmtIter != _stmt1->end(); ++stmtIter) 
    {
        (*stmtIter)->printAST();
    }

    if(this->_stmt2 != NULL)
    {
        for (std::list<Statement*>::iterator stmtIter = _stmt2->begin(); stmtIter != _stmt2->end(); ++stmtIter) 
        {
            (*stmtIter)->printAST();
        }
    }

    std::cout << std::endl;
}


void lp::IfStmt::evaluate() 
{
    if (this->_cond->evaluateBool() == true)
    {
        for (std::list<Statement*>::iterator stmtIter = _stmt1->begin(); stmtIter != _stmt1->end(); ++stmtIter) 
        {
            (*stmtIter)->evaluate();
        }
    }
    else if(this->_stmt2 != NULL)
    {
        for (std::list<Statement*>::iterator stmtIter = _stmt2->begin(); stmtIter != _stmt2->end(); ++stmtIter) 
        {
            (*stmtIter)->evaluate();
        }
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::WhileStmt::printAST() 
{
  std::cout << "WhileStmt: "  << std::endl;
  // Condition
  std::cout << "\t";
  this->_cond->printAST();

  // Body of the while loop
  std::cout << "\t";
  for (std::list<Statement*>::iterator stmtIter = _stmt->begin(); stmtIter != _stmt->end(); ++stmtIter) 
  {
      (*stmtIter)->printAST();
  }

  std::cout << std::endl;
}


void lp::WhileStmt::evaluate() 
{
  // While the condition is true. the body is run 
  while (this->_cond->evaluateBool() == true)
  {	
	    for (std::list<Statement*>::iterator stmtIter = _stmt->begin(); stmtIter != _stmt->end(); ++stmtIter) 
        {
            (*stmtIter)->evaluate();
        }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::RepeatStmt::printAST() 
{
  std::cout << "RepeatStmt: "  << std::endl;
  // Condition
  std::cout << "\t";
  this->_cond->printAST();

  // Body of the while loop
  std::cout << "\t";
  for (std::list<Statement*>::iterator stmtIter = _stmt->begin(); stmtIter != _stmt->end(); ++stmtIter) 
  {
      (*stmtIter)->printAST();
  }

  std::cout << std::endl;
}


void lp::RepeatStmt::evaluate() 
{
  // While the condition is false. the body is run 
  do {
    for (std::list<Statement*>::iterator stmtIter = _stmt->begin(); stmtIter != _stmt->end(); ++stmtIter) {
        (*stmtIter)->evaluate();
     }
  } while (!_cond->evaluateBool());
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ForStmt::printAST()
{
    std::cout << "ForStmt: " << std::endl;
    // Identifier to initialize
    std::cout << "\t";
    std::cout << this->_id;

    // From expresion
    std::cout << "\t";
    this->_from->printAST();

    // To expresion
    std::cout << "\t";
    this->_to->printAST();

    // Block statement
    std::cout << "\t";

    std::cout << std::endl;
}

void lp::ForStmt::evaluate()
{
    // Validate that _from is a numeric expression
    if (this->_from->getType() != NUMBER)
    {
        errorMsg = "'from' value is not numeric.";
        suggestion = "Ensure the 'from' expression evaluates to a numeric value.";
        semanticWarning(fileName, _lineNumber, columnNumber, errorMsg,
                     suggestion);
        return;
    }

    // Validate that _to is a numeric expression
    if (this->_to->getType() != NUMBER)
    {
        errorMsg = "'to' value is not numeric.";
        
        suggestion = "Ensure the 'to' expression evaluates to a numeric value.";
        semanticWarning(fileName, _lineNumber, columnNumber, errorMsg,
                     suggestion);
    }

    // If step is provided, validate it is numeric
    if (this->_step != NULL && this->_step->getType() != NUMBER)
    {
        errorMsg = "'step' value is not numeric.";
        
        suggestion = "Ensure the 'step' expression evaluates to a numeric value.";
        semanticWarning(fileName, _lineNumber, columnNumber, errorMsg,
                     suggestion);
    }

    // Check that the interval is valid (to >= from)
    if (this->_to->evaluateNumber() < this->_from->evaluateNumber())
    {
        errorMsg = "Invalid interval: loop upper bound is less than lower bound.";
        
        suggestion = "Consider swapping 'from' and 'to' values or checking loop direction.";
        semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
                 suggestion);
    }

    lp::NumericVariable *loopVar = NULL;

    // Check if the loop variable already exists in the symbol table
    if (!table.lookupSymbol(this->_id))
    {
        // If not, create it initialized to 'from' value
        loopVar = new lp::NumericVariable(this->_id, VARIABLE, NUMBER, this->_from->evaluateNumber());
        table.installSymbol(loopVar);
    }
    else
    {
        // Get the existing symbol for the loop variable
        lp::Variable *symbol = (lp::Variable *)table.getSymbol(this->_id);

        if (symbol->getType() == NUMBER)
        {
            // If symbol is numeric, use it as the loop variable
            loopVar = (lp::NumericVariable *)symbol;
        }
        else
        {
            // If symbol is not numeric, erase it and recreate as numeric
            table.eraseSymbol(this->_id);
            loopVar = new lp::NumericVariable(this->_id, VARIABLE, NUMBER);
            table.installSymbol(loopVar);
        }

        // Initialize the loop variable value to 'from'
        loopVar->setValue(this->_from->evaluateNumber());
    }

    // Default step value
    double stepValue = 1.0;

    // Validate and assign step value if provided
    if (this->_step != NULL)
    {
        double evaluatedStep = this->_step->evaluateNumber();

        if (evaluatedStep <= ERROR_BOUND)
        {
            errorMsg = "Step value must be a numeric constant greater than the error bound.";
            
            suggestion = "Verify that the step value is numeric and exceeds the defined error bound before use.";
            semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
                 suggestion);
        }
        else
        {
            stepValue = evaluatedStep;
        }
    }

    // Loop execution: increment loopVar by stepValue until it passes 'to'
    for (; loopVar->getValue() <= this->_to->evaluateNumber(); loopVar->setValue(loopVar->getValue() + stepValue))
    {
        // Evaluate all statements inside the loop body
        for (std::list<Statement*>::iterator stmtIter = _stmt->begin(); stmtIter != _stmt->end(); ++stmtIter)
        {
            (*stmtIter)->evaluate();
        }
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::CaseStmt::printAST() {
	std::cout << "CaseStmt: case" << std::endl;
	std::cout << "\t";
	std::cout << std::endl;
}

void lp::CaseStmt::evaluate() {

    std::list<Statement*>::iterator stmtIter;

    for(stmtIter = this->_stmt->begin(); stmtIter != this->_stmt->end(); stmtIter++)
    {
        (*stmtIter)->evaluate();
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::SwitchStmt::printAST() {
	std::cout << "SwitchStmt: switch" << std::endl;
	std::cout << "\t";
	std::cout << std::endl;
}

void lp::SwitchStmt::evaluate() {
    double condValue = this->_exp->evaluateNumber();
    bool matched = false;

    for (std::list<lp::CaseStmt *>::iterator it = this->_caselist->begin(); it != this->_caselist->end(); ++it)
    {
        double caseValue = (*it)->getExp()->evaluateNumber();

        if (fabs(condValue - caseValue) < ERROR_BOUND)
        {
            matched = true;
            std::list<lp::Statement *> *stmts = (*it)->getStatements();

            for (std::list<lp::Statement *>::iterator s = stmts->begin(); s != stmts->end(); ++s)
            {
                (*s)->evaluate();
            }

            break;
        }
    }

    if (!matched && this->_defaultlist != NULL)
    {
        for (std::list<lp::Statement *>::iterator s = this->_defaultlist->begin(); s != this->_defaultlist->end(); ++s)
        {
            (*s)->evaluate();
        }
    }
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::RandomNode::printAST() {
	std::cout << "RandomNode: random" << std::endl;
	std::cout << "\t";
	this->_min->printAST();
	std::cout << "\t";
	this->_max->printAST();
	std::cout << std::endl;
}

int lp::RandomNode::getType() {
    return NUMBER;
}

double lp::RandomNode::evaluateNumber() {
	std::srand(std::time(NULL));

    double minVal, maxVal;

    if(_min->getType() == NUMBER && _max->getType() == NUMBER)
    {
        minVal = static_cast<int>(_min->evaluateNumber());
        maxVal = static_cast<int>(_max->evaluateNumber());

		if (minVal > maxVal) {
			errorMsg = "Invalid range for random number generation: min is greater than max.";
			suggestion = "Ensure that the minimum value is less than or equal to the maximum value.";
			semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, suggestion);
		}

        int escala = 1000;
        int minEscalado = static_cast<int>(minVal * escala);
        int maxEscalado = static_cast<int>(maxVal * escala);

        if (minEscalado > maxEscalado) std::swap(minEscalado, maxEscalado);

        int valorAleatorio = minEscalado + std::rand() % (maxEscalado - minEscalado + 1);
        return static_cast<double>(valorAleatorio) / escala;
    }
	else if(_min->getType() == STRING && _max->getType() == STRING)
	{
		// Get the existing symbols for the min and max variables
		lp::Variable *symbolMin = (lp::Variable *)table.getSymbol(this->_min->evaluateString());
		lp::Variable *symbolMax = (lp::Variable *)table.getSymbol(this->_max->evaluateString());

		lp::NumericVariable *randomVarMin;
		lp::NumericVariable *randomVarMax;

		if (symbolMin->getType() == NUMBER)
		{
			// If symbol is numeric, use it as the loop variable
			randomVarMin = (lp::NumericVariable *)symbolMin;
		}

		if (symbolMax->getType() == NUMBER)
		{
			// If symbol is numeric, use it as the loop variable
			randomVarMax = (lp::NumericVariable *)symbolMax;
		}

		minVal = randomVarMin->getValue();
		maxVal = randomVarMax->getValue();

        // Generar un número aleatorio con dos decimales entre minVal y maxVal
        int escala = 1000; // Para dos decimales
        int minEscalado = static_cast<int>(minVal * escala);
        int maxEscalado = static_cast<int>(maxVal * escala);

        if (minEscalado > maxEscalado) std::swap(minEscalado, maxEscalado);

        int valorAleatorio = minEscalado + std::rand() % (maxEscalado - minEscalado + 1);
        return static_cast<double>(valorAleatorio) / escala;
    }
    else
    {
        errorMsg = "Invalid types for Place statement.";
        suggestion = "Ensure both x and y expressions evaluate to numeric values or valid variable names.";
        semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
                    suggestion);
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::BlockStmt::printAST() 
{
  std::list<Statement *>::iterator stmtIter;

  std::cout << "BlockStmt: "  << std::endl;

  for (stmtIter = this->_stmts->begin(); stmtIter != this->_stmts->end(); stmtIter++) 
  {
     (*stmtIter)->printAST();
  }
}


void lp::BlockStmt::evaluate() 
{
  std::list<Statement *>::iterator stmtIter;

  for (stmtIter = this->_stmts->begin(); stmtIter != this->_stmts->end(); stmtIter++) 
  {
    (*stmtIter)->evaluate();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ClearScreenStmt::printAST() 
{
  std::cout << "ClearScreenStmt: clear_screen" << std::endl;    
}

void lp::ClearScreenStmt::evaluate() 
{
  std::cout << CLEAR_SCREEN_TEXT;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PlaceStmt::printAST() 
{
  std::cout << "PlaceStmt: place" << std::endl;    
}

void lp::PlaceStmt::evaluate() 
{
  int x;
  int y;

  if(_x->getType() == NUMBER && _y->getType() == NUMBER)
  {
    x = _x->evaluateNumber();
    y = _y->evaluateNumber();
    PLACE(x, y);
  } 
  else if(_x->getType() == STRING && _y->getType() == STRING)
  {
    // Get the existing symbol for the loop variable
    lp::Variable *symbolX = (lp::Variable *)table.getSymbol(this->_x->evaluateString());
	lp::Variable *symbolY = (lp::Variable *)table.getSymbol(this->_y->evaluateString());

    lp::NumericVariable * placeVarX;
    lp::NumericVariable * placeVarY;

    if (symbolX->getType() == NUMBER)
    {
        // If symbol is numeric, use it as the loop variable
        placeVarX = (lp::NumericVariable *)symbolX;
    }

    if (symbolY->getType() == NUMBER)
    {
        // If symbol is numeric, use it as the loop variable
        placeVarY = (lp::NumericVariable *)symbolY;
    }

    placeVarX->setValue(this->_x->evaluateNumber());
    placeVarY->setValue(this->_x->evaluateNumber());

    x = placeVarX->getValue();
    y = placeVarY->getValue();

    PLACE(x, y);
  }
  else
  {
	errorMsg = "Invalid types for Place statement.";
	suggestion = "Ensure both x and y expressions evaluate to numeric values or valid variable names.";
	semanticWarning(fileName, _lineNumber, columnNumber, errorMsg, 
				 suggestion);
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::AST::printAST() 
{
  std::list<Statement *>::iterator stmtIter;

  for (stmtIter = stmts->begin(); stmtIter != stmts->end(); stmtIter++) 
  {
     (*stmtIter)->printAST();
  }
}



void lp::AST::evaluate() 
{
  std::list<Statement *>::iterator stmtIter;

  for (stmtIter = stmts->begin(); stmtIter != stmts->end(); stmtIter++) 
  {
    (*stmtIter)->evaluate();
  }
}