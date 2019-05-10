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

	enum ElmRegion
	{
		NONE, FREE, HOME, COLUMN
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

	//Display helper functions
	void DrawGhost();
	void DrawFree();
	void DrawHome();
	void DrawColumns();

private:

	//pausing game functions
	void Pause();


	//hidden grabbing / dropping function
	void GrabCard();
	void DropCard();
	bool CheckOrder();
	void MoveFreeCellsDown();

	ElmRegion GetRegion();


	//constants used for displaying
	const int m_offset = 70;
	const int m_padding = 1;

	const int col_x = 20;
	const int col_y = 95;
	const int card_space = 30;


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

	//keep track of user selection with how
	//many cards are being moved and which column is 
	//cards moving to
	int m_numCards;
	int m_new_col;
	int m_card_in_col;
	int m_old_col;

	//window
	WDManager m_window;

	//objs
	GroupObj m_blanks;
	GroupObj m_homebl;


	//flags
	bool m_Running;
	bool m_cheat_mode;
	bool m_m1_pressed;
	bool m_card_grabbed;

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

	//help with displaying the 'ghost' cards being moved
	LinkedList<Card> m_ghost;
	int m_ghost_count;

	//board counters
	int m_f_count; //freecell array count
	int m_prev_freecell;
	int m_col_counts[8];
	int m_home_counts[4];
	int m_empty_cols;
};
#endif // !FREECELL_H