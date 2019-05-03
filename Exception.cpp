/*///////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	File: Exception.cpp
	Purpose: Implementation file for Exception class
	Contact: jacob.vanderkarr@oit.edu
*///////////////////////////////////////////////////

#include "Exception.h"
#include <cstring>

using std::strlen;
using std::strcpy;

//Default ctor for exception
Exception::Exception(): m_msg(nullptr)
{
}

//one arg ctor for exception class
//takes a char * argument for the message
Exception::Exception(const char * msg) : m_msg(nullptr)
{
	if (msg != nullptr)
	{
		m_msg = new char[strlen(msg) + 1];
		strcpy(m_msg, msg);
	}
}

//copy constructor
Exception::Exception(const Exception & copy) : m_msg(nullptr)
{
	if (copy.m_msg != nullptr)
	{
		m_msg = new char[strlen(copy.m_msg) + 1];
		strcpy(m_msg, copy.m_msg);
	}
}

//dtor
Exception::~Exception()
{
	delete[] m_msg;
	m_msg = nullptr;
}

//class = operator overload, copy
Exception & Exception::operator=(const Exception & rhs)
{
	//check for self assignment
	if (this != &rhs)
	{
		//copy over the private data to this
		delete[] m_msg;
		m_msg = nullptr;
		if (rhs.m_msg != nullptr)
		{
			m_msg = new char[strlen(rhs.m_msg) + 1];
			strcpy(m_msg, rhs.m_msg);
		}
	}
	return *this;
}

//getMessage is a method that returns the private
//m_msg data as a constant
const char * Exception::GetMessage() const
{
	return m_msg;
}

//setMessage sets the m_msg
void Exception::SetMessage(const char * msg)
{
	if (msg != nullptr)
	{
		delete[] m_msg;
		m_msg = new char[strlen(msg) + 1];
		strcpy(m_msg, msg);
	}
	else
	{
		m_msg = nullptr;
	}
}

//stream operator overload to send the m_msg into the stream
ostream & operator<<(ostream & stream, const Exception & except)
{
	stream << except.m_msg;
	return stream;
}
