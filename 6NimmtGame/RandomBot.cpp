#include "pch.h"
#include "RandomBot.h"


RandomBot::RandomBot():Player()
{
	mName = "RandomBot" + std::to_string(mPlayerCount);
	mIsHumanPlayer = false;
}

RandomBot::~RandomBot()
{
}

GameCard RandomBot::chooseCard(std::shared_ptr<Field> matchField)
{
	std::mt19937 mt1(time(nullptr));

	int randIndex = abs((int)mt1()) % mHand.size();

	GameCard RandCard = mHand[randIndex];
	mHand.erase(mHand.begin() + randIndex);

	return RandCard;
}

int RandomBot::chooseRow(std::shared_ptr<Field> matchField) const
{
	return findCheapestRow(matchField);
}
