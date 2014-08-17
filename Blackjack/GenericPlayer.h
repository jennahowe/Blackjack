#ifndef GENERICPLAYER_H
#define GENERICPLAYER_H

#include "Hand.h"

class GenericPlayer: public Hand
{
public:
	GenericPlayer();
	void GetName();
	virtual const void PrintHand();
	void Aces();
	virtual void SetBustTotal();
	int GetBank();
	std::string Name();
	
	friend class Game;
	friend class Deck;

protected:
	bool m_isBust;
	bool m_blackjack;
	float m_bank;
	float m_bet;
	std::string m_name;
};
#endif