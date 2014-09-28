#include "Hand.h"
#include "Card.h"
#include <vector>
#include <iostream>

Hand::Hand(){
}
Hand::~Hand(){
}
void Hand::AddCard(Card card){
	m_hand.push_back(card);
}
void Hand::EmptyHand(){
	m_hand.clear();
}
const Card Hand::GetCard(int position){
	return m_hand[position];
}
const int Hand::HandTotal(){
	int handTotal = 0;
	int aceCount = 0;

	//counting aces and summing the card values
	for (std::vector<Card>::iterator it = m_hand.begin(); it != m_hand.end(); it++){
		Card card = *it;
		int cardValue = card.GetValue();
		handTotal += cardValue;
		
		if(cardValue == 1){
			aceCount++;
		}
	}
	m_aceCount = aceCount;
	m_handTotal = handTotal;
	return handTotal;
}
const void Hand::PrintHandTotal(){
	HandTotal();
	
	//only prints the higher option for the hand total if it's under 21
	if(m_aceCount == 0 || m_handTotal + 10 > 21){
		std::cout << m_handTotal;
	}

	else{
		std::cout << m_handTotal << " or " << m_handTotal + 10;
	}
}