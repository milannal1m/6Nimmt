#include "pch.h"
#include "SmartBot.h"
#include "iostream"
SmartBot::SmartBot():Player()
{
	mName = "SmartBot" + std::to_string(mPlayerCount);
	mIsHumanPlayer = false;
}

SmartBot::~SmartBot()
{
}

GameCard SmartBot::chooseCard(std::shared_ptr<Field> matchField)
{
	std::mt19937 mt1(time(nullptr));

	mGoodCardsInHand = mHand;

	/*for (const GameCard& Card : mGoodCardsInHand) {

		std::cout << (int) Card.value << " ";

	}
	std::cout << std::endl;*/

	removeCardsThatLeadToCost(matchField);

	if (!mGoodCardsInHand.empty()) {
		int randIndex = abs((int)mt1()) % mGoodCardsInHand.size();

		mHand.erase(std::remove(mHand.begin(), mHand.end(), mGoodCardsInHand[randIndex]), mHand.end());

		return mGoodCardsInHand[randIndex];
	}
	else {
		int randIndex = abs((int)mt1()) % mHand.size();

		GameCard Card = mHand[randIndex];
		mHand.erase(std::remove(mHand.begin(), mHand.end(), mHand[randIndex]), mHand.end());
		
		return Card;
	}
	

}

int SmartBot::chooseRow(std::shared_ptr<Field> matchField) const
{
	return findCheapestRow(matchField);
}

void SmartBot::removeCardsThatLeadToCost(std::shared_ptr<Field> matchField)
{
	for (const GameCard& Card : mGoodCardsInHand) {

		int row = matchField->findCorrectRow(Card.value);
		if (row == 5) {
			mGoodCardsInHand.erase(std::remove(mGoodCardsInHand.begin(), mGoodCardsInHand.end(), Card),mGoodCardsInHand.end());
		}else if (matchField->getPlayingField()[row].size() == 5) {
			mGoodCardsInHand.erase(std::remove(mGoodCardsInHand.begin(), mGoodCardsInHand.end(), Card),mGoodCardsInHand.end());
		}
	}
}
