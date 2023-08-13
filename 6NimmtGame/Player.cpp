#include "pch.h"
#include "Player.h"

int Player::mPlayerCount = 0;

Player::Player()
{
	mPlayerCount++;
	mCost = 0;
}

Player::~Player()
{
	mHand.clear();
}

const int Player::findCheapestRow(const std::shared_ptr<Field> matchField) const
{
	int lowestCostRow = 5;
	int currentCost = 500;

	for (int i = 0; i < 4; i++) 
	{
		int cost = matchField->getCostOfRow(i);

		if (cost < currentCost) 
		{
			lowestCostRow = i;
			currentCost = cost;
		}
	}

	return lowestCostRow;
}

void Player::addCost(const int cost)
{
	mCost += cost;
}

void Player::resetCost()
{
	mCost = 0;
}

const int Player::getCost() const
{
	return mCost;
}

const std::string Player::getName() const
{
	return mName;
}

void Player::DrawHand(const std::vector<GameCard> Hand)
{
	mHand.clear();
	mHand = Hand;
}

