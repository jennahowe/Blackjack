#include <iostream>
#include "GenericPlayer.h"

//generalised function for asking for a yes/no answer with a catch for if a wrong type is entered
char GetYNInput(std::string request){
	char choice = '0';
	char input = '0';

	do{
		std::cout << request;
		std::cin >> input;

		if(input == 'y' || input == 'n'){
			choice = input;
		}
		else{
			std::cout << "\tPlease enter either 'y' or 'n'" << std::endl;
			std::cin.clear();
			std::cin.ignore();
		}

	} while(std::cin.fail() || (choice != 'y' && choice != 'n'));
	
	return choice;
}