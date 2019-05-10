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

	m_window.SetTitle("Freecell 2: The Search for More Money");
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

	m_window.SetTitle("Freecell 2: Moichendising (cheat mode)");
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

	m_f_count = 0;
	m_m1_pressed = false;
	m_card_grabbed = false;

	//initialization
	m_freecells.SetLength(0);
	m_freecells.SetLength(4);

	m_homecells.SetLength(0);
	m_homecells.SetLength(4);

	for (int i = 0; i < m_homecells.GetLength(); i++)
	{
		m_homecells[i].SetSize(13);
	}

	m_columns.SetLength(0);
	m_columns.SetLength(8);

	m_ghost.Purge();
	m_ghost_count = 0;

	while (!m_holder.IsEmpty())
	{
		m_holder.Pop();
	}

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

		if (CheckWinCond())
		{
			m_Running = false;
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
	m_deck.SetScale(m_scale / 8 + m_scale);
	m_window.SetDimension(m_Xres, m_Yres);

	do
	{
		m_restart = false;
		m_deck.Reset();
		m_window.Update();
		StartGame();
	} while (m_restart);

	m_window.GetWindow().close();
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

	//Dog
	else if (m_Mouse_x >= (5 * m_offset - 10) && m_Mouse_x < (7 * m_offset)
		&& m_Mouse_y >= 20 && m_Mouse_y < 75)
	{
		m_restart = true;
		m_Running = false;
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
				if (travel->GetNext()->GetData().GetSuit() == Card::CLUB 
					|| travel->GetNext()->GetData().GetSuit() == Card::SPADE)
				{
					flag = false;
				}
				break;

			case Card::CLUB: //if its a club, check if next card is a spade
				if (travel->GetNext()->GetData().GetSuit() == Card::SPADE
					|| travel->GetNext()->GetData().GetSuit() == Card::CLUB)
				{
					flag = false;
				}
				break;

			case Card::HEART: //check for diamond
				if (travel->GetNext()->GetData().GetSuit() == Card::DIAMOND
					|| travel->GetNext()->GetData().GetSuit() == Card::HEART)
				{
					flag = false;
				}
				break;

			case Card::DIAMOND: //check for heart
				if (travel->GetNext()->GetData().GetSuit() == Card::HEART
					|| travel->GetNext()->GetData().GetSuit() == Card::DIAMOND)
				{
					flag = false;
				}
				break;
			}

			//check numerical order
			if (flag && !(static_cast<int>(travel->GetData().GetFace()) - 1 == 
				static_cast<int>(travel->GetNext()->GetData().GetFace())))
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
				int cell_num = 0;
				cell_num = m_Mouse_x / m_offset;
				if (cell_num == 4)
				{
					cell_num = 3;
				}

				//check to see if there is cards there
				if (cell_num < m_f_count)
				{
					//load a copy of the card into ghost
					m_ghost.Append(m_freecells[cell_num]);
					m_ghost_count++;
					
					m_card_grabbed = true;
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

/*///////////////////////////////////////
	MoveFreeCellsDown
		after a freecell removal
		the remaining freecell
		cards get moved down in the array
*////////////////////////////////////////
void Freecell::MoveFreeCellsDown()
{
	if (m_f_count > 1)
	{
		//move everything down to left side of freecells
		for (int i = 0; i < m_f_count && i < m_freecells.GetLength(); i++)
		{
			if (i == m_prev_freecell && i + 1 < m_freecells.GetLength())
			{
				Swap(m_freecells[i], m_freecells[i + 1]);
				m_prev_freecell++; //keep shifting the empty free cell to the back.
			}
		}
	}
	m_f_count--;
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
	if (m_card_grabbed)
	{
		switch (GetRegion())
		{
		case HOME: //homecells
			//can only move 1 card at a time
			if (m_ghost_count == 1)
			{
				//if its one card then proceed
				//get the card in ghost suit to determine
				//which column it needs to look into first
				if (!m_ghost.IsEmpty() && !m_homecells[m_ghost.First().GetSuit()].IsEmpty())
				{
					//if it is not empty, check if our value can fit
					if (static_cast<int>(m_homecells[m_ghost.First().GetSuit()].Peek().GetFace()) + 1
						== static_cast<int>(m_ghost.First().GetFace()))
					{
						//if the cards value is 1 more than the current card in the homecell
						//then we can place our card into the homecell.
						bool found = false;
						int card_index = 0;
						//first check if its in the freecells
						for (int i = 0; !found && i < m_freecells.GetLength() && i < m_f_count; i++)
						{
							if (!m_ghost.IsEmpty())
							{
								if (m_ghost.First().GetSuit() == m_freecells[i].GetSuit())
								{
									if (m_ghost.First().GetFace() == m_freecells[i].GetFace())
									{
										found = true;
										card_index = i;
									}
								}
							}
						}

						if (found)
						{
							//if the card was found in freecell, move it
							//to the appropiate homecell
							m_homecells[m_ghost.First().GetSuit()].Push(m_freecells[card_index]);
							m_prev_freecell = card_index;
							MoveFreeCellsDown();
						}
						else
						{
							//if not, then assume it was from the previous column
							if (!m_ghost.IsEmpty())
							{
								m_homecells[m_ghost.First().GetSuit()].Push(m_columns[m_old_col].Pop());
							}
						}
					}
				}
				else if (!m_ghost.IsEmpty() && m_ghost.First().GetFace() == Card::ACE)
				{
					//if it is empty, check if the card we are trying
					//to move is the Ace of Spades
					bool found = false;
					int card_index = 0;
					//first check if its in the freecells
					for (int i = 0; !found && i < m_freecells.GetLength() && i < m_f_count; i++)
					{
						if (!m_ghost.IsEmpty())
						{
							if (m_ghost.First().GetSuit() == m_freecells[i].GetSuit())
							{
								if (m_ghost.First().GetFace() == m_freecells[i].GetFace())
								{
									found = true;
									card_index = i;
								}
							}
						}
					}

					if (found)
					{
						//if the card was found in freecell, move it
						//to the appropiate homecell
						m_homecells[m_ghost.First().GetSuit()].Push(m_freecells[card_index]);
						m_prev_freecell = card_index;
						MoveFreeCellsDown();
					}
					else
					{
						//if not, then assume it was from the previous column
						m_homecells[m_ghost.First().GetSuit()].Push(m_columns[m_old_col].Pop());
					}
				}
			}
			break;

		case FREE: //freecells
			if (m_ghost_count == 1 && !m_ghost.IsEmpty())
			{
				//if it is empty, check if the card we are trying
					//to move is the Ace of Spades
				bool found = false;
				int card_index = 0;
				//first check if its in the freecells
				for (int i = 0; !found && i < m_freecells.GetLength() && i < m_f_count; i++)
				{
					if (!m_ghost.IsEmpty())
					{
						if (m_ghost.First().GetSuit() == m_freecells[i].GetSuit())
						{
							if (m_ghost.First().GetFace() == m_freecells[i].GetFace())
							{
								found = true;
								card_index = i;
							}
						}
					}
				}

				if (!found)
				{
					if (m_f_count < m_freecells.GetLength())
					{
						//should be coming from a column only tbh
						m_freecells[m_f_count] = m_columns[m_old_col].Pop();
						m_f_count++;
					}
				}
			}
			break;

		case COLUMN: //columns

			std::cout << "entering columns drop card.\n";
			//we can move either 1 item or multiples
			//a little tricky, but there is a formula per card. 
			//first determine which column we /could/ be looking at
			m_new_col = m_Mouse_x / m_offset;
			//to make sure the full width of the cards is explored
			//and nothing is grabbed from inbetween card spaces


			if (m_Mouse_x % m_offset < 5 || m_Mouse_x % m_offset > 20)
			{
				//not in margins, on a definite card column
				if (m_Mouse_x % m_offset <= 1)
				{
					//if on the right edge of a card, we want to insure we dont
					//grab the other column by mistake
					m_new_col--;
				}

				if (m_new_col > m_columns.GetLength() - 1)
				{
					m_new_col = m_columns.GetLength() - 1;
				}

				std::cout << "old column , new column: " << m_old_col << ',' << m_new_col << std::endl;

				//ensure this is a new col we want to look at
				if (m_new_col != m_old_col);
				{
					if (m_columns[m_new_col].IsEmpty() && !m_ghost.IsEmpty())
					{
						//if the new column is empty
						//check freecell for the value first
						//if it is empty, check if the card we are trying
						//to move is the Ace of Spades
						bool found = false;
						int card_index = 0;
						//first check if its in the freecells
						for (int i = 0; !found && i < m_freecells.GetLength() && i < m_f_count; i++)
						{
							if (m_ghost.First().GetSuit() == m_freecells[i].GetSuit())
							{
								if (m_ghost.First().GetFace() == m_freecells[i].GetFace())
								{
									found = true;
									card_index = i;
								}
							}
						}

						if (found)
						{
							//if the card is in freecell, assume there is only 1
							//and move it to the open spot
							m_columns[m_new_col].Push(m_freecells[card_index]);
							m_prev_freecell = card_index;
							MoveFreeCellsDown();
						}
						else
						{
							/*
								if its not found in freecells
								then we are to assume that it is coming
								from another column. 
								
								we have to check for 2 things
								1. if the amount of cards we can move is valid
								2. moving them
							*/
							std::cout << "value not in freecell.\n";
							//create a travel node from the tail
							Node<Card>* travel = m_ghost.GetTail();

							int allowedMovement = MovementCheck() - ((m_empty_cols - 1) * (m_freecells.GetLength() - m_f_count));

							//because we are moving *to* an empty column, we have to discount 1 space in movement
							if (m_ghost_count <= allowedMovement)
							{
								int moved = 0; //how many cards have been moved
								int storage = 0; //how many storage spaces have we used
								int track = 0; //how many storage spaces have we used and passed
								bool store_flag = false; //is this a valid storage space
								int freeCount = 0;

								if (m_ghost_count > 1)
								{
									while (moved < m_ghost_count)
									{
										//move as many cards as we can into freecell first
										for (int i = m_freecells.GetLength() - 1; travel != nullptr && moved < m_ghost_count && i > m_f_count - 1; i--)
										{
											if (travel->GetData() == m_columns[m_old_col].Peek())
											{
												//if the next itteration is the last card in ghost
												if (moved + 1 == m_ghost_count)
												{
													m_columns[m_new_col].Push(m_columns[m_old_col].Pop());
												}
												else
												{
													//if that is the same as the columns top push it into a freecell
													m_freecells[i] = m_columns[m_old_col].Pop();
													freeCount++;
												}
											}

											std::cout << "moving colum to freecell.\n";
											moved++;
											travel = travel->GetPrevious();
										}

										//if moved is still less than ghost count, then load our stored cards in freecell
										//into an empty column
										if (moved < m_ghost_count)
										{

											track = storage;
											for (int j = 0; !store_flag && j < m_columns.GetLength(); j++)
											{
												if (m_col_counts[j] == 0)
												{
													if (track == 0)
													{
														store_flag = true;
													}
													else
													{
														track--;
													}
												}

												//if a valid storage has been found
												if (store_flag)
												{
													//put everything that we can from free cell into a blank column
													for (int i = m_f_count; i < m_freecells.GetLength(); i++)
													{
														m_columns[j].Push(m_freecells[i]);
														freeCount--;
													}
													storage++;
												}
											}
										}
										else
										{
											//consolidate all the storages starting with current freecell
											//then left storages are consilidated
											for (int i = m_freecells.GetLength() - freeCount; i < m_freecells.GetLength(); i++)
											{
												m_columns[m_new_col].Push(m_freecells[i]);
											}
											freeCount = 0;

											//after the freecell values have been put into the new column
											//consolodate all the storeage
											for (int i = m_columns.GetLength() - 1; i > 0; i--)
											{
												int dex = m_f_count;
												//if a columns count is zero, but is not empty, we used 
												//it for storage
												if (m_col_counts[i] == 0 && !m_columns[i].IsEmpty())
												{
													//if the count is 0 and the column is not empty, unload it into freecell
													while (!m_columns[i].IsEmpty())
													{
														m_freecells[dex] = m_columns[i].Pop();
														dex++;
														std::cout << "emptying column: " << i << std::endl;
													}

													//then empty freecell back into the new column
													for (int j = m_f_count; j < m_freecells.GetLength(); j++)
													{
														m_columns[m_new_col].Push(m_freecells[j]);
													}
												}
											}
										}
									}
								}
								else if (m_ghost_count == 1)
								{
									m_columns[m_new_col].Push(m_columns[m_old_col].Pop());
								}
							}
						}
					}
					else
					{
						//if the new column is not empty
						//check freecell for the value first
						bool found = false;
						int card_index = 0;
						//first check if its in the freecells
						for (int i = 0; !found && i < m_freecells.GetLength() && i < m_f_count; i++)
						{
							if (!m_ghost.IsEmpty())
							{
								if (m_ghost.First().GetSuit() == m_freecells[i].GetSuit())
								{
									if (m_ghost.First().GetFace() == m_freecells[i].GetFace())
									{
										found = true;
										card_index = i;
									}
								}
							}
						}

						if (found && !m_ghost.IsEmpty())
						{
							//if the card is in freecell, assume there is only 1
							//and move it to the open spot
							if (!m_ghost.IsEmpty())
							{
								bool flag = true;
								switch (m_freecells[card_index].GetSuit())
								{
								case Card::SPADE: //if its a spade, check if the next card is a club
									if (m_columns[m_new_col].Peek().GetSuit() == Card::CLUB
										|| m_columns[m_new_col].Peek().GetSuit() == Card::SPADE)
									{
										flag = false;
									}
									break;

								case Card::CLUB: //if its a club, check if next card is a spade
									if (m_columns[m_new_col].Peek().GetSuit() == Card::SPADE
										|| m_columns[m_new_col].Peek().GetSuit() == Card::CLUB)
									{
										flag = false;
									}
									break;

								case Card::HEART: //check for diamond
									if (m_columns[m_new_col].Peek().GetSuit() == Card::DIAMOND
										|| m_columns[m_new_col].Peek().GetSuit() == Card::HEART)
									{
										flag = false;
									}
									break;

								case Card::DIAMOND: //check for heart
									if (m_columns[m_new_col].Peek().GetSuit() == Card::HEART
										|| m_columns[m_new_col].Peek().GetSuit() == Card::DIAMOND)
									{
										flag = false;
									}
									break;
								}

								//check numerical order
								if (flag && !(static_cast<int>(m_columns[m_new_col].Peek().GetFace()) - 1 ==
									static_cast<int>(m_freecells[card_index].GetFace())))
								{
									flag = false;
								}


								if (flag)
								{
									//if all the checks have been passed, then move the item here
									m_columns[m_new_col].Push(m_freecells[card_index]);
									m_prev_freecell = card_index;
									MoveFreeCellsDown();
								}
							}
						}
						else
						{
							//the column is not empty
						/*
							if its not found in freecells
							then we are to assume that it is coming
							from another column.

							we have to check for 2 things
							1. if the amount of cards we can move is valid
							2. moving them
						*/
						//create a travel node from the tail
							Node<Card>* travel = m_ghost.GetTail();

							int allowedMovement = MovementCheck();

							//because we are moving *to* an empty column, we have to discount 1 space in movement
							//also need to check if 
							if (m_ghost_count <= allowedMovement && m_ghost_count > 1)
							{
								int moved = 0; //how many cards have been moved
								int storage = 0; //how many storage spaces have we used
								int track = 0; //how many storage spaces have we used and passed
								bool store_flag = false; //is this a valid storage space
								int freeCount = 0;
								bool n_flag = true;


								while (moved < m_ghost_count)
								{
									//move as many cards as we can into freecell first
									for (int i = m_freecells.GetLength() - 1; travel != nullptr && moved < m_ghost_count && i > m_f_count - 1; i--)
									{
										if (travel->GetData() == m_columns[m_old_col].Peek())
										{
											//if the next itteration is the last card in ghost
											if (moved + 1 == m_ghost_count)
											{
												//then move it from its column to the new column first
												if (!m_columns[m_old_col].IsEmpty())
												{
													if (!m_ghost.IsEmpty())
													{

														switch (m_columns[m_old_col].Peek().GetSuit())
														{
														case Card::SPADE: //if its a spade, check if the next card is a club
															if (m_columns[m_new_col].Peek().GetSuit() == Card::CLUB
																|| m_columns[m_new_col].Peek().GetSuit() == Card::SPADE)
															{
																n_flag = false;
															}
															break;

														case Card::CLUB: //if its a club, check if next card is a spade
															if (m_columns[m_new_col].Peek().GetSuit() == Card::SPADE
																|| m_columns[m_new_col].Peek().GetSuit() == Card::CLUB)
															{
																n_flag = false;
															}
															break;

														case Card::HEART: //check for diamond
															if (m_columns[m_new_col].Peek().GetSuit() == Card::DIAMOND
																|| m_columns[m_new_col].Peek().GetSuit() == Card::HEART)
															{
																n_flag = false;
															}
															break;

														case Card::DIAMOND: //check for heart
															if (m_columns[m_new_col].Peek().GetSuit() == Card::HEART
																|| m_columns[m_new_col].Peek().GetSuit() == Card::DIAMOND)
															{
																n_flag = false;
															}
															break;
														}

														//check numerical order
														if (n_flag && !(static_cast<int>(m_columns[m_new_col].Peek().GetFace()) - 1 ==
															static_cast<int>(m_columns[m_old_col].Peek().GetFace())))
														{
															n_flag = false;
														}


														if (n_flag)
														{
															//if all the checks have been passed, then move the item here
															m_columns[m_new_col].Push(m_columns[m_old_col].Pop());
														}
													}
												}
											}
											else
											{
												//if that is the same as the columns top push it into a freecell
												m_freecells[i] = m_columns[m_old_col].Pop();
												freeCount++;
											}
										}

										moved++;
										travel = travel->GetPrevious();
									}

									//if moved is still less than ghost count, then load our stored cards in freecell
									//into an empty column
									if (moved < m_ghost_count)
									{
										track = storage;
										for (int j = 0; !store_flag && j < m_columns.GetLength(); j++)
										{
											if (m_col_counts[j] == 0)
											{
												if (track == 0)
												{
													store_flag = true;
												}
												else
												{
													track--;
												}
											}

											//if a valid storage has been found
											if (store_flag)
											{
												//put everything that we can from free cell into a blank column
												for (int i = m_f_count; i < m_freecells.GetLength(); i++)
												{
													if (!m_ghost.IsEmpty())
													{
														bool flag = true;

														switch (m_freecells[i].GetSuit())
														{
														case Card::SPADE: //if its a spade, check if the next card is a club
															if (m_columns[j].Peek().GetSuit() == Card::CLUB
																|| m_columns[j].Peek().GetSuit() == Card::SPADE)
															{
																flag = false;
															}
															break;

														case Card::CLUB: //if its a club, check if next card is a spade
															if (m_columns[j].Peek().GetSuit() == Card::SPADE
																|| m_columns[j].Peek().GetSuit() == Card::CLUB)
															{
																flag = false;
															}
															break;

														case Card::HEART: //check for diamond
															if (m_columns[j].Peek().GetSuit() == Card::DIAMOND
																|| m_columns[j].Peek().GetSuit() == Card::HEART)
															{
																flag = false;
															}
															break;

														case Card::DIAMOND: //check for heart
															if (m_columns[j].Peek().GetSuit() == Card::HEART
																|| m_columns[j].Peek().GetSuit() == Card::DIAMOND)
															{
																flag = false;
															}
															break;
														}

														//check numerical order
														if (flag && !(static_cast<int>(m_columns[j].Peek().GetFace()) - 1 ==
															static_cast<int>(m_freecells[i].GetFace())))
														{
															flag = false;
														}


														if (flag)
														{
															//if all the checks have been passed, then move the item here
															m_columns[j].Push(m_freecells[i]);
															freeCount--;
														}
													}
												}
												storage++;
											}
										}
									}
									else
									{
										//consolidate all the storages starting with current freecell
										//then left storages are consilidated
										for (int i = m_freecells.GetLength() - freeCount; i < m_freecells.GetLength(); i++)
										{
											if (!m_ghost.IsEmpty())
											{
												bool flag = true;

												switch (m_freecells[i].GetSuit())
												{
												case Card::SPADE: //if its a spade, check if the next card is a club
													if (m_columns[m_new_col].Peek().GetSuit() == Card::CLUB
														|| m_columns[m_new_col].Peek().GetSuit() == Card::SPADE)
													{
														flag = false;
													}
													break;

												case Card::CLUB: //if its a club, check if next card is a spade
													if (m_columns[m_new_col].Peek().GetSuit() == Card::SPADE
														|| m_columns[m_new_col].Peek().GetSuit() == Card::CLUB)
													{
														flag = false;
													}
													break;

												case Card::HEART: //check for diamond
													if (m_columns[m_new_col].Peek().GetSuit() == Card::DIAMOND
														|| m_columns[m_new_col].Peek().GetSuit() == Card::HEART)
													{
														flag = false;
													}
													break;

												case Card::DIAMOND: //check for heart
													if (m_columns[m_new_col].Peek().GetSuit() == Card::HEART
														|| m_columns[m_new_col].Peek().GetSuit() == Card::DIAMOND)
													{
														flag = false;
													}
													break;
												}

												//check numerical order
												if (flag && !(static_cast<int>(m_columns[m_new_col].Peek().GetFace()) - 1 ==
													static_cast<int>(m_freecells[i].GetFace())))
												{
													flag = false;
												}


												if (flag && n_flag)
												{
													//if all the checks have been passed, then move the item here
													m_columns[m_new_col].Push(m_freecells[i]);
												}
												else if (!n_flag)
												{
													m_columns[m_old_col].Push(m_freecells[i]);
												}
											}
										}
										freeCount = 0;

										//after the freecell values have been put into the new column
										//consolodate all the storeage
										for (int i = m_columns.GetLength() - 1; i > 0; i--)
										{
											int dex = m_f_count;
											//if a columns count is zero, but is not empty, we used 
											//it for storage
											if (m_col_counts[i] == 0 && !m_columns[i].IsEmpty())
											{
												//if the count is 0 and the column is not empty, unload it into freecell
												while (!m_columns[i].IsEmpty())
												{
													m_freecells[dex] = m_columns[i].Pop();
													dex++;
												}

												//then empty freecell back into the new column
												for (int j = m_f_count; j < m_freecells.GetLength(); j++)
												{
													bool flag = true;

													switch (m_freecells[j].GetSuit())
													{
													case Card::SPADE: //if its a spade, check if the next card is a club
														if (m_columns[m_new_col].Peek().GetSuit() == Card::CLUB
															|| m_columns[m_new_col].Peek().GetSuit() == Card::SPADE)
														{
															flag = false;
														}
														break;

													case Card::CLUB: //if its a club, check if next card is a spade
														if (m_columns[m_new_col].Peek().GetSuit() == Card::SPADE
															|| m_columns[m_new_col].Peek().GetSuit() == Card::CLUB)
														{
															flag = false;
														}
														break;

													case Card::HEART: //check for diamond
														if (m_columns[m_new_col].Peek().GetSuit() == Card::DIAMOND
															|| m_columns[m_new_col].Peek().GetSuit() == Card::HEART)
														{
															flag = false;
														}
														break;

													case Card::DIAMOND: //check for heart
														if (m_columns[m_new_col].Peek().GetSuit() == Card::HEART
															|| m_columns[m_new_col].Peek().GetSuit() == Card::DIAMOND)
														{
															flag = false;
														}
														break;
													}

													//check numerical order
													if (flag && !(static_cast<int>(m_columns[m_new_col].Peek().GetFace()) - 1 ==
														static_cast<int>(m_freecells[j].GetFace())))
													{
														flag = false;
													}


													if (flag && n_flag)
													{
														//if all the checks have been passed, then move the item here
														m_columns[m_new_col].Push(m_freecells[j]);
													}
													else if (n_flag)
													{
														m_columns[m_old_col].Push(m_freecells[j]);
													}
												}
											}
										}
									}
								}
							}
							else if (m_ghost_count == 1)
							{
								if (!m_ghost.IsEmpty())
								{
									bool flag = true;

									switch (m_ghost.First().GetSuit())
									{
									case Card::SPADE: //if its a spade, check if the next card is a club
										if (m_columns[m_new_col].Peek().GetSuit() == Card::CLUB
											|| m_columns[m_new_col].Peek().GetSuit() == Card::SPADE)
										{
											flag = false;
										}
										break;

									case Card::CLUB: //if its a club, check if next card is a spade
										if (m_columns[m_new_col].Peek().GetSuit() == Card::SPADE
											|| m_columns[m_new_col].Peek().GetSuit() == Card::CLUB)
										{
											flag = false;
										}
										break;

									case Card::HEART: //check for diamond
										if (m_columns[m_new_col].Peek().GetSuit() == Card::DIAMOND
											|| m_columns[m_new_col].Peek().GetSuit() == Card::HEART)
										{
											flag = false;
										}
										break;

									case Card::DIAMOND: //check for heart
										if (m_columns[m_new_col].Peek().GetSuit() == Card::HEART
											|| m_columns[m_new_col].Peek().GetSuit() == Card::DIAMOND)
										{
											flag = false;
										}
										break;
									}

									//check numerical order
									if (flag && !(static_cast<int>(m_columns[m_new_col].Peek().GetFace()) - 1 ==
										static_cast<int>(m_columns[m_old_col].Peek().GetFace())))
									{
										flag = false;
									}
									

									if (flag)
									{
										//if all the checks have been passed, then move the item here
										m_columns[m_new_col].Push(m_columns[m_old_col].Pop());
									}
								}
							}
						}
					}
				}
			}
			break;
		}
	}

	//purge m_ghost
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
	if (m_empty_cols >= 1)
	{
		cond = (4 - m_f_count) + ((m_empty_cols - 1) * (4 - m_f_count)) + 1;
	}
	else
	{
		cond = (4 - m_f_count) + 1;
	}

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
	for (int i = 0; cond && i < m_columns.GetLength(); i++)
	{
		if (!m_columns[i].IsEmpty())
		{
			cond = false;
		}
	}

	return cond;
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
				temp.SetPos(i * m_offset * m_scale + col_x * m_scale, col_x * m_scale);
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
			temp.SetPos(i * m_offset * m_scale + m_scale * horizontalGap * m_offset + 5 * m_scale, 20 * m_scale);
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