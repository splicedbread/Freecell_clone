#include "card.h"
#include "FreeCellResources.h"
/*///////////////////////////////////////////////
	Author: Jacob Vanderkarr
	DAte: 12/2/18
	File: card.cpp
	Purpose: Implementation file for Card class
*///////////////////////////////////////////////

//default ctor
Card::Card() : m_suit(Card::SPADE), m_face(Card::ACE), m_scale(1.0f)
{
}

//Overloaded Ctor is the only one that can be used, default is private
Card::Card(CardSuit suit, CardType face) : m_suit(suit), m_face(face), m_scale(1.0f)
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

//not equivalency
bool Card::operator!=(const Card & right)
{
	return (*this == right);
}

//operator = overload 
Card & Card::operator=(const Card & right)
{
	// TODO: insert return statement here
	if (this != &right)
	{
		this->m_face = right.m_face;
		this->m_suit = right.m_suit;
		this->m_card = right.m_card;
		this->m_scale = right.m_scale;
	}
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

/*/////////////////////////////////////////////
	GetCard is a function that returns
	the drawable group associated for the card
	call update to the card before this
	to get the most current group obj

	mode = true for small card
*//////////////////////////////////////////////
GroupObj & Card::GetCard(bool mode)
{
	UpdateCard(mode);
	return m_card;
}

/*/////////////////////////
	Set Scale
		sets the relative
		scale for the card
*///////////////////////////
void Card::SetScale(float scale)
{
	if (m_scale > 0.0f)
	{
		m_scale = scale;
	}
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

/*/////////////////////////////////////////////
	UpdateCard
		a private function
		that serves as a way to insert details
		about a card into a GroupObj

		size makes the card have a small or large 
		card background
		size = true for small card
*//////////////////////////////////////////////
void Card::UpdateCard(bool size)
{
	m_card.ResetGroup();

	//after resetting the card and positions
	//we should now insert new drawable objs
	//into the group

	DrawableObj e_blank("card", m_scale); //the card blank
	DrawableObj e_suit("suit", m_scale / 1.5f);
	DrawableObj e_value("cardval", m_scale / 1.5f);

	//set the res values for each of the drawables
	//card
	if (!size)
	{
		e_blank.SetSrc(RES_CARD);
	}
	else
	{
		e_blank.SetSrc(RES_CARD_S);
	}

	//suit obj
	switch (m_suit)
	{
	case Card::SPADE:
		e_suit.SetSrc(RES_SPADE);
		break;
	case Card::CLUB:
		e_suit.SetSrc(RES_CLUB);
		break;
	case Card::HEART:
		e_suit.SetSrc(RES_HEART);
		break;
	case Card::DIAMOND:
		e_suit.SetSrc(RES_DIAMOND);
		break;
	}

	//value obj
	switch (m_face)
	{
	case Card::ACE:
		e_value.SetSrc(RES_ACE);
		break;
	case Card::TWO:
		e_value.SetSrc(RES_TWO);
		break;
	case Card::THREE:
		e_value.SetSrc(RES_THREE);
		break;
	case Card::FOUR:
		e_value.SetSrc(RES_FOUR);
		break;
	case Card::FIVE:
		e_value.SetSrc(RES_FIVE);
		break;
	case Card::SIX:
		e_value.SetSrc(RES_SIX);
		break;
	case Card::SEVEN:
		e_value.SetSrc(RES_SEVEN);
		break;
	case Card::EIGHT:
		e_value.SetSrc(RES_EIGHT);
		break;
	case Card::NINE:
		e_value.SetSrc(RES_NINE);
		break;
	case Card::TEN:
		e_value.SetSrc(RES_TEN);
		break;
	case Card::JACK:
		e_value.SetSrc(RES_JACK);
		break;
	case Card::QUEEN:
		e_value.SetSrc(RES_QUEEN);
		break;
	case Card::KING:
		e_value.SetSrc(RES_KING);
		break;
	}

	//set positions relative to the card

	//the card needs to be 0,0, as the anchor for the group
	e_blank.SetPos(0, 0);

	//we would like to use padding so things dont touch the card edge
	//for the value we want it in the top left corner, followed by the suit symbol
	e_value.SetPos(R_PADDING * m_scale, R_PADDING * m_scale); // padding x padding location
	e_suit.SetPos(4 * R_PADDING * m_scale, R_PADDING * m_scale); // 4 * padding x padding location

	//set the group name for all of drawable obj
	e_blank.SetGroup(m_card.GetName());
	e_value.SetGroup(m_card.GetName());
	e_suit.SetGroup(m_card.GetName());

	//after all that, push everythng into the group obj
	m_card.Insert(e_blank); //the card background first
	m_card.Insert(e_value);
	m_card.Insert(e_suit);
}