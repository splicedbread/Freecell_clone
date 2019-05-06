/*//////////////////////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	Date: 5/4/19
	File: DrawableObj.cpp
	Purpose: Implementation of the Drawable class for Freecell game
*///////////////////////////////////////////////////////////////////
#include <iostream>
#include "DrawableObj.h"

//default ctor
DrawableObj::DrawableObj() : m_name(nullptr), m_src_path(nullptr), m_group(nullptr), m_width(0), m_height(0), m_Ypos_rel(0), m_Xpos_rel(0)
{

}

//1 arg ctor
DrawableObj::DrawableObj(const char * name) : m_name(nullptr), m_src_path(nullptr), m_group(nullptr), m_width(0), m_height(0), m_Ypos_rel(0), m_Xpos_rel(0)
{
	if (name != nullptr)
	{
		m_name = new char[strlen(name) + 1];
		strcpy(m_name, name);
	}
}

//special multi arg ctor
DrawableObj::DrawableObj(const char * name, int width, int height) : m_name(nullptr), m_src_path(nullptr), m_group(nullptr), m_width(width), m_height(height), m_Ypos_rel(0), m_Xpos_rel(0)
{
	if (name != nullptr)
	{
		m_name = new char[strlen(name) + 1];
		strcpy(m_name, name);
	}
}

//dtor
DrawableObj::~DrawableObj()
{
	m_width = 0;
	m_height = 0;
	m_Xpos_rel = 0;
	m_Ypos_rel = 0;

	delete m_name;
	delete m_group;
	delete m_src_path;

	m_name = nullptr;
	m_group = nullptr;
	m_src_path = nullptr;
}

//assignment operator overload
DrawableObj & DrawableObj::operator=(const DrawableObj & rhs)
{
	if (this != &rhs)
	{
		//deallocate all existing char * and assign to nullptr
		delete m_name;
		delete m_group;
		delete m_src_path;

		m_name = nullptr;
		m_group = nullptr;
		m_src_path = nullptr;

		//for each of the char *, check if they are nullptr first
		//name
		if (rhs.m_name != nullptr)
		{
			m_name = new char[strlen(rhs.m_name) + 1];
			strcpy(m_name, rhs.m_name);
		}

		//group
		if (rhs.m_group != nullptr)
		{
			m_group = new char[strlen(rhs.m_group) + 1];
			strcpy(m_group, rhs.m_group);
		}

		//src
		if (rhs.m_src_path != nullptr)
		{
			m_src_path = new char[strlen(rhs.m_src_path) + 1];
			strcpy(m_src_path, rhs.m_src_path);
		}

		//make sure to copy the rest of the members
		m_width = rhs.m_width;
		m_height = rhs.m_height;
		m_Xpos_rel = rhs.m_Xpos_rel;
		m_Ypos_rel = rhs.m_Ypos_rel;
	}
	return *this;
}

/*////////////////////////////////////////////////
	SetName
		takes in a name as the new obj name 
*////////////////////////////////////////////////
void DrawableObj::SetName(const char * name)
{
	if (name != nullptr)
	{
		delete m_name;
		m_name = new char[strlen(name) + 1];
		strcpy(m_name, name);
	}
}

/*////////////////////////////////
	SetSrc
		takes in a src char * and
		that becomes the new src
		src is used for referencing
		images from file
*/////////////////////////////////
void DrawableObj::SetSrc(const char * src)
{
	if (src != nullptr)
	{
		delete m_src_path;
		m_src_path = new char[strlen(src) + 1];
		strcpy(m_src_path, src);
	}
}

/*/////////////////////////////////////
	SetGroup
		sets the group that the object
		belongs to
*//////////////////////////////////////
void DrawableObj::SetGroup(const char * group)
{
	if (group != nullptr)
	{
		delete m_group;
		m_group = new char[strlen(group) + 1];
		strcpy(m_group, group);
	}
}

/*////////////////////////////////
	SetDims
		sets the dimensions
		of the object. not the
		position of the object
*//////////////////////////////////
void DrawableObj::SetDims(int x, int y)
{
	//allowing negative values is okay,
	//because that would indicate a transformation
	//on the object (inversion)
	m_width = x;
	m_height = y;
}

/*///////////////////////////////////////////
	SetPos
		sets the position (relative)
		to other objects in its group

		this must be maintained by
		the group obj and how
		Drawables are made. There is no
		way to confirm relative positioning
		without other objects. 
*/////////////////////////////////////////////
void DrawableObj::SetPos(int x, int y)
{
	//origin is 0,0 in the top left corner
	m_Ypos_rel = y;
	m_Xpos_rel = x;
}

/*///////////////////////////
	Getter Methods:
		Name
		Src
		Group
		Width
		Height
		XPos
		YPos
*////////////////////////////
const char * DrawableObj::GetName() const
{
	return m_name;
}

const char * DrawableObj::GetSrc() const
{
	return m_src_path;
}

const char * DrawableObj::GetGroup() const
{
	return m_group;
}

int DrawableObj::GetWidth() const
{
	return m_width;
}

int DrawableObj::GetHeight() const
{
	return m_height;
}

int DrawableObj::GetXpos() const
{
	return m_Xpos_rel;
}

int DrawableObj::GetYpos() const
{
	return m_Ypos_rel;
}