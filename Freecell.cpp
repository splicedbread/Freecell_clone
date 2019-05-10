/*/////////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	Date: 5/4/19
	File: Freecell.cpp
	Purpose: Implementation of the Freecell game class
*//////////////////////////////////////////////////////
#include "Freecell.h"
#include "FreeCellResources.h"
#include <iostream>

#define CHEATING_CHEAT_VAL 1998

//default ctor
Freecell::Freecell() : m_card_grabbed(false), m_Running(false), m_cheat_mode(false), m_scale(1.0f), m_Xres(MIN_X_RES), m_Yres(MIN_Y_RES), m_f_count(0)
{
	//setup the homecells and freecells
	m_freecells.SetLength(4);
	m_homecells.SetLength(4);
	m_columns.SetLength(8);

	//set the size for each stack in the array to 13
	for (int i = 0; i < m_homecells.GetLength(); i++)
	{
		m_homecells[i].SetSize(13);
	}

	m_window.SetTitle("Freecell 2: The search for more money");
}

//cheating ctor
Freecell::Freecell(int specialnum) : m_card_grabbed(false), m_Running(false), m_cheat_mode(false), m_scale(1.0f), m_Xres(MIN_X_RES), m_Yres(MIN_Y_RES), m_f_count(0)
{
	if (specialnum == CHEATING_CHEAT_VAL)
	{
		m_cheat_mode = true;
	}

	//setup the homecells and freecells
	m_freecells.SetLength(4);
	m_homecells.SetLength(4);
	m_columns.SetLength(8);

	//set the size for each stack in the array to 13
	for (int i = 0; i < m_homecells.GetLength(); i++)
	{
		m_homecells[i].SetSize(13);
	}

	m_window.SetTitle("Freecell 2: The search for more money");
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

/*////////////////////////////////////////////////
	Pause
		looks for the gain focus event then frees 
		back to the game
*//////////////////////////////////////////////////
void Freecell::Pause()
{
	bool paused = true;

	while (paused && m_window.GetWindow().isOpen())
	{
		Event ev;
		while (m_window.GetWindow().pollEvent(ev))
		{
			if (ev.type == Event::GainedFocus)
			{
				paused = false;
			}

			if (ev.type == Event::Closed)
			{
				m_window.GetWindow().close();
			}
		}
	}
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
	m_deck.Reset();
	if (!m_cheat_mode)
	{
		m_deck.Randomise();
	}


	//Load the Deck into the board
	LoadDeck();

	//after loading the deck update the screen
	WindowUpdate();

	while (m_Running && m_window.GetWindow().isOpen())
	{
		//check for window events that may have been triggered.
		Event ev;
		while (m_window.GetWindow().pollEvent(ev))
		{
			//while some event occurs (such as clicking 'X')
			switch (ev.type)
			{
			case Event::Closed: //window was closed
				m_window.GetWindow().close();
				m_Running = false;
				break;

			case Event::LostFocus: //window lost focus
				//while loop waiting for the window
				//to regain focus
				Pause();
				break;

			case Event::MouseMoved: //mouse moved in the wind
				//if the mouse moved and the left mouse button 
				//is pressed, update the mouse coordinates.
				if (m_m1_pressed)
				{
					m_Mouse_x = Mouse::getPosition(m_window.GetWindow()).x / m_scale;
					m_Mouse_y = Mouse::getPosition(m_window.GetWindow()).y / m_scale;
				}
				break;
			}
		}
		//also need to handle window events in here.

		//main loop

		//user input (get mouse coords / mouse clicks)
		m_input_result = UserInput();

		if (m_input_result == 1)
		{
			//mouse bttn press
			GrabCard();
		}
		else if (m_input_result == 0)
		{
			//mouse bttn release
			DropCard();
		}

		//update the window
		WindowUpdate();

		//if there was a movement that was valid, then move
		//those items.
		if (m_check_result == 1)
		{
			MoveTo(m_numCards, m_new_col);
		}
	}
	m_window.GetWindow().close();
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
	m_deck.SetScale(m_scale / 8 + m_scale);
	m_deck.Reset();
	m_window.SetDimension(m_Xres, m_Yres);
	m_window.Update();
	StartGame();
}

/*//////////////////////////////////////////
	WindowUpdate
		Updates the windows with the correct
		graphics currently in the buffer
*///////////////////////////////////////////
void Freecell::WindowUpdate()
{
	if (m_window.GetWindow().isOpen())
	{
		//Draw the freecells and homecells first (doesnt matter the order here)
		DrawFree();
		DrawHome();

		//Draw al the columns
		DrawColumns();

		//ghost cards are the last thing drawn to the buffer
		//because they 'sit' on top of everything else
		if (m_m1_pressed && m_card_grabbed)
		{
			DrawGhost();
		}

		//after everything is drawn, update the screen
		m_window.Update();
	}
}

/*///////////////////////////////////////////////////////////
	UserInput
		gathers data about where the users
		mouse is, has on Click listeners
		etc

		returns 1 for a mouse buton press and 0 for a release
		-1 if something else
*/////////////////////////////////////////////////////////////
int Freecell::UserInput()
{
	int cond = -1;

	//check to see if the window is open
	if (m_window.GetWindow().isOpen())
	{
		//after the window events have happend, now 
		//we can track mouse button presses and ESC
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			m_m1_pressed = true;
			m_Mouse_x = Mouse::getPosition(m_window.GetWindow()).x / m_scale;
			m_Mouse_y = Mouse::getPosition(m_window.GetWindow()).y / m_scale;
			cond = 1;
		}
		else
		{
			m_m1_pressed = false;
			cond = 0;
		}

		//check for esc key being pressed
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			m_Running = false;
		}

	}
	else
	{
		m_Running = false;
	}

	return cond;
}

/*////////////////////////////////////////////////////////////
	Get Region
		A tool for getting the general region the mouse is in
*/////////////////////////////////////////////////////////////
Freecell::ElmRegion Freecell::GetRegion()
{
	ElmRegion reg = NONE;
	//freecells
	if (m_Mouse_x >= 20 && m_Mouse_x < m_offset * 4 && m_Mouse_y >= 20 && m_Mouse_y < 75)
	{
		reg = FREE;
	}

	//Homecells
	else if (m_Mouse_x >= (5 + m_offset * 8) && m_Mouse_x < (5 + m_offset * 12)
		&& m_Mouse_y >= 20 && m_Mouse_y < 75)
	{
		reg = HOME;
	}

	//Columns
	else if (m_Mouse_x >= 20 && m_Mouse_x < 5 + m_offset * 8
		&& m_Mouse_y >= col_y && m_Mouse_y < m_Yres)
	{
		reg = COLUMN;
	}

	return reg;
}

/*//////////////////////////////////////////////
	Check Order
		checks the order of the 
		card in m_ghost
		useful for determining if the cards were
		grabbed or not
*///////////////////////////////////////////////
bool Freecell::CheckOrder()
{
	bool flag = true;

	Node<Card>* travel = m_ghost.GetHead();

	while (flag && travel != nullptr)
	{
		if (travel->GetNext() != nullptr)
		{
			//check coloring order
			switch (travel->GetData().GetSuit())
			{
			case Card::SPADE: //if its a spade, check if the next card is a club
				if (travel->GetNext()->GetData().GetSuit() == Card::CLUB)
				{
					flag = false;
				}
				break;

			case Card::CLUB: //if its a club, check if next card is a spade
				if (travel->GetNext()->GetData().GetSuit() == Card::SPADE)
				{
					flag = false;
				}
				break;

			case Card::HEART: //check for diamond
				if (travel->GetNext()->GetData().GetSuit() == Card::DIAMOND)
				{
					flag = false;
				}
				break;

			case Card::DIAMOND: //check for heart
				if (travel->GetNext()->GetData().GetSuit() == Card::HEART)
				{
					flag = false;
				}
				break;
			}

			//check numerical order
			if (flag && travel->GetData().GetFace() < travel->GetNext()->GetData().GetFace())
			{
				flag = false;
			}
		}
		travel = travel->GetNext();
	}

	return flag;
}

/*///////////////////////////////////////////////////////
	Grab Card
		attempts to resolve the coordinates at the mouse
		and place that associated card and any below it
		into ghost.
*////////////////////////////////////////////////////////
void Freecell::GrabCard()
{
	if (m_m1_pressed && !m_card_grabbed)
	{
		//if m1 is pressed and cards are already not grabbed

		//determine which 'area' we are trying to access.
		switch (GetRegion())
		{
		case FREE: //freecell region
			//check if there is any cards in freecell first
			if (m_f_count != 0)
			{
				//by dividing by the offset, we can determine the array
				//positioning
				int cell_num = (m_Mouse_x / m_offset);
				if (cell_num = 4)
				{
					cell_num = 3;
				}

				//check to see if there is cards there
				if (cell_num < m_f_count)
				{
					//load a copy of the card into ghost
					m_ghost.Append(m_freecells[cell_num]);
					m_ghost_count++;
					if (1 <= MovementCheck())
					{
						m_card_grabbed = true;
					}
				}
			}
			break; //end freecell case

		case HOME: //home cell region
			//will not allow players to grab from the home region
			break;

		case COLUMN: //column region
			//a little tricky, but there is a formula per card. 
			//first determine which column we /could/ be looking at
			m_old_col = m_Mouse_x / m_offset;
			//to make sure the full width of the cards is explored
			//and nothing is grabbed from inbetween card spaces
			

			if (m_Mouse_x % m_offset < 5 || m_Mouse_x % m_offset > 20)
			{
				//not in margins, on a definite card column
				if (m_Mouse_x % m_offset <= 1)
				{
					//if on the right edge of a card, we want to insure we dont
					//grab the other column by mistake
					m_old_col--;
				}

				if (m_old_col > m_columns.GetLength() - 1)
				{
					m_old_col = m_columns.GetLength() - 1;
				}

				//now find which card we are looking at
				if (!m_columns[m_old_col].IsEmpty())
				{
					//get the amound of cards that are in the column
					int num_c_card = m_col_counts[m_old_col];
					num_c_card--; //gets the index of the last card


					//check the boundry of the stack of cards
					if (m_Mouse_y <= (col_y * m_scale + (num_c_card + 1) * card_space * m_scale + 50 * m_scale))
					{
						m_card_in_col = (m_Mouse_y - col_y) / card_space; //calculate the index value of the card touched
						//if the y position of the mouse is within the cards available
						//check for grabbing of last card
						if (m_card_in_col > num_c_card)
						{
							m_card_in_col--; //decrement to match the card in the last
							//position of the stack
						}

						//check if we can grab this (these) cards
						if (((num_c_card + 1) - m_card_in_col) <= MovementCheck())
						{
							//if it passed the movement check, then load the cards into
							//the holder while prepending them to ghost
							for (int i = 0; i < (num_c_card + 1) - m_card_in_col; i++)
							{
								m_ghost.Prepend(m_columns[m_old_col].Peek());
								m_ghost_count++;
								m_holder.Push(m_columns[m_old_col].Pop());
							}

							//once copies are in ghost, push everything from
							//holder back to the colum they belonged to

							while (!m_holder.IsEmpty())
							{
								m_columns[m_old_col].Push(m_holder.Pop());
							}

							//now cards should be in ghost to be transitioned
							//around the board visually.
							//set grabbed to true
							m_card_grabbed = CheckOrder();
						}
					}
				}
			}
			break;

		default:
			break;
		}

	}
	else if (!m_m1_pressed && m_card_grabbed)
	{
		DropCard();
	}

	if (!m_card_grabbed)
	{
		DropCard();
	}
}

/*/////////////////////////////////////////
	Drop Card
		attempts to drop a card (or cards)
		into a spot 
		if applicable

		if not valid, the ghost cards
		are removed
*//////////////////////////////////////////
void Freecell::DropCard()
{
	//temp purge m_ghost
	m_ghost.Purge();
	m_ghost_count = 0;
	m_card_grabbed = false;
}

/*//////////////////////////////////////////////
	MovementCheck
		checks to make sure a given movement
		is valid (based on how many cards can be
		moved at a specific time)

		returns the number of cards that can
		currently be moved
*////////////////////////////////////////////////
int Freecell::MovementCheck()
{
	int cond = -1;
	// movement is determined by the 
	//# of available freecells + 1 + #of available colums * # of freecells
	//however, lets instead choose the number of open free cells
	//plus 1 for each empty column
	cond = (4 - m_f_count) + (m_empty_cols) + 1;

	return cond;
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

	//make sure the current col counts are reset
	for (int i = 0; i < 8; i++)
	{
		m_col_counts[i] = 0;
	}

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
			m_col_counts[i]++;
		}
	}
}

/*
	Draw functions down past this point

	I found it easier to break down each
	draw function into each section of the board
	so that the original function for drawing the 
	screen would not take up 2 pages of Visual Studio
*/

/*//////////////////////////////////////////////////////////////
	Draw ghost

		This one is special.
		when it starts it looks at the coordinates that the
		mouse was at when a left click occured
		
		if that click is in a valid location for a card
		then that card and the ones below it are loaded
		into m_ghost
		those objects are then cloned and 'attatched' to
		the mouse until the mouse releases the button.

		on release the ghost should disappear
		(and if the movement was valid, 
			then the cards are moved to their new location)
*////////////////////////////////////////////////////////////////
void Freecell::DrawGhost()
{
	//temporarily cout
	//std::cout << "Mouse Coords: " << m_Mouse_x << ',' << m_Mouse_y << std::endl;

	if (!m_ghost.IsEmpty())
	{
		Node<Card>* travel = m_ghost.GetHead();
		int num_card = 0;
		//display everything in ghost relative to mouse
		while (travel != nullptr)
		{
			GroupObj temp = travel->GetData().GetCard(true);

			//position relative to mouse cursor
			temp.SetPos(m_Mouse_x * m_scale - 25 * m_scale,
				m_Mouse_y * m_scale + num_card * card_space * m_scale - 25 * m_scale);

			num_card++; //increment the num of cards displayed

			m_window.DrawObj(temp);

			travel = travel->GetNext();
		}
	}
}

/*//////////////////////////////////////////////////////////////////////
	Draw Free

		the freecell portion of the board
		draws in the placemarkers for empty cells
		then any cards that belong in there need to use a smaller 
		card blank.

		The freecells start at approx ~20 px from the top left and top
		of the screen (also in account with scaling)
*////////////////////////////////////////////////////////////////////////
void Freecell::DrawFree()
{
	//first draw the blank square objects
	int section = 0;
	m_blanks.SetName("blanks");
	m_blanks.SetPos(20 * m_scale, 20 * m_scale); //sets the group position here
	m_blanks.ResetGroup();

	//non Static obj for the actual things that belong to the group
	DrawableObj eblanc;
	eblanc.SetSrc(RES_CARD_E);
	eblanc.SetScale(m_scale);

	//set the position and name of the first empty one
	eblanc.SetName("1");
	eblanc.SetPos(0, 0);
	//insert it into the group
	m_blanks.Insert(eblanc);
	section++;

	//repeat for the next ones
	eblanc.SetName("2");
	eblanc.SetPos(section * m_offset * m_scale, 0);
	m_blanks.Insert(eblanc);
	section++;

	eblanc.SetName("3");
	eblanc.SetPos(section * m_offset * m_scale, 0);
	m_blanks.Insert(eblanc);
	section++;

	eblanc.SetName("4");
	eblanc.SetPos(section * m_offset * m_scale, 0);
	m_blanks.Insert(eblanc);
	section+=2;

	//special symbol
	eblanc.SetName("sym");
	eblanc.SetSrc(RES_SYMBOL);
	eblanc.SetPos(section * m_offset * m_scale - 10 * m_scale, 0);
	m_blanks.Insert(eblanc);
	section = 0;

	//after the blanks are in their group, draw them to the screen buffer
	m_window.DrawObj(m_blanks);

	//now draw any cards that may be in the freecell
	if (m_f_count > 0)
	{
		for (int i = 0; i < m_f_count && i < m_freecells.GetLength(); i++)
		{
			bool isGhost = false;
			if (!m_ghost.IsEmpty()) //if ghost is not empty
			{
				for (int count = 0; !isGhost && count < m_ghost_count; count++)
				{
					//we want to check if the current card in freecell matches any in ghost
					if (m_freecells[i] == m_ghost.First())
					{
						isGhost = true;
					}
				}
			}

			if (!isGhost)
			{
				GroupObj temp(m_freecells[i].GetCard(true));
				temp.SetPos(i * m_offset * m_scale + m_scale * m_padding, 0);
				m_window.DrawObj(temp);
			}
		}
	}
}

/*/////////////////////////////////////////////////////////////////////
	Draw Home
		Similar to Feecells
		however only need draw the top object of each respective stack
*//////////////////////////////////////////////////////////////////////
void Freecell::DrawHome()
{
	//first draw the blank square objects
	int section = 0;
	int horizontalGap = 8;
	m_homebl.SetName("blanks");
	m_homebl.SetPos(5 * m_scale + horizontalGap * m_offset * m_scale, 20 * m_scale); //sets the group position here

	m_homebl.ResetGroup();

	//non Static obj for the actual things that belong to the group
	DrawableObj eblanc;
	eblanc.SetSrc(RES_CARD_E);
	eblanc.SetScale(m_scale);

	//set the position and name of the first empty one
	eblanc.SetName("1");
	eblanc.SetPos(0, 0);
	//insert it into the group
	m_homebl.Insert(eblanc);
	section++;

	//repeat for the next ones
	eblanc.SetName("2");
	eblanc.SetPos(section * m_offset * m_scale, 0);
	m_homebl.Insert(eblanc);
	section++;

	eblanc.SetName("3");
	eblanc.SetPos(section * m_offset * m_scale, 0);
	m_homebl.Insert(eblanc);
	section++;

	eblanc.SetName("4");
	eblanc.SetPos(section * m_offset * m_scale, 0);
	m_homebl.Insert(eblanc);
	section = 0;

	//after the blanks are in their group, draw them to the screen buffer
	m_window.DrawObj(m_homebl);

	//now draw any cards that may be in the homecell
	for (int i = 0; i < m_homecells.GetLength(); i++)
	{
		if (!m_homecells[i].IsEmpty())
		{
			GroupObj temp(m_homecells[i].Peek().GetCard(true));
			temp.SetPos(i * m_offset * m_scale + m_scale * m_padding, 0);
			m_window.DrawObj(temp);
		}
	}
}

/*/////////////////////////////////////////////////////
	Draw Columns

		A little more difficult
		Pop everything from a column into a temp stack,
		then pop everything back into the column,
		but while doing that draw the cards in their
		repsective locations.
*//////////////////////////////////////////////////////
void Freecell::DrawColumns()
{
	int num_card = 0;


	//have a blank obj n standby
	GroupObj blanks;
	blanks.SetName("blanks");

	//non Static obj for the actual things that belong to the group
	DrawableObj eblanc;
	eblanc.SetSrc(RES_CARD_E);
	eblanc.SetScale(m_scale);

	//set the position and name of the first empty one
	eblanc.SetName("1");
	eblanc.SetPos(0, 0);
	//insert it into the group
	blanks.Insert(eblanc);

	m_empty_cols = 0;

	//have to process each column
	for (int i = 0; i < m_columns.GetLength(); i++)
	{
		num_card = 0; //set the num of cards to zero
		m_col_counts[i] = 0;
		if (m_columns[i].IsEmpty())
		{
			//if the column is empty, then draw a 
			//blank square in its place
			blanks.SetPos(col_x * m_scale + i * m_offset * m_scale, 
							col_y * m_scale + num_card * 20 * m_scale);
			m_window.DrawObj(blanks); //draw the blank
			m_empty_cols++; //increment how many empty columns there are
		}
		else
		{
			//pop all items in col[i] into m_holder
			while (!m_columns[i].IsEmpty())
			{
				m_holder.Push(m_columns[i].Pop());
				m_col_counts[i]++;
			}

			//push them all back
			while (!m_holder.IsEmpty())
			{
				m_columns[i].Push(m_holder.Pop());

				bool isGhost = false;
				if (!m_ghost.IsEmpty()) //if ghost is not empty
				{
					Node<Card>* travel = m_ghost.GetHead();
					while (!isGhost && travel != nullptr)
					{
						//check travels data with the top of the column
						if (travel->GetData() == m_columns[i].Peek())
						{
							isGhost = true;
						}
						//increment travel
						travel = travel->GetNext();
					}
				}

				//if the obj is not listed in ghost, draw it to screen.
				if (!isGhost)
				{
					GroupObj temp;
					temp = m_columns[i].Peek().GetCard(false); //get the drawable objgroup from the card
					temp.SetPos(col_x * m_scale + i * m_offset * m_scale,
						col_y * m_scale + num_card * card_space * m_scale);
					num_card++; //increment after so the next cards displayed are offeset vertically
					m_window.DrawObj(temp); //draw the obj
				}
			}
		}
	}
}