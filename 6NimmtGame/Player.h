#pragma once
#include <string>
#include <memory>
#include "Field.h"
#include "Dealer.h"

class Player
{
public:
	Player();
	~Player();
	virtual GameCard chooseCard(std::shared_ptr<Field> matchField) = 0;
	bool mIsHumanPlayer;

protected:
	static int playerCount;
	std::string mName;
	std::vector<GameCard> mHand;
	int mCost;

};

