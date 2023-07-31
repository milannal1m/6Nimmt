#include "pch.h"
#include "ShortRowBot.h"

ShortRowBot::ShortRowBot(Dealer CardDealer):Player(CardDealer)
{
	mName = "ShortRowBot" + mPlayerCount;
}

ShortRowBot::~ShortRowBot()
{
}

GameCard ShortRowBot::chooseCard(std::shared_ptr<Field> matchField)
{
	return GameCard();
}

int ShortRowBot::chooseRow(std::shared_ptr<Field> matchField) const
{
	return 0;
}
