#include <iostream>
#include "GenericPlayer.h"

//checks if a player has run out of money or not
bool BankEmpty(GenericPlayer player)
{
	if(player.GetBank() <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}