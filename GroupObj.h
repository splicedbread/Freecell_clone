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
#include "LStack.h"

class GroupObj
{
public:
	GroupObj();
	GroupObj(char * name);
	GroupObj(const GroupObj & cpy);

private:
};
#endif // !GROUPOBJ_H