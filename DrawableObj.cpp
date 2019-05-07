/*//////////////////////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	Date: 5/4/19
	File: DrawableObj.cpp
	Purpose: Implementation of the Drawable class for Freecell game
*///////////////////////////////////////////////////////////////////
#include <iostream>
#include "DrawableObj.h"

//default ctor
DrawableObj::DrawableObj() : m_name(nullptr), m_src_path(nullptr), m_group(nullptr), m_scale(1.0f), m_Ypos_rel(0), m_Xpos_rel(0)
{

}

//1 arg ctor
DrawableObj::DrawableObj(const char * name) : m_name(nullptr), m_src_path(nullptr), m_group(nullptr), m_scale(1.0f), m_Ypos_rel(0), m_Xpos_rel(0)
{
	if (name != nullptr)
	{
		m_name = new char[strlen(name) + 1];
		strcpy(m_name, name);
	}
}

//special multi arg ctor
DrawableObj::DrawableObj(const char * name, float scale) : m_name(nullptr), m_src_path(nullptr), m_group(nullptr), m_scale(scale), m_Ypos_rel(0), m_Xpos_rel(0)
{
	if (name != nullptr)
	{
		m_name = new char[strlen(name) + 1];
		strcpy(m_name, name);
	}

	if (scale < 0.0)
	{
		m_scale = 1.0f;
	}
}

//cpy ctor
DrawableObj::DrawableObj(const DrawableObj & cpy) : m_name(nullptr), m_src_path(nullptr), m_group(nullptr), m_scale(cpy.m_scale), m_Ypos_rel(cpy.m_Ypos_rel), m_Xpos_rel(cpy.m_Xpos_rel)
{
	//copy the repective names over
	if (cpy.m_name != nullptr)
	{
		m_name = new char[strlen(cpy.m_name) + 1];
		strcpy(m_name, cpy.m_name);
	}

	//group
	if (cpy.m_group != nullptr)
	{
		m_group = new char[strlen(cpy.m_group) + 1];
		strcpy(m_group, cpy.m_group);
	}

	//src
	if (cpy.m_src_path != nullptr)
	{
		m_src_path = new char[strlen(cpy.m_src_path) + 1];
		strcpy(m_src_path, cpy.m_src_path);
	}
}

//dtor
DrawableObj::~DrawableObj()
{
	m_scale = 1.0f;
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
		m_scale = rhs.m_scale;
		m_Xpos_rel = rhs.m_Xpos_rel;
		m_Ypos_rel = rhs.m_Ypos_rel;
	}
	return *this;
}

//comparison operator overload
bool DrawableObj::operator==(const DrawableObj & rhs)
{
	return ((strcmp(m_name, rhs.m_name) == 0) 
			&& (strcmp(m_src_path, rhs.m_src_path) == 0)
			&& (strcmp(m_group, rhs.m_group) == 0)
			&& m_scale == rhs.m_scale
			&& m_Xpos_rel == rhs.m_Xpos_rel && m_Ypos_rel == rhs.m_Ypos_rel);
}

//not comparison operator overload
bool DrawableObj::operator!=(const DrawableObj & rhs)
{
	return !(*this == rhs);
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
void DrawableObj::SetScale(float scale)
{
	//allowing negative values is okay,
	//because that would indicate a transformation
	//on the object (inversion)
	if (scale > 0)
	{
		m_scale = scale;
	}
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

float DrawableObj::GetScale() const
{
	return m_scale;
}

int DrawableObj::GetXpos() const
{
	return m_Xpos_rel;
}

int DrawableObj::GetYpos() const
{
	return m_Ypos_rel;
}