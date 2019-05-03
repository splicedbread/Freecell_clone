#ifndef ARRAY_H
#define ARRAY_H
/*//////////////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	File: Array.h
	Purpose: Definition and Implementation for an ADT Array
	Contact: jacob.vanderkarr@oit.edu
*///////////////////////////////////////////////////////////
#include "Exception.h"
/*//////////////////////////////////////////////////////
	Class: Array

	Purpose:
		templated class that serves as a container
		for any data type

	Manager Functions:
		ctor, 2 arg ctor (acts like a 1 sometimes), 
		copy ctor, move ctor, dtor

	Methods:
		assignment op, move assignment op
		op[] overloads
		Get/Set startindex: so any starting index
			can be specified
		Get/Set length: 
			Dynamically change the length of the array
*//////////////////////////////////////////////////////
template<typename T> class Array
{
public:
	Array();
	Array(int length, int start_index = 0);
	Array(const Array<T> & copy);
	Array(Array<T> && mv);
	~Array();
	Array & operator= (const Array<T> & rhs);
	Array & operator= (Array<T> && rhs);
	T & operator[] (int index);
	const T & operator[] (int index) const;
	int GetStartIndex() const;
	void SetStartIndex(int start_index);
	int GetLength() const;
	void SetLength(int start_index);

	typedef T value_type;
private:
	T * m_array;
	int m_length;
	int m_start_index;
};

//default ctor, sets things to 0 and nullptr respectfully
template<typename T>
Array<T>::Array() : m_array(nullptr), m_length(0), m_start_index(0)
{
}

//overloaded ctor, takes a length and starting index
template<typename T>
Array<T>::Array(int length, int start_index) : m_array(nullptr), m_start_index(start_index)
{
	if (length <= 0)
	{
		throw Exception("Except: invalid length assigned");
	}
	m_length = length;
	m_array = new T[length];
}

//copy ctor
template<typename T>
Array<T>::Array(const Array & copy) : m_array(nullptr), m_length(copy.m_length), m_start_index(copy.m_start_index)
{
	if (m_length > 0)
	{
		m_array = new T[m_length];

		for (int i = 0; i < m_length; i++)
		{
			m_array[i] = copy.m_array[i];
		}
	}
}

//move ctor
template <typename T>
Array<T>::Array(Array && mv) : m_array(mv.m_array), m_length(mv.m_length), m_start_index(mv.m_start_index)
{
	mv.m_array = nullptr;
	mv.m_length = 0;
	mv.m_start_index = 0;
}

//dtor
template<typename T>
Array<T>::~Array()
{
	delete[] m_array;
	m_array = nullptr;
	m_length = 0;
	m_start_index = 0;
}

//op = overload. similar to copy ctor but frees memory from m_array first
//copy version
template<typename T>
Array<T> & Array<T>::operator=(const Array & rhs)
{
	//check for self assignment
	if (this != &rhs)
	{
		delete[] m_array;
		m_array = nullptr;

		m_length = rhs.m_length;
		m_start_index = rhs.m_start_index;
		if (m_length > 0)
		{
			m_array = new T[m_length];

			for (int i = 0; i < rhs.m_length; i++)
			{
				m_array[i] = rhs.m_array[i];
			}
		}
	}
	else
	{
		throw Exception("Except: self assignment not allowed");
	}
	return *this;
}

//move version
template <typename T>
Array<T> & Array<T>::operator=(Array<T> && mv)
{
	if (this != &mv)
	{
		delete[] m_array;

		m_length = mv.m_length;
		m_start_index = mv.m_start_index;
		m_array = mv.m_array;

		mv.m_length = 0;
		mv.m_start_index = 0;
		mv.m_array = nullptr;
	}
	return *this;
}

//op [] overload. Allows for access to the m_array through an Array obj
//Must include bounds checking
template<typename T>
T & Array<T>::operator[](int index)
{
	if (index < m_start_index || index >= m_start_index + m_length)
	{
		throw Exception("Except: out of bounds access");
	}
	return m_array[index - m_start_index];
}

//const method version
template<typename T>
const T & Array<T>::operator[](int index) const
{
	if (index < m_start_index || index >= m_start_index + m_length)
	{
		throw Exception("Except: out of bounds access");
	}
	return m_array[index - m_start_index];
}
//getters

// getStartIndex() returns the start index
template<typename T>
int Array<T>::GetStartIndex() const
{
	return m_start_index;
}

// getLength() returns the length (count of elements)
template<typename T>
int Array<T>::GetLength() const
{
	return m_length;
}

//setters

// setStartIndex just sets the start index value to one specified
// even if its negative. 
// because of how this works, changing the starting index 
template<typename T>
void Array<T>::SetStartIndex(int start_index)
{
	m_start_index = start_index;
}

// setLength needs to be able to adjust the current length of the array
// This means that it can become shorter, but some data may be lost

template<typename T>
void Array<T>::SetLength(int length)
{
	//check to see if the length is actually changed
	if (length != m_length)
	{
		if (length > 0)
		{
			if (m_array != nullptr)
			{
				//variable that is for copying the old contents of m_array
				int c_len = length < m_length ? length : m_length;

				//create a copy of the current array
				T * cpy;
				cpy = new T[length]; //allocate memory for the new length

				for (int i = 0; i < c_len; i++)
				{
					cpy[i] = m_array[i];
				}

				delete[] m_array;
				m_array = cpy;

				cpy = nullptr;
				m_length = length;
			}
			else
			{
				//if the array is a nullptr, then we should initialize some things
				m_length = length;
				m_array = new T[m_length];
			}
		}
		else
		{
			delete[] m_array;
			m_array = nullptr;
			m_length = 0;
		}
	}
}

#endif // !ARRAY_H
