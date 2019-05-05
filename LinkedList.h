#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include "Node.h"
#include "Exception.h"
/*/////////////////////////////////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	FileName: LinkedList.h
	Template(s): LinkedList

	Purpose: LinkedList is a datastructure of nodes
*//////////////////////////////////////////////////////////////////////////////

/*//////////////////////////////////////////////////////////////////
	LinkedList is the structure that contains nodes in a list manner
*///////////////////////////////////////////////////////////////////
template <typename T>
class LinkedList
{
public:
	LinkedList();
	LinkedList(T data);
	LinkedList(const LinkedList<T> & copy);
	//LinkedList(const LinkedList<T> && mv); //not implemented yet
	LinkedList<T> & operator=(const LinkedList<T> & rhs);
	~LinkedList();

	bool IsEmpty() const;
	const T & First() const;
	const T & Last() const;

	void Prepend(T in);
	void Append(T in);
	void InsertAfter(T new_item, T existing_item);
	void InsertBefore(T new_item, T existing_item);

	bool Extract(T out);
	void Purge();

	void Display(); //Legacy, not used for Assignment 2

	//testing methods
	Node<T> * GetHead() const;
	Node<T> * GetTail() const;

	void PrintForwards() const;
	void PrintBackwards() const;
private:
	Node<T> * m_head;
	Node<T> * m_tail;
};
//default ctor
template <typename T>
LinkedList<T>::LinkedList() : m_head(nullptr), m_tail(m_head)
{}
//one arg ctor, takes in data and assigns m_next and m_prev as nullptr
template <typename T>
LinkedList<T>::LinkedList(T data) : m_head(new Node<T>(data)), m_tail(m_head)
{
	m_head->m_next(nullptr);
	m_head->m_prev(nullptr);
}

//copy ctor
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> & copy) : m_head(nullptr), m_tail(nullptr)
{
	Node<T> * travel = copy.m_head;
	while (travel != nullptr)
	{
		Append(travel->m_data);
		travel = travel->m_next;
	}
}

////move ctor
//template <typename T>
//LinkedList<T>::LinkedList(const LinkedList<T> && mv)
//{
//	//not implemented yet
//}

//default dtor, calls purge on exit to free memory
template <typename T>
LinkedList<T>::~LinkedList()
{
	Purge();
	m_head = nullptr;
	m_tail = nullptr;
}

//Assignment operator overload
template <typename T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList<T> & rhs)
{
	if (this != &rhs)
	{
		Purge();
		m_head = nullptr;
		m_tail = nullptr;

		Node<T> * travel = rhs.m_head;
		while (travel != nullptr)
		{
			Append(travel->m_data);
			travel = travel->m_next;
		}
	}
	return *this;
}

/*////////////////////////////////////////////////
	IsEmpty() checks to see if the list is empty,
	returns true if the list is empty
*/////////////////////////////////////////////////
template <typename T>
bool LinkedList<T>::IsEmpty() const
{
	return (m_head == nullptr && m_tail == nullptr);
}

/*///////////////////////////////////////////////////
	First & Last functions return the first and last
	node in the list respectfully.
*////////////////////////////////////////////////////
template <typename T>
const T & LinkedList<T>::First() const
{
	return m_head->m_data;
}

template <typename T>
const T & LinkedList<T>::Last() const
{
	return m_tail->m_data;
}

/*///////////////////////////////////////////////////////////////////////
	Append only inserts at the end of the list
*////////////////////////////////////////////////////////////////////////
template <typename T>
void LinkedList<T>::Append(T in)
{
	if (m_head == nullptr)
	{
		m_head = new Node<T>(in);
		m_tail = m_head;
	}
	else
	{
		m_tail->m_next = new Node<T>(in);
		m_tail->m_next->m_prev = m_tail;
		m_tail->m_next->m_next = nullptr;
		m_tail = m_tail->m_next;
	}
}

/*////////////////////////////////////////////////////
	Prepend only inserts at the beginning of the list
*/////////////////////////////////////////////////////
template <typename T>
void LinkedList<T>::Prepend(T in)
{
	if (m_head == nullptr)
	{
		m_head = new Node<T>(in);
		m_tail = m_head;
	}
	else
	{
		m_head->m_prev = new Node<T>(in);
		m_head->m_prev->m_next = m_head;
		m_head->m_prev->m_prev = nullptr;
		m_head = m_head->m_prev;
	}
}

/*//////////////////////////////////////////////////////////
	Insert After will navigate to the the old item and insert
	a new node after it
*///////////////////////////////////////////////////////////
template <typename T>
void LinkedList<T>::InsertAfter(T new_item, T old_item)
{
	Node<T> * travel = nullptr;
	if (m_head == nullptr)
	{
		throw Exception("Exception: cannot find old item to append new item.\n");
	}
	else
	{
		bool flag = false;
		travel = m_head;
		while (!flag && travel != nullptr)
		{
			if (travel->m_data == old_item)
			{
				flag = true;
				if (travel == m_tail)
				{
					travel->m_next = new Node<T>(new_item); //tails next is now the new node
					travel->m_next->m_prev = travel; //tails nexts previous is the tail
					travel->m_next->m_next = nullptr; //new nodes next is nullptr
					m_tail = travel->m_next; //new node is the new tail
				}
				else
				{
					travel->m_next->m_prev = new Node<T>(new_item); //make the next nodes previous a new node
					travel->m_next->m_prev->m_next = travel->m_next; //the new nodes next is travels next
					travel->m_next->m_prev->m_prev = travel; //the new nodes previous is travel
					travel->m_next = travel->m_next->m_prev; //travels next is now the new node
				}
			}
			else if (travel->m_next == nullptr)
			{
				//if the tail is not the node for old item, then the item is not found
				throw Exception("Exception: cannot find old item to append new item.\n");
			}
			travel = travel->m_next;
		}
	}
}

/*//////////////////////////////////////////////////////////
	Insert Before will navigate to the the old item and insert
	a new node before it
*///////////////////////////////////////////////////////////
template <typename T>
void LinkedList<T>::InsertBefore(T new_item, T old_item)
{
	Node<T> * travel = nullptr;
	if (m_head == nullptr)
	{
		throw Exception("Exception: cannot find old item to prepend new item.\n");
	}
	else
	{
		bool flag = false;
		travel = m_tail;
		while (!flag && travel != nullptr)
		{
			if (travel->m_data == old_item)
			{
				flag = true;
				if (travel == m_head)
				{
					travel->m_prev = new Node<T>(new_item); //heads prev is now the new node
					travel->m_prev->m_next = travel; //heads prevs next is the head
					travel->m_prev->m_prev = nullptr; //new nodes prev is nullptr
					m_head = travel->m_prev; //new node is the new head
				}
				else
				{
					travel->m_prev->m_next = new Node<T>(new_item); //make the prev nodes next a new node
					travel->m_prev->m_next->m_prev = travel->m_prev; //the new nodes prev is travels prev
					travel->m_prev->m_next->m_next = travel; //the new nodes next is travel
					travel->m_prev = travel->m_prev->m_next; //travels prev is now the new node
				}
			}
			else if (travel->m_prev == nullptr)
			{
				//if the head is not the node for the old item, then the item is not found
				throw Exception("Exception: cannot find old item to prepend new item.\n");
			}
			travel = travel->m_prev;
		}
	}
}

/*////////////////////////////////////////////////////////
	Delete searches for the node to delete, and then does
	returns true or false if it was deleted or not
*/////////////////////////////////////////////////////////
template <typename T>
bool LinkedList<T>::Extract(T out)
{
	bool found = false;

	Node<T> * travel = m_head;

	while (travel != nullptr && travel->m_data != out)
	{
		travel = travel->m_next;
	}

	if (travel != nullptr)
	{
		found = true;
		if (travel != m_head && travel != m_tail)
		{
			travel->m_next->m_prev = travel->m_prev;
			travel->m_prev->m_next = travel->m_next;
		}
		else if (travel == m_head)
		{
			m_head = m_head->m_next;
		}
		else
		{
			m_tail = m_tail->m_prev;
		}
		delete travel;
	}

	if (found == false)
	{
		throw Exception("Exception: object to be deleted does not exist");
	}
	return found;
}

/*////////////////////////////////////////////
	Purge calls delete until the list is empty
*/////////////////////////////////////////////
template <typename T>
void LinkedList<T>::Purge()
{
	Node<T> * travel = m_head;
	while (travel != nullptr)
	{
		if (travel == m_tail)
		{
			delete m_tail;
			m_tail = nullptr;
			travel = nullptr;
		}
		else
		{
			travel = travel->m_next;
			delete travel->m_prev;
		}
	}
	m_head = nullptr;
}

/*/////////////////////////////////////////////////////////////////
	Display displays each piece of data one by one in the console
*//////////////////////////////////////////////////////////////////
template <typename T>
void LinkedList<T>::Display()
{
	int m_current_pos = 0;
	Node<T> * travel = m_head;
	while (travel != nullptr)
	{
		std::cout << "pos[" << m_current_pos << "]: " << travel->m_data << std::endl;
		travel = travel->m_next;
		m_current_pos++;
	}
}

//testing methods

//GetHead and GetTail return the nodes of the respective names
template <typename T>
Node<T> * LinkedList<T>::GetHead() const
{
	return m_head;
}

template <typename T>
Node<T> * LinkedList<T>::GetTail() const
{
	return m_tail;
}

//print functions that print the whole list in either direction
template <typename T>
void LinkedList<T>::PrintForwards() const
{
	Node<T> travel = m_head;
	if (travel == nullptr)
	{
		std::cout << "Emtpy List.\n";
	}

	while (travel != nullptr)
	{
		std::cout << ": " << travel->m_data << std::endl;
		travel = travel->m_next;
	}
}

template <typename T>
void LinkedList<T>::PrintBackwards() const
{
	Node<T> travel = m_tail;
	if (travel == nullptr)
	{
		std::cout << "Emtpy List.\n";
	}

	while (travel != nullptr)
	{
		std::cout << ": " << travel->m_data << std::endl;
		travel = travel->m_prev;
	}
}

#endif // !LINKED_LIST_H;