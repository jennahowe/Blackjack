#include <iostream>
#include "HumanPlayer.h"
#include "GenericPlayer.h"

HumanPlayer::HumanPlayer(): GenericPlayer(){
	m_playerNumber = 0;
}
HumanPlayer::HumanPlayer(int playerNumber): GenericPlayer(){
	m_playerNumber = playerNumber;
}
void HumanPlayer::SetName(){
	std::cout << "\n\tHuman player " << m_playerNumber << " name:  ";
	std::cin >> m_name;
}
