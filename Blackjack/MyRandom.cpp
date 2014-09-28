#include <iostream>
#include <ctime>

//used for shuffling the deck
int MyRandom(int i){ 
	srand(time(NULL));
	return std::rand() % i;
}