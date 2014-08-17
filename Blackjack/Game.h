#ifndef GAME_H
#define GAME_H

#include "House.h"
#include "Deck.h"
#include "Hand.h"
#include "HumanPlayer.h"
#include <vector>

class GenericPlayer;
class Hand;
class ComputerPlayer;

class Game
{
public:
	Game();
	~Game();
	void CheckBlackjack();
	void Deal(int roundNumber);
	void HumanTurn();
	void HouseTurn();
	void EndGame();
	void ScoreCalc(GenericPlayer &player);
	static void RunGame();
	void ComputerDecision(ComputerPlayer &computerPlayer);
	void ComputerTurn();
	void CheckBank(GenericPlayer player);

	//request is the question to ask, m_var is the variable you want to set, 
	//upper and lowerBound set the range of acceptable answers
	//errorMessage is what is printed if the input is the wrong type or out of range
	int GetIntInput(std::string request, int &var, int lowerBound, int upperBound, std::string errorMessage);

private:
	
	int m_compPlayerCount;
	std::vector<ComputerPlayer> m_cPlayers;

	int m_humanPlayerCount;
	std::vector<HumanPlayer> m_hPlayers;

	Deck m_deck;
	House m_house;
	bool m_isBlackjack;
	char m_playAgain;
	float m_blackjackOdds;

};
#endif