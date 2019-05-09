#ifndef STACK_H
#define STACK_H
/*//////////////////////////////////////
	Author: Jacob Vanderkarr
	Date: 4/23/19
	File: Stack.h
	Purpose: Definition + implementation
		of the Stack data struct
	Contact: jacob.vanderkarr@oit.edu
*///////////////////////////////////////
/*
	Class methods:
		Canonical management functions

		Push - pushes parameter onto the stack
		Pop - removes and returns the data 
			from the stack
		Peek - returns the element on the top
			of the stack, but does not remove it
		Size - returns the number of items
			currently on the stack
		IsEmpty - returns tru if the stack is empty
		IsFull - returns true if the stack is full
		SetSize - sets the size of the stack
			after its creation.
*/
#include "Array.h"
template <typename T>
class Stack
{
public:
	Stack();
	Stack(int size);
	Stack(const Stack<T> & cpy);
	~Stack();

	Stack<T> & operator=(const Stack<T> & rhs);

	void Push(const T & itm);
	const T & Pop();
	T & Peek();
	int Size() const;

	bool IsEmpty() const;
	bool IsFull() const;

	void SetSize(int size);

private:
	Array<T> m_stack;
	int m_curr_items;
};

//default ctor
template <typename T>
Stack<T>::Stack() : m_curr_items(0)
{
}

//one arg ctor
template <typename T>
Stack<T>::Stack(int size) : m_curr_items(0)
{
	if (size >= 0)
	{
		m_stack.SetLength(size);
	}
	//if the size is < 0, then the default ctor of m_stack already
	//has its length set to 0
}

//cpy ctor
template <typename T>
Stack<T>::Stack(const Stack<T> & cpy) : m_curr_items(cpy.m_curr_items), m_stack(cpy.m_stack)
{
}

//dtor
template <typename T>
Stack<T>::~Stack()
{
	m_curr_items = 0;
}

//assignment overload
template <typename T>
Stack<T> & Stack<T>::operator=(const Stack<T> & rhs)
{
	if (this != &rhs)
	{
		m_curr_items = rhs.m_curr_items;
		m_stack = rhs.m_stack;
	}
	return *this;
}

/*///////////////////////////////////////
	Push

	Preconds: this object exists

	Postconds:
		the item is pushed onto the
		stack if there is room and
		m_curr_items gets incremented.
		if there is no room, an overflow
		exception is thrown.
*////////////////////////////////////////
template <typename T>
void Stack<T>::Push(const T & item)
{
	//if the current amount of itms is more than
	//the stack size, throw an exception
	if (m_curr_items >= m_stack.GetLength())
	{
		throw Exception("Exception: stack overflow");
	}
	
	if (m_stack.GetLength() <= 0)
	{
		throw Exception("Exception: cannot push onto 0 size stack");
	}
	//if (isEmpty())
		//throw
	//if an exception is not thrown, then add one to
	//the stack. (when 0 items, pushes item on elm 0)
	// (when 1 item, pushes item on elm 1
	m_stack[m_curr_items] = item;
	m_curr_items++;
}

/*///////////////////////////////////////
	Pop

	Preconds: this object exists

	Postconds:
		the top item is 'removed' from the
		stack. If there is no items in the
		stack, a underflow exception is 
		thrown.

		The top item is returned after
		being removed.
*////////////////////////////////////////
template <typename T>
const T & Stack<T>::Pop()
{
	if (m_curr_items <= 0)
	{
		throw Exception("Exception: stack underflow");
	}
	//the item is not actually removed, 
	//but the top of the stack changes. 
	m_curr_items--; //decrement the current items
	return m_stack[m_curr_items];
	//if there is 1 item, decrementing m_curr items means
	//that elm 0 (the one item) is the one that is returned.
}

/*///////////////////////////////////////
	Pop

	Preconds: this object exists

	Postconds:
		returns the value of the top
		of the stack,
		throws an exception if no items
		are on the stack
*////////////////////////////////////////
template <typename T>
T & Stack<T>::Peek()
{
	if (m_curr_items <= 0)
	{
		throw Exception("Exception: stack is empty");
	}
	//return the top item
	return m_stack[m_curr_items - 1];
}

/*///////////////////////////////////////
	Size

	Preconds: this object exists

	Postconds:
		returns the size of the stack
*////////////////////////////////////////
template <typename T>
int Stack<T>::Size() const
{
	return m_curr_items;
}

/*///////////////////////////////////////
	IsEmpty

	Preconds: this object exists

	Postconds:
		returns true if the stack is empty
*////////////////////////////////////////
template <typename T>
bool Stack<T>::IsEmpty() const
{
	return (m_curr_items <= 0);
}

/*///////////////////////////////////////
	IsFull

	Preconds: this object exists

	Postconds:
		returns true if the stack is full
		or if the size of the stack is zero
*////////////////////////////////////////
template <typename T>
bool Stack<T>::IsFull() const
{
	return (m_curr_items == m_stack.GetLength());
}

/*///////////////////////////////////////
	SetSize

	Preconds: this object exists

	Postconds:
		sets the size of the stack
		may lose data if the size
		is smaller than the current size
*////////////////////////////////////////
template <typename T>
void Stack<T>::SetSize(int size)
{
	try
	{
		m_stack.SetLength(size);
		if (size < m_curr_items)
		{
			m_curr_items = size;
		}
	}
	catch (Exception except)
	{
		//if there is an exception
		//from .setlength
		//throw it up another level
		throw except;
	}
}
#endif // !STACK_H