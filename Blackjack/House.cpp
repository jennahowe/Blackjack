#include <iostream>
#include "ComputerPlayer.h"
#include "House.h"

House::House(): ComputerPlayer()
{
	m_name = "Dealer";
	m_maxTotal = 17;

}
//set to zero so any player who isn't bust wins,
//a player who is bust still loses because their total is set to -1
void House::SetBustTotal()
{
	m_handTotal = 0;
}