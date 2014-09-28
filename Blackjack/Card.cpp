#include "Card.h"
#include <iostream>

Card::Card(){
	m_value = 1;
	m_suit = 'X';
	m_name = "Unitialised";
	m_cardId = "Unitialised";
}

Card::Card(std::string name, char suit){
	m_name = name;
	m_suit = suit;
	m_value = SetValue(name);
	m_cardId = name + suit;
}
Card::~Card(){
}
const void Card::Print(){
	std::cout << "Card = " << m_cardId << "  Value = " << m_value << "  Name = " << m_name << "  Suit = " << m_suit << std::endl;
}
const bool Card::IsFaceUp(){
	if(m_cardId.compare("XX") == 0){
		return false;
	}
	else{
		return true;
	}
}
void Card::Flip(){
	std::string tempCardId = m_name + m_suit;
	std::string faceDownId = "XX";

	if(!IsFaceUp()){
		m_cardId.swap(tempCardId);
	}
	else{
		m_cardId.swap(faceDownId);
	}
}
//set the value of a card according to its name
int Card::SetValue(std::string name){
	int value = 0;
	if(name.compare("2") == 0 || name.compare("3") == 0 || name.compare("4") == 0 || 
	   name.compare("5") == 0 || name.compare("6") == 0 || name.compare("7") == 0 || 
	   name.compare("8") == 0 || name.compare("9") == 0){

		value = atoi(name.c_str());
		return value;
	}
	else if(name.compare("10") == 0 || name.compare("J") == 0 || name.compare("Q") == 0 || name.compare("K") == 0){
		value = 10;
		return value;
	}
	//aces can be worth 1 or 11, setting 1 as default
	else if(name.compare("A") == 0){
		value = 1;
		return value;
	}
	else{
		std::cout << "Error: Card name must be a number between 2 and 10 or a letter J, Q, K, or A." << std::endl;
		return value;
	}
}
const int Card::GetValue(){
	return m_value;
}
const std::string Card::GetCardId(){
	return m_cardId;
}