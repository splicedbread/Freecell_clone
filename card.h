#ifndef CARD_H
#define CARD_H
#include <iostream>
#include "GroupObj.h"

#define R_PADDING 5

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	Date: 12/2/18
	File: card.h
	Class: Card

	Purpose: description for a card object that internalizes the suit type and card type of a given card
	
*////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Card
{
public:
	enum CardType
	{
		ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
		EIGHT, NINE, TEN, JACK, QUEEN, KING
	};

	enum CardSuit
	{
		SPADE, CLUB, HEART, DIAMOND
	};

	Card();
	Card(CardSuit suit, CardType face);
	~Card();

	bool operator == (const Card & right);
	bool operator != (const Card & right);
	Card & operator = (const Card & right);

	CardSuit GetSuit() const;
	CardType GetFace() const;
	GroupObj & GetCard(bool mode);
	void SetScale(float scale);
	void SetSuit(CardSuit suit);
	void SetFace(CardType face);
private:
	void UpdateCard(bool size);

	float m_scale;
	GroupObj m_card;
	CardSuit m_suit;
	CardType m_face;
};
#endif // !CARD_H
