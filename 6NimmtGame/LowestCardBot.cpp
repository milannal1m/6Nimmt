#include "pch.h"
#include "LowestCardBot.h"

LowestCardBot::LowestCardBot():Player()
{
	mName = "LowestCardBot" + std::to_string(mPlayerCount);
	mIsHumanPlayer = false;
}

LowestCardBot::~LowestCardBot()
{
}

const GameCard LowestCardBot::chooseCard(const std::shared_ptr<Field> matchField)
{
	GameCard LowestCard = { 105,105 };

	for (const GameCard& Card : mHand) 
	{
		
		if (Card < LowestCard)LowestCard = Card;
	}

	mHand.erase(std::remove(mHand.begin(), mHand.end(), LowestCard),mHand.end());
	return LowestCard;
}

const int LowestCardBot::chooseRow(const std::shared_ptr<Field> matchField) const
{
	return findCheapestRow(matchField);
}
