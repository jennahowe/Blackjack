#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "GenericPlayer.h"

class HumanPlayer: public GenericPlayer
{
public:
	HumanPlayer();
	HumanPlayer(int playerNumber);
	void SetName();

	friend class Game;

protected:
	int m_playerNumber;
	bool m_dropOut;
};
#endif