#include "pch.h"
#include "LowestCardBot.h"

LowestCardBot::LowestCardBot(std::shared_ptr<Dealer> CardDealer):Player(CardDealer)
{
	mName = "LowestCardBot" + std::to_string(mPlayerCount);
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
	mHand.erase(std::remove(mHand.begin(), mHand.end(), LowestCard));
	return LowestCard;
}

int LowestCardBot::chooseRow(std::shared_ptr<Field> matchField) const
{
	return findCheapestRow(matchField);
}
