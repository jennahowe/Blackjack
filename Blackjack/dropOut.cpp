#include <iostream>
#include "HumanPlayer.h"
#include "Extrafns.h"
bool DropOut(GenericPlayer player)
{
	//asking if each player wants to keep playing
	std::string inputRequest = "\t" + player.Name() + ", do you want to keep playing? (y/n) ";
	char choice = GetYNInput(inputRequest);

	if(choice == 'y')
	{
		return false;
	}
	if(choice == 'n')
	{
		return true;
	}
}