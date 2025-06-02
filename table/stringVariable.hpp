/*!	
	\file    stringVariable.hpp
	\brief   Declaration of StringVariable class
	\author  
	\date    2025-06-02
	\version 1.0
*/

#ifndef _STRINGVARIABLE_HPP_
#define _STRINGVARIABLE_HPP_

#include <string>
#include <iostream>

#include "variable.hpp"

/*!	
	\namespace lp
	\brief Name space for the subject Language Processors
*/
namespace lp{

/*!	
  \class StringVariable
  \brief Definition of attributes and methods of StringVariable class
  \note  StringVariable Class publicly inherits from Variable class
*/
class StringVariable : public lp::Variable
{
/*!		
\name Private attributes of StringVariable class
*/
	private:
		std::string _value;   //!< \brief String value of the StringVariable

/*!		
\name Public methods of StringVariable class
*/
	public:

/*!	
	\name Constructors
*/
		
/*!		
	\brief Constructor with arguments with default values
	\note  Inline function that uses Variable's constructor as members initializer
	\param name: name of the StringVariable
	\param token: token of the StringVariable
	\param type: type of the StringVariable
	\param value: string value of the StringVariable
	\pre   None
	\post  A new StringVariable is created with the values of the parameters
	\sa   setName, setValue
*/
	inline StringVariable(std::string name="", int token = 0, int type = 0, std::string value=""): 
 	Variable(name,token,type)
	{
		this->setValue(value);
	}
		
/*!		
	\brief Copy constructor
	\note  Inline function
	\param s: object of StringVariable class
	\pre   None
	\post  A new StringVariable is created with the values of an existent StringVariable
	\sa    setName, setValue
*/
	StringVariable(const StringVariable & s)
	{
		// Inherited methods
		this->setName(s.getName());

		this->setToken(s.getToken());

		this->setType(s.getType());
		
		// Own method
		this->setValue(s.getValue());
	}


/*!	
	\name Observer
*/
	
/*!	
	\brief  Public method that returns the value of the StringVariable
	\note   Inline function
	\pre    None
	\post   None
    \return Value of the StringVariable
	\sa		getValue
*/
	inline std::string getValue() const
	{
		return this->_value;
	}



/*!	
	\name Modifier
*/
		
/*!	
	\brief   This function modifies the value of the StringVariable
	\note    Inline function
	\param   value: new value of the StringVariable
	\pre     None
	\post    The value of the StringVariable is equal to the parameter 
	\return  void
	\sa 	 setValue
*/
	inline void setValue(const std::string & value)
	{
	    this->_value = value;
	}



/*!	
	\name I/O Functions
*/
		
/*!		
	\brief Read a StringVariable
	\pre   None
	\post  The attributes of the StringVariable are modified with the read values
    \sa    write
*/
	void read();

	
/*!		
	\brief Write a StringVariable
	\pre   None
	\post  None
    \sa    read
*/
	void write() const;


/*!	
	\name Operators
*/
	
/*!		
	\brief  Assignment Operator
	\param  s: object of StringVariable class
	\post   The attributes of this object are equal to the attributes of the parameter
	\return Reference to this object
*/
	StringVariable &operator=(const StringVariable &s);
	

 //! \name Friend functions
/*!		
	\brief  Insertion operator
	\param  i: input stream
	\param  s: object of StringVariable class
	\pre    None
	\post   The attributes of the StringVariable are modified with the inserted values from the input stream
	\return The input stream
*/
	friend std::istream &operator>>(std::istream &i, StringVariable &s);

/*!		
	\brief  Extraction operator
	\param  o: output stream
	\param  s: object of StringVariable class
	\pre    None
	\post   The attributes of the StringVariable are written in the output stream
	\return The output stream
*/
	friend std::ostream &operator<<(std::ostream &o, StringVariable const &s);
	
// End of StringVariable class
};

// End of name space lp
}

// End of _STRINGVARIABLE_HPP_
#endif
