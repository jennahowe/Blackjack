#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "Deck.h"
#include "GenericPlayer.h"
#include "ExtraFns.h"

Deck::Deck(){
	//populating deck
	std::string name[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
	char suit[4] = {'h', 'd', 'c', 's'};

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 13; j++){
			m_deck.push_back(Card(name[j], suit[i]));
		}
	}
}
void Deck::Shuffle(){
	std::random_shuffle(m_deck.begin(), m_deck.end(), MyRandom);
}
void Deck::DealHand(Hand &player){
	Hit(player);
	Hit(player);
}
void Deck::Hit(Hand &player){
	Card card = m_deck.back();
	player.AddCard(card);
	m_deck.pop_back();
}
//this is in deck because Hit is in here as well
void Deck::HitOrStick(GenericPlayer &player){
	if(player.m_handTotal == 21){
		player.m_handTotal = 22;
		player.m_isBust = false;
		player.m_blackjack = true;

		std::cout << "\t";
		player.GetName();
		std::cout << " has: 21 (blackjack)" << std::endl;

	}

	while(player.m_handTotal < 21){
		player.m_blackjack = false;
	
		std::string inputRequest = ("\t" + player.m_name + ", hit? (y/n)  ");
		char choice = GetYNInput(inputRequest);

		if(choice == 'y'){
			Hit(player);
			player.PrintHand();
			
			//if the last card added is an ace and the total is more than 10
			Card lastCard = player.m_hand.back();
			if(lastCard.GetValue() == 1 && m_handTotal > 10){
				player.Aces();
			}

			if(player.m_handTotal > 21){
				std::cout << "\t" << player.m_name << " went bust!" << std::endl;
				std::cout << "\t" << player.m_name << " has: BUSTED" << std::endl;
				player.m_isBust = true;
				player.m_handTotal = -1;
				break;
			}
			else if(player.m_handTotal == 21){
				std::cout << "\t" << player.m_name << " has: " << player.m_handTotal << std::endl;
				player.m_isBust = false;
				break;
			}
			else{
				player.m_isBust = false;
			}
		}
		
		else if(choice == 'n'){
			//sets hand total to max possible (taking account of aces) without going bust 
			if(player.m_aceCount != 0 && player.m_handTotal + 10 <= 21){
				player.m_handTotal += 10;
			}
		
			std::cout << "\t" << player.m_name << " has: " << player.m_handTotal << std::endl;
			break;
		}
	}
}