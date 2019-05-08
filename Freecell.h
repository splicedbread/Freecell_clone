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
	enum WindowSize
	{
		SMALL, MEDIUM, LARGE
	};


	Freecell();
	Freecell(int specialnum); //used for cheats
	Freecell(const Freecell & cpy);
	~Freecell();

	void ChooseSize(WindowSize size);
	void WindowUpdate();
	int UserInput();
	int MovementCheck();
	//int UndoMove(); //might not get implemented
	bool CheckWinCond(); //all cards are in homecell ie all columns are empty

	void MoveTo(int numOfCards, int column);

private:
	//game loop initiator
	void StartGame(); //private so you are forced to choose a window size first

	//hidden helper functions
	void LoadDeck();

	//saved resolutions
	int m_Xres;
	int m_Yres;

	//Mouse coords for interactions
	int m_Mouse_x;
	int m_Mouse_y;

	//window
	WDManager m_window;

	//flags
	bool m_Running;
	bool m_cheat_mode;
	bool m_m1_pressed;
	bool m_m1_released;

	int m_input_result;
	int m_check_result;

	//deck
	Deck m_deck;

	//scale, what size should items be displayed as?
	float m_scale;

	//board containers
	Array<Card> m_freecells;
	Array<Stack<Card>> m_homecells;
	Array<LStack<Card>> m_columns;
	LStack<Card> m_holder;
};
#endif // !FREECELL_H