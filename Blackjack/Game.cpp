#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <Windows.h>
#include "Game.h"
#include "HumanPlayer.h"
#include "Deck.h"
#include "ComputerPlayer.h"
#include "ExtraFns.h"

const int width = 81;

Game::Game()
{
	std::cout << "\n\n************************************Blackjack***********************************\n" << std::endl;

	//ask how many human players
	m_humanPlayerCount = -1;
	GetIntInput("\tNumber of human players (0 to 6):  ", 
		m_humanPlayerCount, 0, 6, "\tPlease enter a number between 0 and 6");

	//vector of HumanPlayers created and named, player 1 is element 0, player 2 is element 1 etc
	for(int i = 1; i <= m_humanPlayerCount; i++)
	{
		m_hPlayers.push_back(HumanPlayer(i));
		m_hPlayers[i-1].SetName();
		
		//taking bets
		std::string inputRequest = "\t" + m_hPlayers[i-1].m_name + ", how much do you want to bet? (1-10) ";
		m_hPlayers[i-1].m_bet = GetIntInput(inputRequest,
									(int&)m_hPlayers[i-1].m_bet, 1, 10, "\tPlease enter a number 1 to 10");
	}

	//ask how many computer players
	m_compPlayerCount = -1;
	GetIntInput("\n\tNumber of computer players (0 to 5):  ",
		m_compPlayerCount, 0, 5, "\tPlease enter a number between 0 and 6");

	//create ComputerPlayers
	std::string compNames[5] = {"Sidney", "Alex", "Khaled", "Ramona", "Mei"};
	int compMaxTotals[5] = {12, 21, 16, 15, 18};
	float compBets[5] = {1, 1, 5, 3, 10};

	for(int i = 0; i < m_compPlayerCount; i++)
	{
		m_cPlayers.push_back(ComputerPlayer(compNames[i], compMaxTotals[i], compBets[i]));
	}

	//asking about 5:6 odds on blackjack
	char fiveSix = GetYNInput("\n\tDo you want to play 5:6 blackjack? (y/n) ");
	if(fiveSix == 'y')
	{
		m_blackjackOdds = 5./6.;
	}
	else
	{
		m_blackjackOdds = 3./2.;
	}

	m_house = House();
	m_deck = Deck();
	m_deck.Shuffle();

	Deal(1);
}
//function to ask for an integer answer to a question
int Game::GetIntInput(std::string request, int &m_var, int lowerBound, int upperBound, std::string errorMessage)
{
	int input;
	//keep asking the question until a valid answer is inputted
	do
	{
		std::cout << request;
		std::cin >> input;

		//m_var only gets set to the value inputted if it is an integer in the specified range
		if(input >= lowerBound && input <= upperBound)
		{
			m_var = input;
		}
		else
		{
			std::cout << errorMessage << std::endl;
			std::cin.clear();
			std::cin.ignore();
		}
	} while(m_var != input || std::cin.fail());

	return m_var;
}
Game::~Game()
{
}
void Game::Deal(int roundNumber)
{
	std::cout << "\n" << "********************************************************************************" << std::endl;
	std::cout << "\n\tRound " << roundNumber << "\n" << std::endl;

	//if this isn't the first round then stuff needs to be reset
	if(roundNumber > 1)
	{
		//removing players who want to drop out, DropOut asks for y/n input
		m_hPlayers.erase(std::remove_if(m_hPlayers.begin(), m_hPlayers.end(), DropOut), m_hPlayers.end());
		
		//removing players who've run out of money
		m_hPlayers.erase(std::remove_if(m_hPlayers.begin(), m_hPlayers.end(), BankEmpty), m_hPlayers.end());
		m_cPlayers.erase(std::remove_if(m_cPlayers.begin(), m_cPlayers.end(), BankEmpty), m_cPlayers.end());

		if(m_cPlayers.size() == 0 && m_hPlayers.size() == 0)
		{
			return;
		}
		std::cout << "\n" << std::endl;

		//resetting everything and taking bets before dealing a new hand
		for(int i = 1; i <= m_hPlayers.size(); i++)
		{
			m_hPlayers[i-1].EmptyHand();

			//setting bets
			std::string inputRequest = "\t" + m_hPlayers[i-1].m_name + ", how much do you want to bet? (1-10) ";
			m_hPlayers[i-1].m_bet = GetIntInput(inputRequest, 
										(int&)m_hPlayers[i-1].m_bet, 1, 10, "\tPlease enter a number 1 to 10");

			m_hPlayers[i-1].m_isBust = false;
			m_hPlayers[i-1].m_blackjack = false;
		}
		for(int i = 1; i <= m_cPlayers.size(); i++)
		{
			m_cPlayers[i-1].EmptyHand();
			m_cPlayers[i-1].m_isBust = false;
			m_cPlayers[i-1].m_blackjack = false;

		}

		m_house.EmptyHand();
		m_house.m_isBust = false;
		m_isBlackjack = false;

		m_deck = Deck();
		m_deck.Shuffle();

		std::cout << "\n" << std::endl;
	}

	m_deck.DealHand(m_house);
	m_house.m_hand[0].Flip();
	m_house.PrintHand(false);
	std::cout << "\n" << std::endl;

	//dealing human players
	for(int i = 1; i <= m_hPlayers.size(); i++)
	{
		m_deck.DealHand(m_hPlayers[i-1]);
		m_hPlayers[i-1].PrintHand();
	}

	//dealing computer players
	for(int i = 1; i <= m_cPlayers.size(); i++)
	{
		m_deck.DealHand(m_cPlayers[i-1]);
		m_cPlayers[i-1].PrintHand(true);
	}

	CheckBlackjack();
}
void Game::CheckBlackjack()
{
	//if house has a blackjack, cut to the end
	if((m_house.m_hand.back().GetValue() == 1 || m_house.m_hand.front().GetValue() == 1) 
		&& m_house.HandTotal() == 11)
	{
		m_isBlackjack = true;
		EndGame();
	}
	else
	{
		m_isBlackjack = false;
		HumanTurn();
	}
}
void Game::HumanTurn()
{
	for(int i = 0; i < m_hPlayers.size(); i++)
	{
		std::cout << "\n" << std::setw(width) << std::setfill('*') << std::endl;
		std::cout << "\n" << std::endl;
		m_hPlayers[i].PrintHand();

		if(m_hPlayers[i].m_aceCount != 0)
		{
			m_hPlayers[i].Aces();
		}
		
		m_deck.HitOrStick(m_hPlayers[i]);
	}

	ComputerTurn();
}
void Game::ComputerTurn()
{
	for(int i = 0; i < m_cPlayers.size(); i++)
	{
		std::cout << "\n" << std::setw(width) << std::endl;
		std::cout << "\n" << std::endl;

		m_cPlayers[i].PrintHand(true);
		ComputerDecision(m_cPlayers[i]);
	}

	HouseTurn();
}
void Game::HouseTurn()
{
	std::cout << "\n" << std::setw(width) << std::endl;
	std::cout << "\n" << std::endl;

	//flip house's first card face up
	m_house.m_hand[0].Flip();
	std::cout << "\n" << std::endl;
	m_house.PrintHand(true);

	ComputerDecision(m_house);

	EndGame();
}
void Game::ComputerDecision(ComputerPlayer &computerPlayer)
{
	//if player has a blackjack
	if(computerPlayer.m_handTotal + 10 == 21 && 
		(computerPlayer.m_hand.front().GetValue() == 10 || computerPlayer.m_hand.back().GetValue() == 10))
	{
		//set to 22 so it will beat all hands except another blackjack, the house's hand is also set
		//to 22 if it has a blackjack
		computerPlayer.m_handTotal = 22;
		computerPlayer.m_isBust = false;
		computerPlayer.m_blackjack = true;

		std::cout << "\t";
		computerPlayer.GetName();
		std::cout << " has: 21 (blackjack)" << std::endl;

	}
	else
	{
		computerPlayer.m_blackjack = false;

		while(computerPlayer.m_handTotal < computerPlayer.m_maxTotal)
		{
			std::cout << "\tHit" << std::endl;
			m_deck.Hit(computerPlayer);
			computerPlayer.PrintHand(true);
		}
		
		if(computerPlayer.m_handTotal >= computerPlayer.m_maxTotal && computerPlayer.m_handTotal <= 21)
		{
			std::cout << "\tStick" << std::endl;
			std::cout << "\t" << computerPlayer.m_name << " has: " << computerPlayer.m_handTotal << std::endl;
			computerPlayer.m_isBust = false;
		}
		else
		{
			std::cout << "\t" << computerPlayer.m_name << " went bust!" << std::endl;
			std::cout << "\t" << computerPlayer.m_name << " has: BUSTED" << std::endl;
			computerPlayer.m_isBust = true;
			computerPlayer.SetBustTotal();
		}
	}

	Sleep(2500);
}
void Game::EndGame()
{
	std::cout << "\n" << std::setw(width) << std::endl;
	
	//printing out the house's score
	if(m_isBlackjack == true)
	{
		//flip house's first card face up
		m_house.m_hand[0].Flip();
		m_house.PrintHand(true);
		std::cout << "\t" <<  m_house.m_name << ": 21 (blackjack)" << std::endl;
		m_house.m_handTotal = 22;
	}
	else if(m_house.m_isBust == true)
	{
		std::cout << "\t" << m_house.m_name << ": bust" << std::endl;
	}
	else
	{
		std::cout << "\t" <<  m_house.m_name << ": " << m_house.m_handTotal << std::endl;
	}
	
	std::cout << "\n" << std::endl;
	//printing other players' scores
	for(int i = 0; i < m_hPlayers.size(); i++)
	{
		ScoreCalc(m_hPlayers[i]);
		CheckBank(m_hPlayers[i]);
	}
	for(int i = 0; i < m_cPlayers.size(); i++)
	{
		ScoreCalc(m_cPlayers[i]);
		CheckBank(m_cPlayers[i]);
	}

	m_playAgain = GetYNInput("\n\tDo you want to play again? (y/n) ");
}
void Game::CheckBank(GenericPlayer player)
{	
	if(player.m_bank <= 0)
	{
		std::cout << "\n\t" << player.m_name << ", you lost all your money! You're out" << std::endl;
	}
}

//calculates whether the inputted player won, lost or pushed and updates their bank-roll accordingly
void Game::ScoreCalc(GenericPlayer &player)
{
	if(player.m_handTotal == 22 && m_house.m_handTotal < 22)
	{
			std::cout << "\t" << player.m_name << "\twins!";
			player.m_bank += m_blackjackOdds*player.m_bet;
	}
	else
	{
		//if the player pushes, their bank-roll stays the same, the bet hasn't been taken out at any point before now
		if(player.m_handTotal == m_house.m_handTotal)
		{
			std::cout << "\t" << player.m_name << "\tpushes";
		}
		else if(player.m_handTotal > m_house.m_handTotal)
		{
			std::cout << "\t" << player.m_name << "\twins!";
			player.m_bank += player.m_bet;
		}
		else
		{
			std::cout << "\t" << player.m_name << "\tloses";
			player.m_bank -= player.m_bet;
		}
	}
	if(player.m_isBust == true)
	{
		std::cout << "\t(bust)" << std::endl;
	}
	else if(player.m_handTotal == 22)
	{
		std::cout << "\t(21, blackjack)" << std::endl;
	}
	else
	{
		std::cout << "\t(" << player.m_handTotal << ")" << std::endl;
	}
	
	std::cout << "\t" << player.m_name << " has " << player.m_bank << " in the bank\n" << std::endl;
	
}
//runs the whole game and deals with playing multiple rounds
void Game::RunGame()
{
	//starts from 2 because when the Deal function is first called inside the loop it's the second time it's been called
	int i = 2;
	Game game = Game();

	//m_playAgain is set at the end of Game
	while(game.m_playAgain == 'y')
	//for(int i = 0; i < 100; i++)
	{
		//it gets reset here because Deal leads through the whole game to the end
		game.Deal(i);
		
		if(game.m_playAgain == 'n')
		{
			return;
		}
		
		i++;
	}
}