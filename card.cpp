#include "card.h"
#include "String.h"
/*///////////////////////////////////////////////
	Author: Jacob Vanderkarr
	DAte: 12/2/18
	File: card.cpp
	Purpose: Implementation file for Card class
*///////////////////////////////////////////////

//default ctor
Card::Card() : m_suit(Card::SPADE), m_face(Card::ACE)
{
}

//Overloaded Ctor is the only one that can be used, default is private
Card::Card(CardSuit suit, CardType face) : m_suit(suit), m_face(face)
{
}

//card dtor doesnt do anything
Card::~Card()
{
}

//equivalency operator, returns true if the face and suit is the same
bool Card::operator==(const Card & right)
{
	return ((this->m_face == right.m_face) && (this->m_suit == right.m_suit));
}

//operator = overload 
Card & Card::operator=(const Card & right)
{
	// TODO: insert return statement here
	this->m_face = right.m_face;
	this->m_suit = right.m_suit;
	return *this;
}

/*//////////////////////////////////
	GetSuit returns the cards suit
*/////////////////////////////////
Card::CardSuit Card::GetSuit() const
{
	return m_suit;
}

/*///////////////////////////////////////////////
	GetFace returns the cards face value as enum
*////////////////////////////////////////////////
Card::CardType Card::GetFace() const
{
	return m_face;
}

/*/////////////////////////////////////////////////////////////////////
	Sets the suit type, useful for changing a card if the need arrises
*//////////////////////////////////////////////////////////////////////
void Card::SetSuit(CardSuit suit)
{
	m_suit = suit;
}

/*/////////////////////////////////////////////////////////////////////
	Sets the face type, useful for changing a card if the need arrises
*//////////////////////////////////////////////////////////////////////
void Card::SetFace(CardType face)
{
	m_face = face;
}