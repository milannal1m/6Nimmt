#include "pch.h"
#include "Player.h"

int Player::playerCount = 0;

Player::Player(Dealer CardDealer)
{
	playerCount++;
	mHand = CardDealer.Draw(10);
	mCost = 0;
}

Player::~Player()
{
}

void Player::addCost(int cost)
{
	mCost += cost;
}

int Player::getCost()
{
	return mCost;
}

