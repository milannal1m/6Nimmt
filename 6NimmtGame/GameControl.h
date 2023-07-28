#pragma once
#include "UI.h"
#include <memory>
#include "Player.h"
#include "HumanPlayer.h"

class GameControl
{
public:

	GameControl();
	~GameControl();

	void startgame();
	int startRound(std::shared_ptr<Player> P1, std::shared_ptr<Player> P2);
	std::shared_ptr<Player> initPlayer(std::string number);

private:

	int mCurrentRound;

};

