/*/////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	Date: 5/4/19
	File: GroupObj.cpp
	Purpose: Implementation of the group obj class
*//////////////////////////////////////////////////
#include "GroupObj.h"
/*
	some notes. 
	The idea of this class is to hold a 'group'
	of similar drawable objects.

	One thing to keep in mind is the order in which
	drawable objects are inserted.

	The head is going to be the first object
	that is drawn to the buffer.
	the next sits on top of that etc.

	Designing how these objects appear is up
	to the user. 

	The head has less visual priority than the tail.
	in simple terms.
*/

//default ctor
GroupObj::GroupObj() : m_name(nullptr), m_Xpos(0), m_Ypos(0)
{
	m_name = new char[strlen("default") + 1];
	strcpy(m_name, "default");
}

//1 arg ctor
GroupObj::GroupObj(const char * name) : m_name(nullptr), m_Xpos(0), m_Ypos(0)
{
	if (name != nullptr)
	{
		m_name = new char[strlen(name) + 1];
		strcpy(m_name, name);
	}
	else
	{
		m_name = new char[strlen("default") + 1];
		strcpy(m_name, "default");
	}
}

//copy ctor
GroupObj::GroupObj(const GroupObj & cpy) : m_name(nullptr), m_Xpos(cpy.m_Xpos), m_Ypos(cpy.m_Ypos)
{
	if (cpy.m_name != nullptr)
	{
		m_name = new char[strlen(cpy.m_name) + 1];
		strcpy(m_name, cpy.m_name);
	}
	m_group = cpy.m_group;
}

//dtor
GroupObj::~GroupObj()
{
	delete m_name;
	m_Xpos = 0;
	m_Ypos = 0;
}

//assignment operator overload
GroupObj & GroupObj::operator=(const GroupObj & rhs)
{
	if (this != &rhs)
	{
		if (rhs.m_name != nullptr)
		{
			delete m_name;
			m_name = new char[strlen(rhs.m_name) + 1];
			strcpy(m_name, rhs.m_name);
		}

		m_Xpos = rhs.m_Xpos;
		m_Ypos = rhs.m_Ypos;
		m_group = rhs.m_group;
	}
	return *this;
}

/*//////////////////////////////////////////
	Insert
		adds a Drawable object to the group
		and updates that objects group name
		to the current group name
		(helps for identification)
*///////////////////////////////////////////
void GroupObj::Insert(const DrawableObj & itm)
{
	m_group.Append(itm); //insert the constant referrence into the group
	m_group.Last().SetGroup(m_name); //change the group to the group name
}

/*
	Remove
		removes an object from the group
		(object must have a name)
*/
void GroupObj::Remove(const char * name)
{

}


//setters
/*////////////////////////////////////////
	SetPos sets a position for the object
	relative to the window. origin (0,0)
	starts in the top left corner
*/////////////////////////////////////////
void GroupObj::SetPos(int x, int y)
{
	m_Xpos = x;
	m_Ypos = y;
}

/*
	SetName
		Sets the name of the
		group, also renames Drawable objects
		group names
*/
void GroupObj::SetName(const char * name)
{

}

//getters

int GroupObj::GetXPos() const
{
	return m_Xpos;
}

int GroupObj::GetYPos() const
{
	return m_Ypos;
}

const char * GroupObj::GetName() const
{
	return m_name;
}

/*///////////////////////////////////////////
	GetDrawable
		returns a reference to a 
		drawable object within the group
		returns nullptr if nothing was found
*////////////////////////////////////////////
DrawableObj & GroupObj::GetDrawable(const char * name) const
{

}