#pragma once
#include "UI.h"
#include <memory>
#include "Player.h"
#include "HumanPlayer.h"
#include "LowestCardBot.h"
#include "Dealer.h"

class GameControl
{
public:

	GameControl();
	~GameControl();

	void startGame();
	int startRound(std::shared_ptr<Player> P1, std::shared_ptr<Player> P2);
	void placeCardLogic(GameCard Card, std::shared_ptr<Field> matchField, std::shared_ptr<Player> P);
	int findCorrectRow(int value, std::array<std::vector <GameCard>, 4> matchField);
	bool isFullRow(int row, std::array<std::vector <GameCard>, 4> matchField);
	std::shared_ptr<Player> initPlayer(std::string number);


private:

	int mCurrentRound;

};
