#pragma once
#include <string>
#include <memory>
#include "Field.h"
#include "Dealer.h"

class Player
{
public:
	Player(std::shared_ptr<Dealer> CardDealer);
	~Player();

	virtual GameCard chooseCard(std::shared_ptr<Field> matchField) = 0;
	virtual int chooseRow(std::shared_ptr<Field> matchField) const = 0;
	int findCheapestRow(std::shared_ptr<Field> matchField) const;
	void addCost(int cost);
	int getCost() const;
	const std::string getName() const;

	bool mIsHumanPlayer;

protected:
	static int mPlayerCount;
	std::string mName;
	std::vector<GameCard> mHand;
	int mCost;

};

