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
#include "deck.h"
#include "Stack.h"
#include "LStack.h"
class Freecell
{
public:
	Freecell();
	Freecell(int specialnum); //used for cheats
	Freecell(const Freecell & cpy);
	~Freecell();

	Freecell & operator=(const Freecell & rhs);
	void WindowUpdate();
	int UserInput();
	int MovementCheck();
	int UndoMove(); //might not get implemented
	bool CheckWinCond();

private:
	//window
	WDManager m_window;

	//flags
	bool m_Running;
	bool m_cheat_mode;

	//deck
	Deck m_deck;

	//board containers
	Array<Card> m_freecells;
	Array<Stack<Card>> m_homecells;
	Array<LStack<Card>> m_columns;
};
#endif // !FREECELL_H