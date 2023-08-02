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
	int startRound();
	void placeCardLogic(GameCard Card, std::shared_ptr<Player> P);
	int findCorrectRow(int value) const;
	std::shared_ptr<Player> initPlayer(std::string number);
	void initField();


private:

	const std::shared_ptr<Dealer> mCardDealer;
	std::shared_ptr<Field> mMatchField;
	const std::shared_ptr<UI> mUI;
	std::shared_ptr<Player> Player1;
	std::shared_ptr<Player> Player2;
	int mCurrentRound;

	friend class TestGameControl_FindingTheCorrectRow_Test;
};
