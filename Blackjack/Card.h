#ifndef CARD_H
#define CARD_H

#include <string>

class Card
{
public:
	Card();
	Card(std::string name, char suit);
	~Card();
	const void Print();
	const bool IsFaceUp();
	void Flip();
	int SetValue(std::string name);
	const int GetValue();
	const std::string GetCardId();
	
private:
	int m_value;
	char m_suit;
	std::string m_name;
	std::string m_cardId;
};
#endif