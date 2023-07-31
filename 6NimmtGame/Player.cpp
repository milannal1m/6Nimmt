#include "pch.h"
#include "Player.h"

int Player::mPlayerCount = 0;

Player::Player(Dealer CardDealer)
{
	mPlayerCount++;
	mHand = CardDealer.Draw(10);
	mCost = 0;
}

Player::~Player()
{
}

int Player::findCheapestRow(std::shared_ptr<Field> matchField) const
{
	int lowestCostRow = 5;
	int currentCost = 500;

	for (int i = 0; i < 4; i++) {
		int cost = matchField->getCostOfRow(i);
		if (cost < currentCost) {

			lowestCostRow = i;
			currentCost = cost;
		}
	}

	return lowestCostRow;
}

void Player::addCost(int cost)
{
	mCost += cost;
}

int Player::getCost() const
{
	return mCost;
}

const std::string Player::getName() const
{
	return mName;
}

