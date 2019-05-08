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

		throws an exception if an obj
		with the same name is found
*///////////////////////////////////////////
void GroupObj::Insert(const DrawableObj & itm)
{
	bool similar = false;

	Node<DrawableObj> * travel;
	travel = m_group.GetHead();

	if (travel != nullptr && strcmp(travel->GetData().m_name, itm.m_name) == 0)
	{
		//if the head contains the data, we already found it
		similar = true;
	}

	while (!similar && travel != nullptr)
	{
		//if the name is the same
		if (strcmp(travel->GetData().m_name, itm.m_name) == 0)
		{
			similar = true;
		}
		else
		{
			travel = travel->GetNext();
		}
	}

	if (similar)
	{
		//if there is already an item with the existing name
		//throw an exception
		throw Exception("Exception: object already in group");
	}
	m_group.Append(itm); //insert the constant referrence into the group
	m_group.Last().SetGroup(m_name); //change the group to the group name
}

/*///////////////////////////////////////
	Remove
		removes an object from the group
		(object must have a name)

		throws an exception if the group
		is empty
		throws if the item is not found

		The idea is that each DrawableObj
		has a unique name and can be found
*////////////////////////////////////////
void GroupObj::Remove(const char * name)
{
	if (m_group.IsEmpty())
	{
		throw Exception("Exception: empty group, cannot remove");
	}

	Node<DrawableObj> * travel;
	travel = m_group.GetHead();
	bool found = false;

	if (strcmp(travel->GetData().m_name, name) == 0)
	{
		//if the head contains the data, we already found it
		found = true;
	}

	//try finding the same name in the group
	while (!found && travel != nullptr)
	{
		//if the name is the same
		if (strcmp(travel->GetData().m_name, name) == 0)
		{
			found = true;
		}
		else
		{
			travel = travel->GetNext();
		}
	}

	//after finding it, now remove it
	//otherwise if not found throw an exception
	if (!found)
	{
		throw Exception("Exception: obj not in group");
	}
	
	//if found, extract the DrawableObj
	m_group.Extract(travel->GetData());	
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

/*////////////////////////////////////////////
	SetName
		Sets the name of the
		group, also renames Drawable objects
		group names
*/////////////////////////////////////////////
void GroupObj::SetName(const char * name)
{
	if (name != nullptr)
	{
		//we want to set the group name
		//to the specified argument
		delete m_name;
		m_name = new char[strlen(name) + 1];
		strcpy(m_name, name);

		//after the name is set, we 
		//would like to update existing
		//Drawable objects with that group name

		Node<DrawableObj> * travel;
		travel = m_group.GetHead();

		while (travel != nullptr)
		{
			//set the group name in drawable obj
			travel->GetData().SetGroup(name);
			//travel along the groups linked list
			travel = travel->GetNext();
		}
	}
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

/*///////////////////////////////////////
	ResetGroup
		resets the group so its ready for
		new input
*////////////////////////////////////////
void GroupObj::ResetGroup()
{
	m_group.Purge();
}


/*///////////////////////////////////////////
	GetDrawable
		returns a reference to a 
		drawable object within the group
		throws exception if not found
*////////////////////////////////////////////
DrawableObj & GroupObj::GetDrawable(const char * name) const
{
	if (m_group.IsEmpty())
	{
		throw Exception("Exception: empty group, cannot retrieve");
	}

	Node<DrawableObj> * travel;
	travel = m_group.GetHead();
	bool found = false;

	if (strcmp(travel->GetData().m_name, name) == 0)
	{
		//if the head contains the data, we already found it
		found = true;
	}

	//try finding the same name in the group
	while (!found && travel != nullptr)
	{
		//if the name is the same
		if (strcmp(travel->GetData().m_name, name) == 0)
		{
			found = true;
		}
		else
		{
			travel = travel->GetNext();
		}
	}

	//after finding it, now remove it
	//otherwise if not found throw an exception
	if (!found)
	{
		throw Exception("Exception: obj not in group");
	}

	return travel->GetData();
}