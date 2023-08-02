#include "pch.h"
#include "HighestCardBot.h"

HighestCardBot::HighestCardBot(std::shared_ptr<Dealer> CardDealer):Player(CardDealer)
{
	mName = "HighestCardBot" + std::to_string(mPlayerCount);
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
	mHand.erase(std::remove(mHand.begin(), mHand.end(), HighestCard));
	return HighestCard;
}

int HighestCardBot::chooseRow(std::shared_ptr<Field> matchField) const
{
	return findCheapestRow(matchField);
}
