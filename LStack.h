#ifndef LSTACK_H
#define LSTACK_H
/*//////////////////////////////////////
	Author: Jacob Vanderkarr
	Date: 4/23/19
	File: LStack.h
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
#include "LinkedList.h"
template <typename T>
class LStack
{
public:
	LStack();
	LStack(const LStack<T> & cpy);
	~LStack();

	LStack<T> & operator=(const LStack<T> & rhs);

	void Push(T itm);
	T Pop();
	const T & Peek() const;
	int Size() const;

	bool IsEmpty() const;

private:
	LinkedList<T> m_stack;
	int m_curr_items;
};

//default ctor
template <typename T>
LStack<T>::LStack() : m_curr_items(0)
{
}

//cpy ctor
template <typename T>
LStack<T>::LStack(const LStack<T> & cpy) : m_curr_items(cpy.m_curr_items)
{
	m_stack = cpy.m_stack;
}

//dtor
template <typename T>
LStack<T>::~LStack()
{
	m_curr_items = 0;
}

//assignment overload
template <typename T>
LStack<T> & LStack<T>::operator=(const LStack<T> & rhs)
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
void LStack<T>::Push(T item)
{
	//if an exception is not thrown, then add one to
	//the stack. (when 0 items, pushes item on elm 0)
	// (when 1 item, pushes item on elm 1
	m_stack.Prepend(item);
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
T LStack<T>::Pop()
{
	if (m_curr_items <= 0)
	{
		throw Exception("Exception: stack underflow");
	}
	//the item is not actually removed, 
	//but the top of the stack changes. 
	m_curr_items--; //decrement the current items
	T old = m_stack.First();
	m_stack.Extract(m_stack.First());
	return old;
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
const T & LStack<T>::Peek() const
{
	if (m_curr_items <= 0)
	{
		throw Exception("Exception: stack is empty");
	}
	//return the top item
	return m_stack.First();
}

/*///////////////////////////////////////
	Size

	Preconds: this object exists

	Postconds:
		returns the size of the LStack
*////////////////////////////////////////
template <typename T>
int LStack<T>::Size() const
{
	return m_curr_items;
}

/*///////////////////////////////////////
	IsEmpty

	Preconds: this object exists

	Postconds:
		returns true if the LStack is empty
*////////////////////////////////////////
template <typename T>
bool LStack<T>::IsEmpty() const
{
	return (m_curr_items <= 0);
}
#endif // !LStack_H