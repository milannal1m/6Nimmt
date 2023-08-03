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

GameCard LowestCardBot::chooseCard(std::shared_ptr<Field> matchField)
{
	GameCard LowestCard = { 105,105 };
	for (const GameCard& Card : mHand) {
		
		if (Card < LowestCard)LowestCard = Card;
	}
	mHand.erase(std::remove(mHand.begin(), mHand.end(), LowestCard),mHand.end());
	return LowestCard;
}

int LowestCardBot::chooseRow(std::shared_ptr<Field> matchField) const
{
	return findCheapestRow(matchField);
}
