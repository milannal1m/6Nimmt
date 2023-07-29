#pragma once
#include <string>
#include <memory>
#include "Field.h"
#include "Dealer.h"

class Player
{
public:
	Player(Dealer RoundDealer);
	~Player();
	virtual GameCard chooseCard(std::shared_ptr<Field> matchField) = 0;
	virtual int chooseRow(std::shared_ptr<Field> matchField) = 0;
	bool mIsHumanPlayer;
	void addCost(int cost);
	int getCost();
	const std::string getName() const;

protected:
	static int playerCount;
	std::string mName;
	std::vector<GameCard> mHand;
	int mCost;

};

