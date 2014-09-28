#include <iostream>
#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer(): GenericPlayer(){
}
ComputerPlayer::ComputerPlayer(std::string name, int maxTotal, float bet): GenericPlayer(){
	m_name = name;
	m_maxTotal = maxTotal;
	m_bet = bet;
}
const void ComputerPlayer::PrintHand(bool showTotal) {
	std::cout << "\t" << m_name << ":\t";

	for(int i = 0; i < m_hand.size(); i++){
		std::cout << m_hand[i].GetCardId() << "  ";
	}
	if(showTotal){
		std::cout << "(";
		PrintHandTotal();
		std::cout << ")" << std::endl;
	}
}
