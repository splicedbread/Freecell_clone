/*/////////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	Date: 5/4/19
	File: Freecell.cpp
	Purpose: Implementation of the Freecell game class
*//////////////////////////////////////////////////////
#include "Freecell.h"

#define CHEATING_CHEAT_VAL 1998

//default ctor
Freecell::Freecell() : m_Running(false), m_cheat_mode(false), m_scale(1.0f), m_Xres(MIN_X_RES), m_Yres(MIN_Y_RES)
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
Freecell::Freecell(int specialnum) : m_Running(false), m_cheat_mode(false), m_scale(1.0f), m_Xres(MIN_X_RES), m_Yres(MIN_Y_RES)
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
Freecell::Freecell(const Freecell & cpy) : m_Running(false), m_cheat_mode(cpy.m_cheat_mode), m_scale(cpy.m_scale)
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
		//main loop
		//update the window first (this loop will happen really fast each time)
		WindowUpdate();

		//user input (get mouse coords / mouse clicks)
		m_input_result = UserInput();

		//user validation on a move
		m_check_result = MovementCheck();


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