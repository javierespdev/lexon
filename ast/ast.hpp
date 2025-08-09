/*!	
	\file    ast.hpp
	\brief   Declaration of AST class
	\author  
	\date    2025-06-06
	\version 1.0
*/

#ifndef _AST_HPP_
#define _AST_HPP_

// Standard C++ libraries
#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>
#include <sstream>

#define ERROR_BOUND 1.0e-6  //!< Error bound for the comparison of real numbers.

namespace lp
{
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
/*!	
  \class   ExpNode
  \brief   Definition of atributes and methods of ExpNode class
  \warning Abstract class
*/
 class ExpNode 
{
  public:
	/*!	
		\brief   Type of the expression
		\warning Pure virtual function: must be redefined in the heir classes
		\return  int
		\sa		   printAST, evaluateNumber, evaluateBool
	*/
    virtual int getType() = 0;
    int _lineNumber; //!< Line number for error


	/*!	
		\brief   Print the AST for expression
		\warning Pure virtual function: must be redefined in the heir classes
		\return  void
		\sa		   getType, evaluateNumber, evaluateBool
	*/
    virtual void printAST() = 0;

	/*!	
		\brief   Evaluate the expression as NUMBER
		\warning Virtual function: could be redefined in the heir classes
		\return  double
		\sa		   getType, printAST, evaluateBool
	*/
    virtual double evaluateNumber()
	{
		return 0.0;
	}		


	/*!	
		\brief   Evaluate the expression as BOOL
		\warning Virtual function: could be redefined in the heir classes
		\return  bool
		\sa		   getType, printAST, evaluateNumber
	*/
    virtual bool evaluateBool()
	{
		return false;
	}

	/*!	
		\brief   Evaluate the expression as string
		\warning Virtual function: could be redefined in the heir classes
		\return  string
		\sa		 getType, printAST, evaluateString
	*/
    virtual std::string evaluateString()
	{
		return "";
	}

};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class VariableNode
  \brief Definition of atributes and methods of VariableNode class
  \note  VariableNode Class publicly inherits from ExpNode class
*/
class VariableNode : public ExpNode 
{
	private:
	  std::string _id; //!< Name of the VariableNode

	public:

	/*!   
		\brief Constructor of VariableNode
		\param value: double
		\param lineNumber: int
		\post  A new NumericVariableNode is created with the name of the parameter
		\note  Inline function
	*/
	  VariableNode(std::string const & value, int lineNumber)
		{
			this->_id = value; 
			this->_lineNumber = lineNumber;
		}

	/*!	
		\brief   Type of the Variable
		\return  int
		\sa		   printAST
	*/
	 int getType();

	/*!
		\brief   Print the AST for Variable
		\return  void
		\sa		   getType, evaluateNumber, evaluateBool
	*/
	  void printAST();

	/*!	
		\brief   Evaluate the Variable as NUMBER
		\return  double
		\sa		   printAST
	*/
	  double evaluateNumber();

	/*!	
		\brief   Evaluate the Variable as BOOL
		\return  bool
		\sa		   getType, printAST, evaluateNumber
	*/
	  bool evaluateBool();

	/*!	
		\brief   Evaluate the Variable as STRING
		\return  string
		\sa		   getType, printAST, evaluateNumber
	*/
	  std::string evaluateString();

	/*!	
		\brief   Get variable id
		\return  string
		\sa		   getType, printAST, evaluateNumber
	*/
	  std::string getId() {
        return _id;
      }
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class ConstantNode
  \brief Definition of atributes and methods of ConstantNode class
  \note  ConstantNode Class publicly inherits from ExpNode class
*/
class ConstantNode : public ExpNode 
{
	private:
	  std::string _id; //!< Name of the ConstantNode

	public:

	/*!		
		\brief Constructor of ConstantNode
		\param value: double
		\param lineNumber: int
		\post  A new ConstantNode is created with the name of the parameter
	*/
	  ConstantNode(std::string value, int lineNumber)
		{
			this->_id = value; 
			this->_lineNumber = lineNumber;
		}

	/*!	
		\brief   Type of the Constant
		\return  int
		\sa		   printAST, evaluateNumber, evaluateBool
	*/
	 int getType();

	/*!
		\brief   Print the AST for Constant
		\return  void
		\sa		   getType, evaluateNumber, evaluateBool
	*/
	  void printAST();

	/*!	
		\brief   Evaluate the Constant as NUMBER
		\return  double
		\sa		   getType, printAST, 
	*/
	  double evaluateNumber();

	/*!	
		\brief   Evaluate the Constant as BOOL
		\return  bool
		\sa		   getType, printAST, evaluateNumber, evaluateBool
	*/
	  bool evaluateBool();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class NumberNode
  \brief Definition of atributes and methods of NumberNode class
  \note  NumberNode Class publicly inherits from ExpNode class
*/
class NumberNode : public ExpNode 
{
 private: 	
   double _number; //!< \brief number of the NumberNode
 
 public:

/*!		
	\brief Constructor of NumberNode
	\param value: double
	\param lineNumber: int
	\post  A new NumberNode is created with the value of the parameter
	\note  Inline function
*/
  NumberNode(double value, int lineNumber)
	{
	    this->_number = value;
	    this->_lineNumber = lineNumber;
	}

	/*!	
	\brief   Get the type of the expression: NUMBER
	\return  int
	\sa		   printAST, evaluateNumber
	*/
	int getType();

	/*!
		\brief   Print the AST for expression
		\return  void
		\sa		   getType, evaluateNumber
	*/
	void printAST();

	/*!	
		\brief   Evaluate the expression
		\return  double
		\sa		   getType, printAST
	*/
	double evaluateNumber();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/**
 * @class StringNode
 * @brief Definition of attributes and methods of StringNode class
 * @note StringNode publicly inherits from ExpNode.
 */
class StringNode : public ExpNode
{
private:
    std::string _string; //!< \brief Stored string value of this node

public:
    /*!
        \brief Constructor of StringNode
        \param value: The string to store in this node
        \post  A StringNode object is created holding the given string
        \note  Inline implementation
    */
    StringNode(std::string value, int lineNumber)
    {
        this->_string = value;
        this->_lineNumber = lineNumber;
    }

    /*!
        \brief   Returns the type of this expression node (STRING)
        \return  int representing the node type
        \sa      printAST()
    */
    int getType();

    /*!
        \brief   Prints the string value of this node
        \return  void
        \sa      evaluateString()
    */
    void printAST();

    /*!
        \brief   Evaluates and returns the stored string
        \return  std::string containing the node's string value
        \sa      getType()
    */
    std::string evaluateString();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   UnaryOperatorNode
  \brief   Definition of atributes and methods of UnaryOperatorNode class
  \note    UnaryOperatorNode Class publicly inherits from ExpNode class
  \warning Abstract class, because it does not redefine the printAST method of ExpNode
*/
class UnaryOperatorNode : public ExpNode 
{
 protected:
  ExpNode *_exp;  //!< Child expression

 public:

/*!		
	\brief Constructor of UnaryOperatorNode links the node to it child,
           and stores the character representation of the operator.
	\param expression: pointer to ExpNode
	\post  A new OperatorNode is created with the parameters
	\note  Inline function
*/
  UnaryOperatorNode(ExpNode *expression, int lineNumber)
	{
		this->_exp = expression;
		this->_lineNumber = lineNumber;
	}

	/*!	
	\brief   Get the type of the child expression
	\return  int
	\sa		   printAST
	*/
	inline int getType()
	{
		return this->_exp->getType();
	}
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   NumericUnaryOperatorNode
  \brief   Definition of atributes and methods of UnaryOperatorNode class
  \note    UnaryOperatorNode Class publicly inherits from UnaryOperatorNode class
  \warning Abstract class, because it does not redefine the printAST method of ExpNode
*/
class NumericUnaryOperatorNode : public UnaryOperatorNode 
{
 public:

/*!		
	\brief Constructor of NumericUnaryOperatorNode uses UnaryOperatorNode's constructor as member initializer
	\param expression: pointer to ExpNode
	\post  A new NumericUnaryOperatorNode is created with the parameters
	\note  Inline function
*/
  NumericUnaryOperatorNode(ExpNode *expression, int lineNumber): UnaryOperatorNode(expression, lineNumber)
	{
		// Empty
	}

	/*!	
	\brief   Get the type of the child expression
	\return  int
	\sa		   printAST
	*/
	int getType();

};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   LogicalUnaryOperatorNode
  \brief   Definition of atributes and methods of UnaryOperatorNode class
  \note    UnaryOperatorNode Class publicly inherits from UnaryOperatorNode class
  \warning Abstract class, because it does not redefine the printAST method of ExpNode
*/
class LogicalUnaryOperatorNode : public UnaryOperatorNode 
{
 public:

/*!		
	\brief Constructor of LogicalUnaryOperatorNode uses UnaryOperatorNode's constructor as member initializer
	\param expression: pointer to ExpNode
	\post  A new NumericUnaryOperatorNode is created with the parameters
	\note  Inline function
*/
  LogicalUnaryOperatorNode(ExpNode *expression, int lineNumber): UnaryOperatorNode(expression, lineNumber)
	{
		// Empty
	}

	/*!	
	\brief   Get the type of the child expression
	\return  int
	\sa		   printAST
	*/
	int getType();

};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   UnaryMinusNode
  \brief   Definition of atributes and methods of UnaryMinusNode class
  \note    UnaryMinusNode Class publicly inherits from NumericUnaryOperatorNode class
*/
class UnaryMinusNode : public NumericUnaryOperatorNode 
{

 public:

/*!		
	\brief Constructor of UnaryMinusNode uses NumericUnaryOperatorNode's constructor as member initializer.
	\param expression: pointer to ExpNode
	\post  A new UnaryMinusNode is created with the parameter
	\note  Inline function: the NumericUnaryOperatorNode's constructor is used ad member initializer
*/
  UnaryMinusNode(ExpNode *expression, int lineNumber): NumericUnaryOperatorNode(expression, lineNumber) 
	{
		// empty
	} 

/*!
	\brief   Print the AST for expression
	\return  void
	\sa		   evaluateNumber
*/
  void printAST();

/*!	
	\brief   Evaluate the expression
	\return  double
	\sa		   printAST
*/
  double evaluateNumber();
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/*!	
  \class   UnaryPlusNode
  \brief   Definition of atributes and methods of UnaryPlusNode class
  \note    UnaryPlusNode Class publicly inherits from NumericUnaryOperatorNode class
*/
class UnaryPlusNode : public NumericUnaryOperatorNode 
{

 public:

/*!		
	\brief Constructor of UnaryPlusNode uses NumericUnaryOperatorNode's constructor as member initializer
	\param expression: pointer to ExpNode
	\post  A new UnaryPlusNode is created with the parameter
*/
  UnaryPlusNode(ExpNode *expression, int lineNumber): NumericUnaryOperatorNode(expression, lineNumber) 
	{
		// empty
	} 

/*!
	\brief   Print the AST for expression
	\return  void
	\sa		   evaluateNumber
*/
  void printAST();

/*!	
	\brief   Evaluate the expression
	\return  double
	\sa		   printAST
*/
  double evaluateNumber();
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/*!	
  \class   UnaryIncrementNode
  \brief   Definition of atributes and methods of UnaryIncrementNode class
  \note    UnaryIncrementNode Class publicly inherits from NumericUnaryOperatorNode class
*/
class UnaryIncrementNode : public NumericUnaryOperatorNode 
{

 public:

/*!		
	\brief Constructor of UnaryIncrementNode uses NumericUnaryOperatorNode's constructor as member initializer
	\param expression: pointer to ExpNode
	\post  A new UnaryIncrementNode is created with the parameter
*/
  UnaryIncrementNode(ExpNode *expression, int lineNumber): NumericUnaryOperatorNode(expression, lineNumber) 
	{
		// empty
	} 

/*!
	\brief   Print the AST for expression
	\return  void
	\sa		   evaluateNumber
*/
  void printAST();

/*!	
	\brief   Evaluate the expression
	\return  double
	\sa		   printAST
*/
  double evaluateNumber();
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/*!	
  \class   UnaryDecrementNode
  \brief   Definition of atributes and methods of UnaryDecrementNode class
  \note    UnaryDecrementNode Class publicly inherits from NumericUnaryOperatorNode class
*/
class UnaryDecrementNode : public NumericUnaryOperatorNode 
{

 public:

/*!		
	\brief Constructor of UnaryDecrementNode uses NumericUnaryOperatorNode's constructor as member initializer
	\param expression: pointer to ExpNode
	\post  A new UnaryDecrementNode is created with the parameter
*/
  UnaryDecrementNode(ExpNode *expression, int lineNumber): NumericUnaryOperatorNode(expression, lineNumber) 
	{
		// empty
	} 

/*!
	\brief   Print the AST for expression
	\return  void
	\sa		   evaluateNumber
*/
  void printAST();

/*!	
	\brief   Evaluate the expression
	\return  double
	\sa		   printAST
*/
  double evaluateNumber();
};


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/*!	
  \class   UnaryFactorialNode
  \brief   Definition of atributes and methods of UnaryFactorialNode class
  \note    UnaryFactorialNode Class publicly inherits from NumericUnaryOperatorNode class
*/
class UnaryFactorialNode : public NumericUnaryOperatorNode 
{

 public:

/*!		
	\brief Constructor of UnaryFactorialNode uses NumericUnaryOperatorNode's constructor as member initializer
	\param expression: pointer to ExpNode
	\post  A new UnaryFactorialNode is created with the parameter
*/
  UnaryFactorialNode(ExpNode *expression, int lineNumber): NumericUnaryOperatorNode(expression, lineNumber) 
	{
		// empty
	} 

/*!
	\brief   Print the AST for expression
	\return  void
	\sa		   evaluateNumber
*/
  void printAST();

/*!	
	\brief   Evaluate the expression
	\return  double
	\sa		   printAST
*/
  double evaluateNumber();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   OperatorNode
  \brief   Definition of atributes and methods of OperatorNode class
  \note    OperatorNode Class publicly inherits from ExpNode class
  \warning Abstract class, because it does not redefine the printAST and getType methods of ExpNode
*/
class OperatorNode : public ExpNode 
{
	protected:
		ExpNode *_left;    //!< Left expression
		ExpNode *_right;   //!< Right expression

	public:
	/*!		
		\brief Constructor of OperatorNode links the node to its children,
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new OperatorNode is created with the parameters
	*/
    OperatorNode(ExpNode *L, ExpNode *R, int lineNumber)
	{
	    this->_left  = L;
    	this->_right = R;
        this->_lineNumber = lineNumber;
	}

};



//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   NumericOperatorNode
  \brief   Definition of atributes and methods of NumericOperatorNode class
  \note    NumericOperatorNode Class publicly inherits from OperatorNode class
  \warning Abstract class, because it does not redefine the printAST method of ExpNode
*/
class NumericOperatorNode : public OperatorNode 
{
	public:

	/*!		
		\brief Constructor of NumericOperatorNode uses OperatorNode's constructor as members initializer
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new NumericOperatorNode is created with the parameters
	*/
    NumericOperatorNode(ExpNode *L, ExpNode *R, int lineNumber): OperatorNode(L,R,lineNumber) 
	{
		// Empty
	}

	/*!	
	\brief   Get the type of the children expressions
	\return  int
	*/
	int getType();
};


//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!
  \class   StringOperatorNode
  \brief   Definition of attributes and methods of StringOperatorNode class
  \note    StringOperatorNode Class publicly inherits from OperatorNode class
  \warning Abstract class, because it does not redefine the printAST method of ExpNode
*/
class StringOperatorNode : public OperatorNode 
{
	public:

	/*!
		\brief Constructor of StringOperatorNode uses OperatorNode's constructor as members initializer
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new StringOperatorNode is created with the parameters
	*/
	StringOperatorNode(ExpNode *L, ExpNode *R, int lineNumber): OperatorNode(L, R, lineNumber) 
	{
		// Empty
	}

	/*!
		\brief   Get the type of the children expressions
		\return  int
	*/
	int getType();
};

//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   RelationalOperatorNode
  \brief   Definition of atributes and methods of RelationalOperatorNode class
  \note    RelationalOperatorNode Class publicly inherits from OperatorNode class
  \warning Abstract class, because it does not redefine the printAST method of ExpNode
*/
class RelationalOperatorNode : public OperatorNode 
{
public:
/*!		
	\brief Constructor of RelationalOperatorNode uses OperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new RelationalOperatorNode is created with the parameters
*/
    RelationalOperatorNode(ExpNode *L, ExpNode *R, int lineNumber): OperatorNode(L,R,lineNumber) 
	{
		//	Empty
	}

	/*!	
	\brief   Get the type of the children expressions
	\return  int
	*/
	int getType();

};


//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   LogicalOperatorNode
  \brief   Definition of atributes and methods of LogicalOperatorNode class
  \note    NumericOperatorNode Class publicly inherits from OperatorNode class
  \warning Abstract class, because it does not redefine the printAST method of ExpNode
*/
class LogicalOperatorNode : public OperatorNode 
{
	public:

	/*!		
		\brief Constructor of LogicalOperatorNode uses OperatorNode's constructor as members initializer
		\param L: pointer to ExpNode
		\param R: pointer to ExpNode
		\post  A new NumericOperatorNode is created with the parameters
	*/
    LogicalOperatorNode(ExpNode *L, ExpNode *R, int lineNumber): OperatorNode(L,R,lineNumber) 
	{
		//	Empty
	}

	/*!	
	\brief   Get the type of the children expressions
	\return  int
	*/
	int getType();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   PlusNode
  \brief   Definition of atributes and methods of PlusNode class
  \note    PlusNode Class publicly inherits from NumericOperatorNode class 
		   and adds its own printAST and evaluate functions
*/
class PlusNode : public NumericOperatorNode 
{
  public:
/*!		
	\brief Constructor of PlusNode uses NumericOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new PlusNode is created with the parameter
*/
  PlusNode(ExpNode *L, ExpNode *R, int lineNumber) : NumericOperatorNode(L,R,lineNumber) 
  {
		// Empty
  }

/*!
	\brief   Print the AST for PlusNode
	\return  void
	\sa		   evaluateNumber
*/
  void printAST();

/*!	
	\brief   Evaluate the PlusNode
	\return  double
	\sa		   printAST
*/
  double evaluateNumber();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   MinusNode
  \brief   Definition of atributes and methods of MinusNode class
  \note    MinusNode Class publicly inherits from NumericOperatorNode class 
		       and adds its own printAST and evaluate functions
*/
class MinusNode : public NumericOperatorNode 
{
  public:

/*!		
	\brief Constructor of MinusNode uses NumericOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new MinusNode is created with the parameter
*/
  MinusNode(ExpNode *L, ExpNode *R, int lineNumber): NumericOperatorNode(L,R,lineNumber) 
  {
		// Empty
  }
/*!
	\brief   printAST the MinusNode
	\return  void
	\sa		   evaluateNumber
*/
  void printAST();

/*!	
	\brief   Evaluate the MinusNode
	\return  double
	\sa		   printAST
*/
  double evaluateNumber();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   MultiplicationNode
  \brief   Definition of atributes and methods of MultiplicationNode class
  \note    MultiplicationNode Class publicly inherits from NumericOperatorNode class 
		   and adds its own printAST and evaluate functions
*/
class MultiplicationNode : public NumericOperatorNode 
{
  public:

/*!		
	\brief Constructor of MultiplicationNode uses NumericOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new MultiplicationNode is created with the parameter
*/
  MultiplicationNode(ExpNode *L, ExpNode *R, int lineNumber): NumericOperatorNode(L,R,lineNumber) 
  {
		// Empty
  }
/*!
	\brief   printAST the MultiplicationNode
	\return  void
	\sa		   evaluateNumber
*/
  void printAST();

/*!	
	\brief   Evaluate the MultiplicationNode
	\return  double
	\sa		   printAST
*/
  double evaluateNumber();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   DivisionNode
  \brief   Definition of atributes and methods of DivisionNode class
  \note    DivisionNode Class publicly inherits from NumericOperatorNode class 
		   and adds its own printAST and evaluate functions
*/
class DivisionNode : public NumericOperatorNode 
{
  public:
/*!		
	\brief Constructor of DivisionNode uses NumericOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new DivisionNode is created with the parameter
*/
  DivisionNode(ExpNode *L, ExpNode *R, int lineNumber): NumericOperatorNode(L,R,lineNumber) 
  {
		// Empty
  }
/*!
	\brief   printAST the DivisionNode
	\return  void
	\sa		   evaluateNumber
*/
  void printAST();

/*!	
	\brief   Evaluate the DivisionNode
	\return  double
	\sa		   printAST
*/
  double evaluateNumber();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   IntegerDivisionNode
  \brief   Definition of atributes and methods of IntegerDivisionNode class
  \note    IntegerDivisionNode Class publicly inherits from NumericOperatorNode class 
		   and adds its own printAST and evaluate functions
*/
class IntegerDivisionNode : public NumericOperatorNode 
{
  public:
/*!		
	\brief Constructor of IntegerDivisionNode uses NumericOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new IntegerDivisionNode is created with the parameter
*/
  IntegerDivisionNode(ExpNode *L, ExpNode *R, int lineNumber): NumericOperatorNode(L,R,lineNumber) 
  {
		// Empty
  }
/*!
	\brief   printAST the IntegerDivisionNode
	\return  void
	\sa		   evaluateNumber
*/
  void printAST();

/*!	
	\brief   Evaluate the IntegerDivisionNode
	\return  double
	\sa		   printAST
*/
  double evaluateNumber();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   ConcatenationNode
  \brief   Definition of atributes and methods of ConcatenationNode class
  \note    ConcatenationNode Class publicly inherits from ConcatenationNode class 
		   and adds its own printAST and evaluate functions
*/
class ConcatenationNode : public StringOperatorNode 
{
  public:
/*!		
	\brief Constructor of ConcatenationNode uses ConcatenationNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new IntegerDivisionNode is created with the parameter
*/
  ConcatenationNode(ExpNode *L, ExpNode *R, int lineNumber): StringOperatorNode(L,R,lineNumber) 
  {
		// Empty
  }
/*!
	\brief   printAST the ConcatenationNode
	\return  void
	\sa		   evaluateNumber
*/
  void printAST();

/*!	
	\brief   Evaluate the ConcatenationNode
	\return  double
	\sa		   printAST
*/
  std::string evaluateString();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   ModuloNode
  \brief   Definition of atributes and methods of ModuloNode class
  \note    ModuloNode Class publicly inherits from NumericOperatorNode class 
		   and adds its own printAST and evaluate functions
*/
class ModuloNode : public NumericOperatorNode 
{
  public:
/*!		
	\brief Constructor of ModuloNode uses NumericOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new ModuloNode is created with the parameter
*/
  ModuloNode(ExpNode *L, ExpNode *R, int lineNumber): NumericOperatorNode(L,R,lineNumber) 
  {
		// Empty
  }
/*!
	\brief   printAST the ModuloNode
	\return  void
	\sa		   evaluateNumber
*/
  void printAST();

/*!	
	\brief   Evaluate the ModuloNode
	\return  double
	\sa		   printAST
*/
  double evaluateNumber();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   PowerNode
  \brief   Definition of atributes and methods of PowerNode class
  \note    PowerNode Class publicly inherits from NumericOperatorNode class 
		   and adds its own printAST and evaluate functions
*/
class PowerNode : public NumericOperatorNode 
{
  public:
/*!		
	\brief Constructor of PowerNode uses NumericOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new PowerNode is created with the parameter
*/
  PowerNode(ExpNode *L, ExpNode *R, int lineNumber): NumericOperatorNode(L,R,lineNumber) 
  {
		// Empty
  }

/*!
	\brief   Print the AST for PowerNode
	\return  void
	\sa		   evaluateNumber
*/
  void printAST();

/*!	
	\brief   Evaluate the PowerNode
	\return  double
	\sa		   printAST
*/
  double evaluateNumber();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   BuiltinFunctionNode
  \brief   Definition of atributes and methods of BuiltinFunctionNode class
  \note    BuiltinFunctionNode Class publicly inherits from ExpNode class 
*/
class BuiltinFunctionNode : public ExpNode 
{
  protected: 
	std::string _id; //!< Name of the BuiltinFunctionNode
	
  public:
/*!		
	\brief Constructor of BuiltinFunctionNode
	\param id: string, name of the BuiltinFunction
	\post  A new BuiltinFunctionNode is created with the parameter
*/
  BuiltinFunctionNode(std::string id, int lineNumber)
	{
		this->_id = id;
		this->_lineNumber = lineNumber;
	}

};




///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   BuiltinFunctionNode_0
  \brief   Definition of atributes and methods of BuiltinFunctionNode_0 class
  \note    BuiltinFunctionNode_0 Class publicly inherits from BuiltinFunctionNode class 
		   and adds its own printAST and evaluate functions
*/
class BuiltinFunctionNode_0 : public BuiltinFunctionNode 
{
  public:
/*!		
	\brief Constructor of BuiltinFunctionNode_0 uses BuiltinFunctionNode's constructor as member initializer
	\param id: string, name of the BuiltinFunction
	\post  A new BuiltinFunctionNode_2 is created with the parameter
*/
  BuiltinFunctionNode_0(std::string id, int lineNumber): BuiltinFunctionNode(id, lineNumber)
	{
		// 
	}

	/*!	
		\brief   Get the type of the child expression:
		\return  int
		\sa		   printAST, evaluateNumber
	*/
	int getType();



	/*!
		\brief   Print the AST for BuiltinFunctionNode_0
		\return  void
		\sa		   getType, evaluateNumber
	*/
	  void printAST();

	/*!	
		\brief   Evaluate the BuiltinFunctionNode_0
		\return  double
		\sa		   getType, printAST
	*/
	  double evaluateNumber();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   BuiltinFunctionNode_1
  \brief   Definition of atributes and methods of BuiltinFunctionNode_1 class
  \note    BuiltinFunctionNode_1 Class publicly inherits from BuiltinFunctionNode class 
		   and adds its own printAST and evaluate functions
*/
class BuiltinFunctionNode_1: public BuiltinFunctionNode 
{
  private:
	ExpNode *_exp;  //!< Argument of the BuiltinFunctionNode_1

  public:
/*!		
	\brief Constructor of BuiltinFunctionNode_1 uses BuiltinFunctionNode's constructor as member initializer
	\param id: string, name of the BuiltinFunction
	\param expression: pointer to ExpNode, argument of the BuiltinFunctionNode_1
	\post  A new BuiltinFunctionNode_1 is created with the parameters
*/
  BuiltinFunctionNode_1(std::string id, ExpNode *expression, int lineNumber): BuiltinFunctionNode(id, lineNumber)
	{
		this->_exp = expression;
	}

	/*!	
		\brief   Get the type of the child expression:
		\return  int
		\sa		   printAST, evaluateNumber
	*/
	int getType();

	/*!
		\brief   Print the AST for BuiltinFunctionNode_1
		\return  void
		\sa		   getType, evaluateNumber
	*/
	  void printAST();

	/*!	
		\brief   Evaluate the BuiltinFunctionNode_1
		\return  double
		\sa		   getType, printAST
	*/
	  double evaluateNumber();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   BuiltinFunctionNode_2
  \brief   Definition of atributes and methods of BuiltinFunctionNode_2 class 
  \note    BuiltinFunctionNode_2 Class publicly inherits from BuiltinFunctionNode class 
		   and adds its own printAST and evaluate functions
*/
class BuiltinFunctionNode_2 : public BuiltinFunctionNode 
{
	private:
		ExpNode *_exp1; //!< First argument of the BuiltinFunction_2
		ExpNode *_exp2; //!< Second argument of the BuiltinFunction_2

	public:
	/*!		
		\brief Constructor of BuiltinFunctionNode_2 uses BuiltinFunctionNode's constructor as member initializer
		\param id: string, name of the BuiltinFunction_2
		\param expression1: pointer to ExpNode, first argument of the BuiltinFunctionNode
		\param expression2: pointer to ExpNode, second argument of the BuiltinFunctionNode
		\post  A new BuiltinFunctionNode_2 is created with the parameters
	*/
	  BuiltinFunctionNode_2(std::string id,ExpNode *expression1,ExpNode *expression2, int lineNumber): BuiltinFunctionNode(id, lineNumber)
	{
		this->_exp1 = expression1;
		this->_exp2 = expression2;
	}

	/*!	
	\brief   Get the type of the children expressions
	\return  int
	\sa		   printAST. evaluateNumber
	*/
	int getType();



	/*!
		\brief   Print the AST for BuiltinFunctionNode_2
		\return  void
		\sa		   getType, evaluateNumber
	*/
	  void printAST();

	/*!	
		\brief   Evaluate the BuiltinFunctionNode_2
		\return  double
		\sa		   getType, printAST
	*/
	  double evaluateNumber();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   GreaterThanNode
  \brief   Definition of atributes and methods of GreaterThanNode class
  \note    GreaterThanNode Class publicly inherits from RelationalOperatorNode class 
		   and adds its own printAST and evaluate functions
*/
class GreaterThanNode : public RelationalOperatorNode 
{
  public:

/*!		
	\brief Constructor of GreaterThanNode uses RelationalOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new GreaterThanNode is created with the parameter
*/
  GreaterThanNode(ExpNode *L, ExpNode *R, int lineNumber): RelationalOperatorNode(L,R,lineNumber) 
  {
		// Empty
  }


/*!
	\brief   Print the AST for GreaterThanNode
	\return  void
	\sa		   evaluateBool
*/
  void printAST();

/*!	
	\brief   Evaluate the GreaterThanNode
	\return  bool
	\sa		   printAST
*/
  bool evaluateBool();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   GreaterOrEqualNode
  \brief   Definition of atributes and methods of GreaterOrEqualNode class
  \note    GreaterOrEqualNode Class publicly inherits from RelationalOperatorNode class 
		       and adds its own printAST and evaluate functions
*/
class GreaterOrEqualNode : public RelationalOperatorNode 
{
  public:

/*!		
	\brief Constructor of GreaterOrEqualNode uses RelationalOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new GreaterOrEqualNode is created with the parameter
*/
  GreaterOrEqualNode(ExpNode *L, ExpNode *R, int lineNumber): RelationalOperatorNode(L,R,lineNumber) 
  {
		// Empty
  }
/*!
	\brief   Print the AST for GreaterOrEqualNode
	\return  void
	\sa		   evaluateBool
*/
  void printAST();

/*!	
	\brief   Evaluate the GreaterOrEqualNode
	\return  bool
	\sa		   printAST
*/
  bool evaluateBool();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   LessThanNode
  \brief   Definition of atributes and methods of LessThanNode class
  \note    LessThanNode Class publicly inherits from RelationalOperatorNode class 
		   and adds its own printAST and evaluate functions
*/
class LessThanNode : public RelationalOperatorNode 
{
  public:

/*!		
	\brief Constructor of LessThanNode uses RelationalOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new LessThanNode is created with the parameter
*/
  LessThanNode(ExpNode *L, ExpNode *R, int lineNumber): RelationalOperatorNode(L,R,lineNumber) 
  {
		// Empty
  }
/*!
	\brief   Print the AST for LessThanNode
	\return  void
	\sa		   evaluateBool
*/
  void printAST();

/*!	
	\brief   Evaluate the LessThanNode
	\return  bool
	\sa		   printAST
*/
  bool evaluateBool();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   LessOrEqualNode
  \brief   Definition of atributes and methods of LessOrEqualNode class
  \note    LessThanNode Class publicly inherits from RelationalOperatorNode class 
		       and adds its own printAST and evaluate functions
*/
class LessOrEqualNode : public RelationalOperatorNode 
{
  public:

/*!		
	\brief Constructor of LessOrEqualNode uses RelationalOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new LessOrEqualNode is created with the parameter
*/
  LessOrEqualNode(ExpNode *L, ExpNode *R, int lineNumber): RelationalOperatorNode(L,R,lineNumber) 
  {
		// Empty
  }

/*!
	\brief   Print the AST for LessOrEqualNode
	\return  void
	\sa		   evaluateBool
*/
  void printAST();

/*!	
	\brief   Evaluate the LessOrEqualNode
	\return  bool
	\sa		   printAST
*/
  bool evaluateBool();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   EqualNode
  \brief   Definition of atributes and methods of EqualNode class
  \note    EqualNode Class publicly inherits from RelationalOperatorNode class 
		   and adds its own printAST and evaluate functions
*/
class EqualNode : public RelationalOperatorNode 
{
  public:

/*!		
	\brief Constructor of EqualNode uses RelationalOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new EqualNode is created with the parameter
*/
  EqualNode(ExpNode *L, ExpNode *R, int lineNumber): RelationalOperatorNode(L,R,lineNumber) 
  {
		// Empty
  }

/*!
	\brief   Print the AST for EqualNode
	\return  void
	\sa		   evaluateBool
*/
  void printAST();

/*!	
	\brief   Evaluate the EqualNode
	\return  bool
	\sa		  printAST
*/
  bool evaluateBool();;
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   NotEqualNode
  \brief   Definition of atributes and methods of NotEqualNode class
  \note    NotEqualNode Class publicly inherits from RelationalOperatorNode class 
		   and adds its own printAST and evaluate functions
*/
class NotEqualNode : public RelationalOperatorNode 
{
  public:

/*!		
	\brief Constructor of NotEqualNode uses RelationalOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new NotEqualNode is created with the parameter
*/
  NotEqualNode(ExpNode *L, ExpNode *R, int lineNumber): RelationalOperatorNode(L,R,lineNumber) 
  {
		// Empty
  }

/*!
	\brief   Print the AST for NotEqualNode
	\return  void
	\sa		   evaluateBool
*/
  void printAST();

/*!	
	\brief   Evaluate the NotEqualNode
	\return  bool
	\sa		   printAST
*/
  bool evaluateBool();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   AndNode
  \brief   Definition of atributes and methods of AndNode class
  \note    AndNode Class publicly inherits from LogicalOperatorNode class 
		       and adds its own printAST and evaluate functions
*/
class AndNode : public LogicalOperatorNode 
{
  public:

/*!		
	\brief Constructor of AndNode uses LogicalOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new AndNode is created with the parameter
*/
  AndNode(ExpNode *L, ExpNode *R, int lineNumber): LogicalOperatorNode(L,R,lineNumber) 
  {
		// Empty
  }

/*!
	\brief   Print the AST for AndNode
	\return  void
	\sa		   evaluateBool
*/
  void printAST();

/*!	
	\brief   Evaluate the AndNode
	\return  bool
	\sa		   printAST
*/
  bool evaluateBool();
};




///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   OrNode
  \brief   Definition of atributes and methods of OrNode class
  \note    OrNode Class publicly inherits from LogicalOperatorNode class 
		       and adds its own printAST and evaluate functions
*/
class OrNode : public LogicalOperatorNode 
{
  public:

/*!		
	\brief Constructor of AndNode uses LogicalOperatorNode's constructor as members initializer
	\param L: pointer to ExpNode
	\param R: pointer to ExpNode
	\post  A new AndNode is created with the parameter
*/
  OrNode(ExpNode *L, ExpNode *R, int lineNumber): LogicalOperatorNode(L,R,lineNumber) 
  {
		// Empty
  }

/*!
	\brief   Print the AST for OrNode
	\return  void
	\sa		   evaluateBool
	*/
  void printAST();

/*!	
	\brief   Evaluate the OrNode
	\return  bool
	\sa		 printAST()
	*/
  bool evaluateBool();
};



//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/*!	
  \class   NotNode
  \brief   Definition of atributes and methods of UnaryPlusNode class
  \note    NotNode Class publicly inherits from LogicalUnaryOperatorNode class
*/
class NotNode : public LogicalUnaryOperatorNode 
{

 public:

/*!		
	\brief Constructor of NotNode uses LogicalUnaryOperatorNode's constructor as member initializer
	\param expression: pointer to ExpNode
	\post  A new NotNode is created with the parameter
*/
  NotNode(ExpNode *expression, int lineNumber): LogicalUnaryOperatorNode(expression, lineNumber) 
	{
		// empty
	} 

/*!
	\brief   Print the AST for NotNode
	\return  void
	\sa		   evaluateBool
*/
  void printAST();

/*!	
	\brief   Evaluate the NotNode
	\return  bool
	\sa		   printAST
*/
  bool evaluateBool();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   Statement
  \brief   Definition of atributes and methods of Statement class
  \warning Abstract class
*/

class Statement {
 public:
    int _lineNumber; //!< Line number for error

/*!	
	\brief   Print the AST for Statement
	\note    Virtual function: can be redefined in the heir classes
	\return  double
	\sa		   evaluate
*/

  virtual void printAST() {}

/*!	
	\brief   Evaluate the Statement
	\warning Pure virtual function: must be redefined in the heir classes
	\return  double
	\sa		   printAST
*/
  virtual void evaluate() = 0;
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   AssignmentStmt
  \brief   Definition of atributes and methods of AssignmentStmt class
  \note    AssignmentStmt Class publicly inherits from Statement class 
		   and adds its own printAST and evaluate functions
*/
class AssignmentStmt : public Statement 
{
 private:
  std::string _id; //!< Name of the variable of the assignment statement
  ExpNode *_exp; 	 //!< Expresssion the assignment statement

  AssignmentStmt *_asgn;  //!< Allow multiple assigment -> a = b = 2 

 public:

/*!		
	\brief Constructor of AssignmentStmt 
	\param id: string, variable of the AssignmentStmt
	\param expression: pointer to ExpNode
	\post  A new AssignmentStmt is created with the parameters
*/
  AssignmentStmt(std::string id, ExpNode *expression, int lineNumber): _id(id), _exp(expression)
	{
		this->_asgn = NULL; 
		this->_lineNumber = lineNumber;
	}

/*!		
	\brief Constructor of AssignmentStmt 
	\param id: string, variable of the AssignmentStmt
	\param asgn: pointer to AssignmentStmt
	\post  A new AssignmentStmt is created with the parameters
	\note  Allow multiple assigment -> a = b = 2 
*/

  AssignmentStmt(std::string id, AssignmentStmt *asgn, int lineNumber): _id(id), _asgn(asgn)
	{
		this->_exp = NULL;
		this->_lineNumber = lineNumber;
	}


/*!
	\brief   Print the AST for AssignmentStmt
	\return  void
	\sa		   evaluate
*/
  void printAST();

/*!	
	\brief   Evaluate the AssignmentStmt
	\return  void
	\sa		   printAST
*/
    void evaluate();

};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   PlusAssignmentStmt
  \brief   Definition of atributes and methods of PlusAssignmentStmt class
  \note    PlusAssignmentStmt Class publicly inherits from Statement class 
		   and adds its own printAST and evaluate functions
*/
class PlusAssignmentStmt : public Statement 
{
 private:
  std::string _id; 	//!< Name of the variable of the assignment statement
  ExpNode *_exp; 	//!< Expresssion the assignment statement

 public:

/*!		
	\brief Constructor of Plus3 
	\param id: string, variable of the PlusAssignmentStmt
	\param expression: pointer to ExpNode
	\post  A new PlusAssignmentStmt is created with the parameters
	\note  This class is used for the statement "a += b"
*/
  PlusAssignmentStmt(std::string id, ExpNode *expression, int lineNumber): _id(id), _exp(expression)
	{
		this->_lineNumber = lineNumber;
	}


/*!
	\brief   Print the AST for P
	\return  void
	\sa		   evaluate
*/
  void printAST();

/*!	
	\brief   Evaluate the AssignmentStmt
	\return  void
	\sa		   printAST
*/
    void evaluate();

};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   MinusAssignmentStmt
  \brief   Definition of atributes and methods of MinusAssignmentStmt class
  \note    MinusAssignmentStmt Class publicly inherits from Statement class 
		   and adds its own printAST and evaluate functions
*/
class MinusAssignmentStmt : public Statement 
{
 private:
  std::string _id; 	//!< Name of the variable of the assignment statement
  ExpNode *_exp; 	//!< Expresssion the assignment statement

 public:

/*!		
	\brief Constructor of MinusAssignmentStmt 
	\param id: string, variable of the MinusAssignmentStmt
	\param expression: pointer to ExpNode
	\post  A new MinusAssignmentStmt is created with the parameters
	\note  This class is used for the statement "a += b"
*/
  MinusAssignmentStmt(std::string id, ExpNode *expression, int lineNumber): _id(id), _exp(expression)
	{
		this->_lineNumber = lineNumber;
	}


/*!
	\brief   Print the AST for MinusAssignmentStmt
	\return  void
	\sa		   evaluate
*/
  void printAST();

/*!	
	\brief   Evaluate the MinusAssignmentStmt
	\return  void
	\sa		   printAST
*/
    void evaluate();

};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   PrintStmt
  \brief   Definition of atributes and methods of PrintStmt class
  \note    PrintStmt Class publicly inherits from Statement class 
		   and adds its own print and evaluate functions
  \warning  In this class, printAST and evaluate functions have the same meaning.
*/
class PrintStmt: public Statement 
{
 private:
  ExpNode *_exp; //!< Expresssion the print statement

 public:
/*!		
	\brief Constructor of PrintStmt 
	\param expression: pointer to ExpNode
	\post  A new PrintStmt is created with the parameter
*/
  PrintStmt(ExpNode *expression, int lineNumber)
	{
		this->_exp = expression;
		this->_lineNumber = lineNumber;
	}

/*!
	\brief   Print the AST for PrintStmt
	\return  void
	\sa		   evaluate
*/
  void printAST();

/*!	
	\brief   Evaluate the PrintStmt
	\return  double
	\sa		   printAST
*/
  void evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   ReadStmt
  \brief   Definition of atributes and methods of ReadStmt class
  \note    ReadStmt Class publicly inherits from Statement class 
		   and adds its own printAST and evaluate functions
*/
class ReadStmt : public Statement 
{
  private:
	std::string _id; //!< Name of the ReadStmt
	

  public:
/*!		
	\brief Constructor of ReadStmt
	\param id: string, name of the variable of the ReadStmt
	\post  A new ReadStmt is created with the parameter
*/
  ReadStmt(std::string id, int lineNumber)
	{
		this->_id = id;
		this->_lineNumber = lineNumber;
	}

/*!
	\brief   Print the AST for ReadStmt
	\return  void
	\sa		   evaluate
*/
  void printAST();

/*!	
	\brief   Evaluate the ReadStmt
	\return  void
	\sa		   printAST
*/
  void evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   ReadStringStmt
  \brief   Definition of atributes and methods of ReadStringStmt class
  \note    ReadStringStmt Class publicly inherits from Statement class 
		   and adds its own printAST and evaluate functions
*/
class ReadStringStmt : public Statement 
{
  private:
	std::string _id; //!< Name of the ReadStringStmt
	

  public:
/*!		
	\brief Constructor of ReadStringStmt
	\param id: string, name of the variable of the ReadStringStmt
	\post  A new ReadStringStmt is created with the parameter
*/
  ReadStringStmt(std::string id, int lineNumber)
	{
		this->_id = id;
		this->_lineNumber = lineNumber;
	}

/*!
	\brief   Print the AST for ReadStringStmt
	\return  void
	\sa		   evaluate
*/
  void printAST();

/*!	
	\brief   Evaluate the ReadStringStmt
	\return  void
	\sa		   printAST
*/
  void evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   EmptyStmt
  \brief   Definition of atributes and methods of EmptyStmt class
  \note    EmptyStmt Class publicly inherits from Statement class 
		   and adds its own printAST and evaluate functions
*/
class EmptyStmt : public Statement 
{
  // No attributes

  public:
/*!		
	\brief Constructor of  EmptyStmt
	\post  A new EmptyStmt is created 
*/
  EmptyStmt(int lineNumber)
	{
		// Empty
		this->_lineNumber = lineNumber;
	}


/*!
	\brief   Print the AST for EmptyStmt
	\return  void
	\sa		   evaluate
*/
  void printAST();

/*!	
	\brief   Evaluate the EmptyStmt
	\return  void
	\sa		   printAST
*/
  void evaluate();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   IfStmt
  \brief   Definition of atributes and methods of IfStmt class
  \note    IfStmt Class publicly inherits from Statement class 
		       and adds its own printAST and evaluate functions
*/
class IfStmt : public Statement 
{
 private:
  ExpNode *_cond;    //!< Condicion of the if statement
  std::list<Statement *> *_stmt1; //!< Statement of the consequent
  std::list<Statement *> *_stmt2; //!< Statement of the alternative

  public:
/*!		
	\brief Constructor of Single IfStmt (without alternative)
	\param condition: ExpNode of the condition
	\param statement1: Statement of the consequent
	\post  A new IfStmt is created with the parameters
*/
  IfStmt(ExpNode *condition, std::list<Statement *> *statement1, int lineNumber)
	{
		this->_cond = condition;
		this->_stmt1 = statement1;
        this->_stmt2 = NULL;
        this->_lineNumber = lineNumber;
	}


/*!		
	\brief Constructor of Compound IfStmt (with alternative)
	\param condition: ExpNode of the condition
	\param statement1: Statement of the consequent
	\param statement2: Statement of the alternative
	\post  A new IfStmt is created with the parameters
*/
  IfStmt(ExpNode *condition, std::list<Statement *> *statement1, std::list<Statement *> *statement2, int lineNumber)
	{
		this->_cond = condition;
		this->_stmt1 = statement1;
		this->_stmt2 = statement2;
		this->_lineNumber = lineNumber;
	}


/*!
	\brief   Print the AST for IfStmt
	\return  void
	\sa		   evaluate
*/
  void printAST();

/*!	
	\brief   Evaluate the IfStmt
	\return  void
	\sa	   	 printAST
*/
  void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   WhileStmt
  \brief   Definition of atributes and methods of WhileStmt class
  \note    WhileStmt Class publicly inherits from Statement class 
		       and adds its own printAST and evaluate functions
*/
class WhileStmt : public Statement 
{
 private:
  ExpNode *_cond; //!< Condicion of the while statement
  std::list<Statement *> *_stmt; //!< Statements of the body of the while loop

  public:
/*!		
	\brief Constructor of  WhileStmt
	\param condition: ExpNode of the condition
	\param statement: Statement of the body of the loop 
	\post  A new WhileStmt is created with the parameters
*/
  WhileStmt(ExpNode *condition, std::list<Statement *> *statement, int lineNumber)
	{
		this->_cond = condition;
		this->_stmt = statement;
		this->_lineNumber = lineNumber;
	}


/*!
	\brief   Print the AST for WhileStmt
	\return  void
	\sa		   evaluate
*/
  void printAST();

/*!	
	\brief   Evaluate the WhileStmt
	\return  void
	\sa	   	 printAST
*/
  void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   DoWhileStmt
  \brief   Definition of atributes and methods of DoWhileStmt class
  \note    DoWhileStmt Class publicly inherits from Statement class 
		       and adds its own printAST and evaluate functions
*/
class DoWhileStmt : public Statement 
{
 private:
  ExpNode *_cond; //!< Condicion of the do while statement
  std::list<Statement *> *_stmt; //!< Statements of the body of the do while loop

  public:
/*!		
	\brief Constructor of  DoWhileStmt
	\param condition: ExpNode of the condition
	\param statement: Statement of the body of the loop 
	\post  A new DoWhileStmt is created with the parameters
*/
  DoWhileStmt(ExpNode *condition, std::list<Statement *> *statement, int lineNumber)
	{
		this->_cond = condition;
		this->_stmt = statement;
		this->_lineNumber = lineNumber;
	}


/*!
	\brief   Print the AST for DoWhileStmt
	\return  void
	\sa		   evaluate
*/
  void printAST();

/*!	
	\brief   Evaluate the DoWhileStmt
	\return  void
	\sa	   	 printAST
*/
  void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   RepeatStmt
  \brief   Definition of atributes and methods of RepeatStmt class
  \note    RepeatStmt Class publicly inherits from Statement class 
		       and adds its own printAST and evaluate functions
*/
class RepeatStmt : public Statement 
{
 private:
  ExpNode *_cond; //!< Condicion of the Repeat statement
  std::list<Statement *> *_stmt; //!< Statements of the body of the Repeat loop

  public:
/*!		
	\brief Constructor of  RepeatStmt
	\param condition: ExpNode of the condition
	\param statement: Statement of the body of the loop 
	\post  A new RepeatStmt is created with the parameters
*/
  RepeatStmt(std::list<Statement *> *statement, ExpNode *condition, int lineNumber)
	{
		this->_cond = condition;
		this->_stmt = statement;
		this->_lineNumber = lineNumber;
	}


/*!
	\brief   Print the AST for RepeatStmt
	\return  void
	\sa		   evaluate
*/
  void printAST();

/*!	
	\brief   Evaluate the RepeatStmt
	\return  void
	\sa	   	 printAST
*/
  void evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   ForStmt
  \brief   Definition of atributes and methods of ForStmt class
  \note    ForStmt Class publicly inherits from Statement class 
		       and adds its own printAST and evaluate functions
*/
class ForStmt : public Statement 
{
 private:
  std::string _id;                        //!< Identifier (loop variable) of the For statement
  ExpNode *_from;                         //!< Initial value expression
  ExpNode *_to;                           //!< Final value expression
  ExpNode *_step;                         //!< Step expression
  std::list<Statement *> *_stmt;          //!< Statements in the body of the For loop

  public:
/*!		
    \brief Constructor of the ForStmt class without step
    \param id: Identifier of the loop variable
    \param from: Expression representing the initial value
    \param to: Expression representing the final value
    \param stmt: List of statements inside the loop body
    \post  A new ForStmt is created with the provided parameters
*/
  ForStmt(const std::string &id, ExpNode *from, ExpNode *to, std::list<Statement *> *stmt, int lineNumber)
  {
    this->_id = id;
    this->_from = from;
    this->_to = to;
    this->_stmt = stmt;
    this->_step = NULL;
    this->_lineNumber = lineNumber;
  }

  
/*!		
    \brief Constructor of the ForStmt class with step
    \param id: Identifier of the loop variable
    \param from: Expression representing the initial value
    \param to: Expression representing the final value
    \param step: Expression representing the increment step
    \param stmt: List of statements inside the loop body
    \post  A new ForStmt is created with the provided parameters
*/
  ForStmt(const std::string &id, ExpNode *from, ExpNode *to, ExpNode *step, std::list<Statement *> *stmt, int lineNumber)
  {
    this->_id = id;
    this->_from = from;
    this->_to = to;
    this->_stmt = stmt;
    this->_step = step;
  }


/*!
	\brief   Print the AST for RepeatStmt
	\return  void
	\sa		   evaluate
*/
  void printAST();

/*!	
	\brief   Evaluate the RepeatStmt
	\return  void
	\sa	   	 printAST
*/
  void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   CaseStmt
  \brief   Definition of atributes and methods of CaseStmt class
  \note    CaseStmt Class publicly inherits from Statement class 
		       and adds its own printAST and evaluate functions
*/
class CaseStmt : public Statement 
{
 private:
  ExpNode *_exp;
  std::list<Statement *> *_stmt;

  public:
/*!		

*/
  CaseStmt(ExpNode * exp, std::list<lp::Statement *> *stmt, int lineNumber)
  {
    this->_exp = exp;
    this->_stmt = stmt;
    this->_lineNumber = lineNumber;
  }


/*!
	\brief   Print the AST for RepeatStmt
	\return  void
	\sa		   evaluate
*/
  void printAST();

/*!	
	\brief   Evaluate the RepeatStmt
	\return  void
	\sa	   	 printAST
*/
  void evaluate();

  ExpNode* getExp() {
    return _exp;
  }

  std::list<Statement *>* getStatements() {
    return _stmt;
  }
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   SwitchStmt
  \brief   Definition of atributes and methods of SwitchStmt class
  \note    SwitchStmt Class publicly inherits from Statement class 
		       and adds its own printAST and evaluate functions
*/
class SwitchStmt : public Statement 
{
 private:
  ExpNode *_exp;                 //!< Expression to evaluate for switching
  std::list<lp::CaseStmt *> *_caselist; //!< List of case statements
  std::list<lp::Statement *> *_defaultlist; //!< List of statements for the default case

 public:
  /**
   * @brief Constructor for SwitchStmt without default case.
   * @param exp Expression to evaluate for switching.
   * @param caselist List of case statements.
   * @param lineNumber Line number for error reporting.
   */
  SwitchStmt(ExpNode * exp, std::list<lp::CaseStmt *> *caselist, int lineNumber)
  {
    this->_exp = exp;
    this->_caselist = caselist;
    this->_lineNumber = lineNumber;
  }

  /**
   * @brief Constructor for SwitchStmt with default case.
   * @param exp Expression to evaluate for switching.
   * @param caselist List of case statements.
   * @param defaultlist List of statements for the default case.
   * @param lineNumber Line number for error reporting.
   */
  SwitchStmt(ExpNode * exp, std::list<lp::CaseStmt *> *caselist, std::list<lp::Statement *> *defaultlist, int lineNumber)
  {
    this->_exp = exp;
    this->_caselist = caselist;
    this->_lineNumber = lineNumber;
    this->_defaultlist = defaultlist;
  }

  /**
   * @brief Prints the AST for the SwitchStmt node.
   * @return void
   * @sa evaluate
   */
  void printAST();

  /**
   * @brief Evaluates the SwitchStmt, executing the matching case or default block.
   * @return void
   * @sa printAST
   */
  void evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   UnaryIncrementStmt
  \brief   Definition of atributes and methods of UnaryIncrementStmt class
  \note    UnaryIncrementStmt Class publicly inherits from Statement class 
		   and adds its own printAST and evaluate functions
*/
class UnaryIncrementStmt : public Statement 
{
 private:
	  ExpNode *_exp;   //!< Expression to increment
	  int _lineNumber; //!< Line number for error reporting

 public:
  /**
   * @brief Constructor for UnaryIncrementStmt.
   * @param exp Expression to increment.
   * @param lineNumber Line number for error reporting.
   * @post A new UnaryIncrementStmt is created with the provided expression and line number.
   */
  UnaryIncrementStmt(ExpNode * exp, int lineNumber)
  {
	this->_exp = exp;
	this->_lineNumber = lineNumber;
  }

  /**
   * @brief Prints the AST for the UnaryIncrementStmt node.
   * @return void
   * @sa evaluate
   */
  void printAST();

  /**
   * @brief Evaluates the UnaryIncrementStmt, incrementing the value of the expression.
   * @return void
   * @sa printAST
   */
  void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @class UnaryDecrementStmt
 * @brief Represents a statement that decrements the value of an expression.
 * @note Inherits from Statement. Adds its own printAST and evaluate methods.
 */
class UnaryDecrementStmt : public Statement 
{
 private:
	  ExpNode *_exp;   //!< Expression to decrement
	  int _lineNumber; //!< Line number for error reporting

 public:
  /**
   * @brief Constructor for UnaryDecrementStmt.
   * @param exp Expression to decrement.
   * @param lineNumber Line number for error reporting.
   * @post A new UnaryDecrementStmt is created with the provided expression and line number.
   */
  UnaryDecrementStmt(ExpNode * exp, int lineNumber)
  {
    this->_exp = exp;
    this->_lineNumber = lineNumber;
  }

  /**
   * @brief Prints the AST for the UnaryDecrementStmt node.
   * @return void
   * @sa evaluate
   */
  void printAST();

  /**
   * @brief Evaluates the UnaryDecrementStmt, decrementing the value of the expression.
   * @return void
   * @sa printAST
   */
  void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @class UnaryFactorialStmt
 * @brief Represents a statement that applies the factorial operation to an expression.
 * @note Inherits from Statement. Adds its own printAST and evaluate methods.
 */
class UnaryFactorialStmt : public Statement 
{
 private:
	  ExpNode *_exp;   //!< Expression to apply factorial
	  int _lineNumber; //!< Line number for error reporting

 public:
  /**
   * @brief Constructor for UnaryFactorialStmt.
   * @param exp Expression to apply factorial.
   * @param lineNumber Line number for error reporting.
   * @post A new UnaryFactorialStmt is created with the provided expression and line number.
   */
  UnaryFactorialStmt(ExpNode * exp, int lineNumber)
  {
    this->_exp = exp;
    this->_lineNumber = lineNumber;
  }

  /**
   * @brief Prints the AST for the UnaryFactorialStmt node.
   * @return void
   * @sa evaluate
   */
  void printAST();

  /**
   * @brief Evaluates the UnaryFactorialStmt, applying the factorial operation to the expression.
   * @return void
   * @sa printAST
   */
  void evaluate();
};



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   RandomNode
  \brief   Definition of atributes and methods of RandomNode class
  \note    RandomNode Class publicly inherits from Statement class 
		       and adds its own printAST and evaluate functions
*/
class RandomNode : public ExpNode 
{
 private:
  ExpNode *_min;                         
  ExpNode *_max;                         

  public:


    RandomNode(ExpNode * min, ExpNode * max, int lineNumber)
	{
		this->_min = min;
		this->_max = max;
		this->_lineNumber = lineNumber;
    }

    int getType();

    double evaluateNumber();

    void printAST();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   BlockStmt
  \brief   Definition of atributes and methods of BlockStmt class
  \note    BlockStmt Class publicly inherits from Statement class 
		       and adds its own printAST and evaluate functions
*/
class BlockStmt : public Statement 
{
private:
    std::list<Statement *> *_stmts;  //!< List of statements in the block
public:
    /**
     * @brief Constructor for BlockStmt.
     * @param stmtList List of statements to include in the block.
     * @param lineNumber Line number for error reporting.
     * @post A new BlockStmt is created with the provided statements.
     */
    BlockStmt(std::list<Statement *> *stmtList, int lineNumber): _stmts(stmtList)
    {
        // Empty
    }
    /**
     * @brief Prints the AST for the BlockStmt node.
     * @return void
     * @sa evaluate
     */
    void printAST();
    /**
     * @brief Evaluates the BlockStmt, executing all statements in the block.
     * @return void
     * @sa printAST
     */
    void evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!	
  \class   ClearScreenStmt
  \brief   Definition of attributes and methods of ClearScreenStmt class
  \note    ClearScreenStmt class inherits from Statement and overrides printAST and evaluate
*/
class ClearScreenStmt : public Statement
{
 public:

/*!		
  \brief Constructor of ClearScreenStmt
  \post  A new ClearScreenStmt object is created
*/
  inline ClearScreenStmt() {}

  
/*!	
  \brief   Print the AST node for ClearScreenStmt
  \return  void
  \sa      evaluate
*/
  void printAST();

  
/*!	
  \brief   Evaluate the ClearScreenStmt and clears the terminal screen
  \return  void
  \sa      printAST
*/
  void evaluate();
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


/*!    
  \class   PlaceStmt
  \brief   Definition of attributes and methods of PlaceStmt class
  \note    PlaceStmt class inherits from Statement and overrides printAST and evaluate
*/
class PlaceStmt : public Statement
{
 public:
    ExpNode * _x;
    ExpNode * _y;
    int _lineNumber;

/*!        
  \brief Constructor of PlaceStmt
  \post  A new ClearScreenStmt object is created
*/
inline PlaceStmt(ExpNode * x, ExpNode * y, int lineNumber)
{
    this->_x = x;
    this->_y = y;
    this->_lineNumber = lineNumber;
}
  
/*!    
  \brief   Print the AST node for PlaceStmt
  \return  void
  \sa      evaluate
*/
  void printAST();

  
/*!    
  \brief   Evaluate the PlaceStmt and place the terminal screen
  \return  void
  \sa      printAST
*/
  void evaluate();
};


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

/*!	
  \class   AST
  \brief   Definition of atributes and methods of AST class
*/
class AST {
private:
    std::list<Statement *> *stmts;  //!< List of statements in the AST
public:
    /**
     * @brief Constructor for AST.
     * @param stmtList Pointer to a list of Statement pointers.
     * @post A new AST is created with the provided list of statements.
     */
    AST(std::list<Statement *> *stmtList): stmts(stmtList)
    {
        // Empty
    }
    /**
     * @brief Prints the AST by traversing and printing all statements.
     * @return void
     * @sa evaluate
     */
    void printAST();
    /**
     * @brief Evaluates the AST by executing all statements in order.
     * @return void
     * @sa printAST
     */
    void evaluate();
};

// End of name space lp
}

// End of _AST_HPP_
#endif