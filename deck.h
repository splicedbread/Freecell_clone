#ifndef DECK_H
#define DECK_H
#include <iostream>
#include <chrono>
#include <random>
#include "Array.h"
#include "MySwap.h"
#include "card.h"

/*///////////////////////////////////////////////////////////////////////////
	Author: Jacob Vanderkarr
	Date: 12/2/18
	File: deck.h

	Purpose: A deck made for the blackjack game, where it can easily be used
	and randomized.
*///////////////////////////////////////////////////////////////////////////
class Deck
{
public:
	Deck();
	~Deck();

	Deck(const Deck & cpy);

	Card Draw();
	void Reset();
	void Empty();
	void Randomise();
	int GetSize();
	void SetScale(float scale);
private:
	float m_scale;
	void Load();
	int m_c_cards;
	Array<Card> m_deck;
	std::default_random_engine gen;
};
#endif // !DECK_H