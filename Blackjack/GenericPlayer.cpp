#include "GenericPlayer.h"
#include "Deck.h"
#include <iostream>

GenericPlayer::GenericPlayer(): Hand()
{
	m_bank = 1000;
	m_bet = -1;
}
void GenericPlayer::GetName()
{
	std::cout << m_name;
}
std::string GenericPlayer::Name()
{
	return m_name;
}
const void GenericPlayer::PrintHand()
{
	std::cout << "\t" << m_name << ":\t";

	for(int i = 0; i < m_hand.size(); i++)
	{
		std::cout << m_hand[i].GetCardId() << "  ";
	}
	std::cout << "(";
	PrintHandTotal();
	std::cout << ")" << std::endl;
}
void GenericPlayer::Aces()
{
	//aces are worth 1 by default, they are effectively set to 11 if that doesn't push the total over 21
	if(m_handTotal + 10 <= 21)
	{
		m_handTotal += 10;
	}
}
//if a player (except the house, there's another version of this for House) goes bust,
//their total is set to -1 so they always lose
void GenericPlayer::SetBustTotal()
{
	m_handTotal = -1;
}
int GenericPlayer::GetBank()
{
	return m_bank;
}