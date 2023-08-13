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

	void startHumanControlledGame();


private:

	void takeTurn(const GameCard Card, const std::shared_ptr<Player> P) const;
	void initField();
	
	const int startGame();
	const std::shared_ptr<Player> initPlayer(const std::string number);
	

	const std::shared_ptr<Dealer> mCardDealer;
	const std::shared_ptr<Field> mMatchField;
	const std::shared_ptr<UI> mUI;
	std::shared_ptr<Player> mPlayer1;
	std::shared_ptr<Player> mPlayer2;
	int mCurrentRound;


	friend class TestGameControl_FindingTheCorrectRow_Test;
	friend class BotvBot_SmartvHigh_Test;
	friend class BotvBot_SmartvLow_Test;
	friend class BotvBot_SmartvRand_Test;
	friend class BotvBot_SmartvSmartDiff_Test;

};
