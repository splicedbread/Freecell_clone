#ifndef FREECELL_H
#define FREECELL_H
/*/////////////////////////////////////////////
	Author: Jacob Vanderkarr
	Date: 5/4/19
	File: Freecell.h
	Purpose: definition of the freecell class

	Manager Functions:
		default ctor, dtor, copy ctor

*//////////////////////////////////////////////
#include "WDManager.h"
class Freecell
{
public:
	Freecell();
	Freecell(int specialnum); //used for cheats
	Freecell(const Freecell & cpy);
	~Freecell();

	Freecell & operator=(const Freecell & rhs);


private:
	WDManager m_window;
};
#endif // !FREECELL_H