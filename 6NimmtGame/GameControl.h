#pragma once
#include "UI.h"
#include <memory>
#include "Player.h"
#include "HumanPlayer.h"
#include "LowestCardBot.h"
#include "HighestCardBot.h"
#include "RandomBot.h"
#include "Dealer.h"
#include "SmartBot.h"

class GameControl
{
public:

	GameControl();
	~GameControl();

	void startGame();


private:

	int startRound();
	void placeCardLogic(GameCard Card, std::shared_ptr<Player> P);
	std::shared_ptr<Player> initPlayer(std::string number);
	void initField();

	const std::shared_ptr<Dealer> mCardDealer;
	std::shared_ptr<Field> mMatchField;
	const std::shared_ptr<UI> mUI;
	std::shared_ptr<Player> Player1;
	std::shared_ptr<Player> Player2;
	int mCurrentRound;

	friend class TestGameControl_FindingTheCorrectRow_Test;
	friend class BotvBot_SmartvHigh_Test;
	friend class BotvBot_SmartvLow_Test;
	friend class BotvBot_SmartvRand_Test;
};
