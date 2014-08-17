#ifndef DECK_H
#define DECK_H

#include "Hand.h"
#include "GenericPlayer.h"
int myRandom(int i);

class Deck: public Hand
{
public:
	Deck();
	void Shuffle();
	void DealHand(Hand &player);
	void Hit(Hand &player);
	void HitOrStick(GenericPlayer &player);
	friend class GenericPlayer;

protected:
	std::vector<Card> m_deck;
};

#endif