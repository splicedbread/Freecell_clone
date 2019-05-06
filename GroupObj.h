#ifndef GROUPOBJ_H
#define GROUPOBJ_H
/*/////////////////////////////////////////////
	Author: Jacob Vanderkarr
	Date: 5/4/19
	File: GroupObj.h
	Purpose: Definition of group object class
		A group object is a group of
		drawable objects to act as one 'obj'
		that can be used for interaction
		with the window.
*//////////////////////////////////////////////
#include "LinkedList.h"
#include "DrawableObj.h"

class GroupObj
{
	friend class WDManager;
public:
	GroupObj();
	GroupObj(const char * name);
	GroupObj(const GroupObj & cpy);
	~GroupObj();

	GroupObj & operator=(const GroupObj & rhs);

	void Insert(const DrawableObj & itm);
	void Remove(const char * name);

	void SetPos(int x, int y);
	void SetName(const char * name);

	int GetXPos() const;
	int GetYPos() const;
	const char * GetName() const;

	DrawableObj & GetDrawable(const char * name) const;

private:
	char * m_name;
	int m_Xpos;
	int m_Ypos;
	LinkedList<DrawableObj> m_group;
};
#endif // !GROUPOBJ_H