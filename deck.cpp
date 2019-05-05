#include "deck.h"
//default ctor
Deck::Deck() : m_c_cards(0)
{
	//Load the deck with the cards
	m_deck.SetLength(52); //set the length of the array to 52
	Load();
}

//default dtor, does nothing really
Deck::~Deck()
{
}

/*//////////////////////////////////////////////////////////////////////////
	Draw() returns the card that is drawn from the deck, then removing that
	card from the deck until the next reset
*///////////////////////////////////////////////////////////////////////////
Card Deck::Draw()
{
	//Drawing a card should return the top of the stack, 
	//Drawing the last element, and returning it, then deleting it
	//from the deck, will reduce the deck size for the next draw.
	Card tempCard(Card::SPADE, Card::ACE);
	tempCard = m_deck[m_c_cards - 1];
	m_c_cards--; //decrease how 'many' cards there is in the deck
	return tempCard;
}

/*//////////////////////////////////////////////////////////////////
	Reset() clears the deck configuration, then loads the deck again
*///////////////////////////////////////////////////////////////////
void Deck::Reset()
{
	m_c_cards = 0;
	Empty();
	Load();
}
/*/////////////////////////////////////////
	Calls the dynamic array empty function
*//////////////////////////////////////////
void Deck::Empty()
{
	m_deck.SetLength(0); //clear it
	m_deck.SetLength(52); //set the size back to 52
}

/*////////////////////////////////////////////////////////////
	Randomise() mixes up the deck using a simple random number
	gen and a swap function
*/////////////////////////////////////////////////////////////
void Deck::Randomise()
{
	//setting up the seed for the random number generator
	std::chrono::high_resolution_clock clock;
	std::chrono::high_resolution_clock::time_point period = clock.now();
	std::chrono::high_resolution_clock::duration dur = std::chrono::high_resolution_clock::now() - period;
	unsigned seed = dur.count();
	gen.seed(seed);

	int rngCardNum;
	std::uniform_int_distribution<int> card_distribution(0, m_deck.GetLength() - 1);

	for (int i = 0; i < m_deck.GetLength(); i++)
	{
		rngCardNum = card_distribution(gen);//generate an element from the deck
		Swap(i, rngCardNum); //swap those elements with the current selected one
		card_distribution.reset(); // reset the rng num, just in case
	}
}

//Return how many cards are in the deck
int Deck::GetSize()
{
	return m_c_cards;
}

/*////////////////////////////////////////////////////////////////////////////
	Load loads the dynamic array of the deck with cards, called
	only in the deck constructor, and in Reset() 
*/////////////////////////////////////////////////////////////////////////////
void Deck::Load()
{
	//createa temporary card, due to the nature its an Ace of Spades
	Card tempCard(Card::SPADE, Card::ACE);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			tempCard.SetFace(static_cast<Card::CardType>(j)); //sets face between ace and king
			tempCard.SetSuit(static_cast<Card::CardSuit>(i)); //sets suit between spade and diamond
			m_deck[m_c_cards] = tempCard; //inserts card at m_c_cards index
			m_c_cards++; //a new card has been added, so increment the number
		}
	}
}
