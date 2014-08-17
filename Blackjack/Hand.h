#ifndef HAND_H
#define HAND_H

#include <vector>
#include "Card.h"

class Hand
{
public:
	Hand();
	~Hand();
	void AddCard(Card card);
	void EmptyHand();
	const Card GetCard(int position);
	const int HandTotal();
	const void PrintHandTotal();

	friend class Game;
	friend class Deck;

protected:
	std::vector<Card> m_hand;
	int m_handTotal;
	int m_aceCount;

};
#endif