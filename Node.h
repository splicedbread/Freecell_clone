#ifndef NODE_H
#define NODE_H
/*////////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	File: Node.h
	Purpose: Definition & Implementation of Node class
	Contact: jacob.vanderkarr@oit.edu
*/////////////////////////////////////////////////////

//forward declaration of LinkedList
template <typename T>
class LinkedList;

/*////////////////////////////////////////////////////////////////
	Node holds data and some pointers to the next & previous node
*/////////////////////////////////////////////////////////////////
template <typename T>
class Node
{
	friend class LinkedList<T>;
public:
	Node();
	Node(const T data);
	~Node();
	bool operator==(const Node<T> & rhs);
	Node<T> * GetNext() const;
	Node<T> * GetPrevious() const;
	T & GetData() const;
private:
	Node<T> * m_next;
	Node<T> * m_prev;
	T m_data;
};

//default ctor
template <typename T>
Node<T>::Node() : m_next(nullptr), m_prev(nullptr), m_data()
{
}

//one arg ctor
template <typename T>
Node<T>::Node(const T data) : m_next(nullptr), m_prev(nullptr), m_data(data)
{
}

//dtor
template <typename T>
Node<T>::~Node()
{
	m_next = nullptr;
	m_prev = nullptr;
}

//equality operator overload
//returns true if the data is the same.
template <typename T>
bool Node<T>::operator==(const Node<T> & rhs)
{
	return (this->m_data == rhs->m_data);
}

//GetNext returns the next pointer
template <typename T>
Node<T> * Node<T>::GetNext() const
{
	return m_next;
}

//GetPrevious returns the previous pointer
template <typename T>
Node<T> * Node<T>::GetPrevious() const
{
	return m_prev;
}

//GetData return the data from node
template <typename T>
T Node<T>::GetData() const
{
	return m_data;
}
#endif // !NODE_H