#include "pch.h"
#include "Player.h"

int Player::playerCount = 0;

Player::Player()
{
	playerCount++;
	Dealer CardDealer;
	mHand = CardDealer.Draw(10);
	mCost = 0;
}

Player::~Player()
{
}

