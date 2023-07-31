#include "pch.h"
#include "LowestCardBot.h"

LowestCardBot::LowestCardBot(Dealer CardDealer):Player(CardDealer)
{
	mName = "ShortRowBot" + mPlayerCount;
}

LowestCardBot::~LowestCardBot()
{
}

GameCard LowestCardBot::chooseCard(std::shared_ptr<Field> matchField)
{
	return GameCard();
}

int LowestCardBot::chooseRow(std::shared_ptr<Field> matchField) const
{
	return 0;
}
