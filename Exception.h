#ifndef EXCEPTION_H
#define EXCEPTION_H

/*////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	File: Exception.h
	Purpose: Definition file for Exceptions class
	Contact: jacob.vanderkarr@oit.edu
*/////////////////////////////////////////////////

#include <iostream>
using std::ostream;

/*//////////////////////////////////////////
	Class: Exception

	Purpose: custom exception class
		used for error checking things

	Manager Functions:
		ctor, 1 arg, copy ctor, dtor

	Methods:
		Get/Set message: does what it says
		ostream overload: prints exception
*//////////////////////////////////////////
class Exception
{
public:
	//Constructors / Destructors
	Exception();
	Exception(const char * msg);
	Exception(const Exception & copy);
	~Exception();

	Exception & operator= (const Exception & rhs);
	const char * GetMessage() const;
	void SetMessage(const char * msg);
	friend ostream & operator << (ostream & stream, const Exception & except);
private:
	char * m_msg;
};

#endif // !EXCEPTION_H