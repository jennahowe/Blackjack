#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "GenericPlayer.h"

class ComputerPlayer: public GenericPlayer
{
public:
	ComputerPlayer();
	ComputerPlayer(std::string name, int maxTotal, float bet);
	const void PrintHand(bool showTotal);	//bool: if ComputerPlayer's hand total should be shown or not

	friend class Game;
	
protected:
	int m_maxTotal;
};

#endif