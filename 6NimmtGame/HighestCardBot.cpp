#include "pch.h"
#include "HighestCardBot.h"

HighestCardBot::HighestCardBot():Player()
{
	mName = "HighestCardBot" + std::to_string(mPlayerCount);
	mIsHumanPlayer = false;
}

HighestCardBot::~HighestCardBot()
{
}

GameCard HighestCardBot::chooseCard(std::shared_ptr<Field> matchField)
{
	GameCard HighestCard = { 0,0 };
	for (const GameCard& Card : mHand) {

		if (HighestCard < Card)HighestCard = Card;
	}
	mHand.erase(std::remove(mHand.begin(), mHand.end(), HighestCard),mHand.end());
	return HighestCard;
}

int HighestCardBot::chooseRow(std::shared_ptr<Field> matchField) const
{
	return findCheapestRow(matchField);
}
