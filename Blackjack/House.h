#ifndef HOUSE_H
#define HOUSE_H

#include "ComputerPlayer.h"

class House: public ComputerPlayer
{
public:
	House();
	void SetBustTotal();

	friend class Game;
};

#endif