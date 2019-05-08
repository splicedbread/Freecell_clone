/*/////////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	Date: 5/4/19
	File: Freecell.cpp
	Purpose: Implementation of the Freecell game class
*//////////////////////////////////////////////////////
#include "Freecell.h"

#define CHEATING_CHEAT_VAL 1998

//default ctor
Freecell::Freecell() : m_Running(false), m_cheat_mode(false), m_scale(1.0f), m_Xres(MIN_X_RES), m_Yres(MIN_Y_RES), m_f_count(0)
{
	//setup the homecells and freecells
	m_freecells.SetLength(4);
	m_homecells.SetLength(4);

	//set the size for each stack in the array to 13
	for (int i = 0; i < m_homecells.GetLength(); i++)
	{
		m_homecells[i].SetSize(13);
	}
}

//cheating ctor
Freecell::Freecell(int specialnum) : m_Running(false), m_cheat_mode(false), m_scale(1.0f), m_Xres(MIN_X_RES), m_Yres(MIN_Y_RES), m_f_count(0)
{
	if (specialnum == CHEATING_CHEAT_VAL)
	{
		m_cheat_mode = true;
	}

	//setup the homecells and freecells
	m_freecells.SetLength(4);
	m_homecells.SetLength(4);

	//set the size for each stack in the array to 13
	for (int i = 0; i < m_homecells.GetLength(); i++)
	{
		m_homecells[i].SetSize(13);
	}
}

//copy ctor
/*
	WARNING, COPY CTOR WORKS, BUT IN WHY
	WOULD YOU WANT A COPY OF THE GAME TO RUN
	AT THE SAME TIME?
*/
Freecell::Freecell(const Freecell & cpy) : m_Running(false), m_cheat_mode(cpy.m_cheat_mode), m_scale(cpy.m_scale), m_f_count(cpy.m_f_count)
{
	m_window = cpy.m_window;
	m_deck = cpy.m_deck;
	m_freecells = cpy.m_freecells;
	m_homecells = cpy.m_homecells;
	m_columns = cpy.m_columns;
	m_holder = cpy.m_holder;
}

//dtor
Freecell::~Freecell()
{
	m_Running = false;
	m_cheat_mode = false;
	m_scale = 1.0f;
	m_f_count = 0;
}

/*/////////////////////////////////////////////////////////////
	StartGame
		private method because we want the user to choose 
		a size for the playing screen first. (done in console)
		once selected the console dissappears and leaves the 
		main window open for play

		the loop should be pertainant
		> Update Window
		> User Input
		> Validation of User Input
		> Card movement under the hood
		> Update Card Positions
*//////////////////////////////////////////////////////////////
void Freecell::StartGame()
{
	//setup phase
	m_Running = true;

	//if cheat mode is enabled, dont randomise the
	//deck, because LoadDeck() does something special
	if (m_cheat_mode)
	{
		m_deck.Reset();
	}
	else
	{
		m_deck.Randomise();
	}

	//Load the Deck into the board
	LoadDeck();

	//after loading the deck update the screen
	WindowUpdate();

	while (m_Running && m_window.GetWindow().isOpen())
	{
		//also need to handle window events in here.

		//main loop
		//update the window first (this loop will happen really fast each time)
		WindowUpdate();

		//user input (get mouse coords / mouse clicks)
		m_input_result = UserInput();

		//user validation on a move
		if (m_input_result == 0)
		{
			m_check_result = MovementCheck();
		}

		//if there was a movement that was valid, then move
		//those items.
		if (m_check_result == 1)
		{
			MoveTo(m_numCards, m_new_col);
		}
	}
}

/*///////////////////////////////////////////////////////////
	ChooseSize
		needs to occur before the window is reallly created
		can be SMALL, MEDIUM, or LARGE
		SMALL = 848 x 477
		MEDIUM = 1600 x 900
		LARGE = 1920 x 1080
*////////////////////////////////////////////////////////////
void Freecell::ChooseSize(Freecell::WindowSize size)
{
	switch (size)
	{
	case Freecell::SMALL:
		m_Xres = MIN_X_RES;
		m_Yres = MIN_Y_RES;
		break;
	case Freecell::MEDIUM:
		m_Xres = 1600;
		m_Yres = 900;
		break;
	case Freecell::LARGE:
		m_Xres = 1920;
		m_Yres = 1080;
		break;
	default:
		m_Xres = MIN_X_RES;
		m_Yres = MIN_Y_RES;
		break;
	}

	//get the scale that we will be using to display our cards
	m_scale = (static_cast<float>(m_Xres) / static_cast<float>(MIN_X_RES));
	m_window.SetDimension(m_Xres, m_Yres);
	m_window.Update();
	StartGame();
}

/*
	WindowUpdate
		Updates the windows with the correct
		graphics currently in the buffer
*/
void Freecell::WindowUpdate()
{
	//Draw the freecells and homecells first (doesnt matter the order here)
	DrawFree();
	DrawHome();

	//Draw al the columns
	DrawColumns();

	//ghost cards are the last thing drawn to the buffer
	//because they 'sit' on top of everything else
	if (m_m1_pressed)
	{
		DrawGhost();
	}
	
	//after everything is drawn, update the screen
	m_window.Update();
}

/*
	UserInput
		gathers data about where the users
		mouse is, has on Click listeners
		etc

		returns 1 for a click a 0 for a release
		-1 if something else
*/
int Freecell::UserInput()
{

	return 0;
}

/*
	MovementCheck
		checks to make sure a given movement
		is valid (based on how many cards can be
		moved at a specific time)

		returns 1 if valid 0 if not
		-1 if unspecified or nothing moved
*/
int Freecell::MovementCheck()
{


	return 0;
}

/*//////////////////////////////////////////////////
	Check Win Cond
		checks if both the freecells and the board
		are empty. When that is the case 
		the game has been won. 

		Maybe do something special.
*///////////////////////////////////////////////////
bool Freecell::CheckWinCond()
{
	bool cond = true;

	//check if any cards are left in freecells
	if (m_f_count != 0)
	{
		cond = false;
	}
	
	//check if any cards are left on the board.
	for (int i = 0; i < m_columns.GetLength(); i++)
	{
		if (!m_columns[i].IsEmpty())
		{
			cond = false;
		}
	}

	return cond;
}

/*
	MoveTo
		after a valid movement check,
		move the amount of cards
		requested to the new location

		0-7 is the board columns
		8 is freecells (checks if there is open space first)
		9 is homecells (checks if just one card is being moved)
*/
void Freecell::MoveTo(int numOfCards, int column)
{

}

/*////////////////////////////////////////////////
	LoadDeck
		Loads the current deck into
		the game board, starting with left column
		and then then inserts left to right
*//////////////////////////////////////////////////
void Freecell::LoadDeck()
{
	int dealNum = 52;
	int drawn = 0;

	//if cheating, we only deal half the deck
	if (m_cheat_mode)
	{
		dealNum = 26;
	}

	//while loop that pushes cards into the board
	//with each top of columns first
	while (drawn < dealNum)
	{
		for (int i = 0; drawn < dealNum && i < m_columns.GetLength(); i++, drawn++)
		{
			m_columns[i].Push(m_deck.Draw());
		}
	}
}