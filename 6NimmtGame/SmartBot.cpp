#include "pch.h"
#include "SmartBot.h"
#include "iostream"
SmartBot::SmartBot(bool considerLowestDiff):
	Player(),
	mConsiderLowestDiff(considerLowestDiff)
{
	mName = "SmartBot" + std::to_string(mPlayerCount);
	mIsHumanPlayer = false;
}

SmartBot::~SmartBot()
{
}

GameCard SmartBot::chooseCard(const std::shared_ptr<Field> matchField)
{

	mGoodCardsInHand = mHand;

	removeCardsThatLeadToCost(matchField);

	if (mConsiderLowestDiff) {

		mTempHand = mGoodCardsInHand;

		removeCardsThatWontGoShortestRow(matchField);

	}


	if (!mGoodCardsInHand.empty()) {

		GameCard Card;

		if (mConsiderLowestDiff) {
			Card = CardWithLowestDiff(matchField, mGoodCardsInHand);
		}
		else {
			Card = CardThatGoesShortestRow(matchField, mGoodCardsInHand);
		}
		mHand.erase(std::remove(mHand.begin(), mHand.end(), Card), mHand.end());
		
		return Card;
	}
	else {

		GameCard Card = Lowestcard(mHand);
		mHand.erase(std::remove(mHand.begin(), mHand.end(), Card), mHand.end());
		
		return Card;
	}
}

int SmartBot::chooseRow(const std::shared_ptr<Field> matchField) const
{
	return findCheapestRow(matchField);
}

void SmartBot::removeCardsThatLeadToCost(const std::shared_ptr<Field> matchField)
{
	for (const GameCard& Card : mHand) {

		int row = matchField->findCorrectRow(Card.value);
		if (row == 5) {
			mGoodCardsInHand.erase(std::remove(mGoodCardsInHand.begin(), mGoodCardsInHand.end(), Card),mGoodCardsInHand.end());
		}else if (matchField->getPlayingField()[row].size() == 5) {
			mGoodCardsInHand.erase(std::remove(mGoodCardsInHand.begin(), mGoodCardsInHand.end(), Card),mGoodCardsInHand.end());
		}
	}
}

void SmartBot::removeCardsThatWontGoShortestRow(const std::shared_ptr<Field> matchField)
{
	int shortestRowSizeInHand = findShortestRowSizeInHand(matchField, mGoodCardsInHand);
	int currentRowSize = 0;
	int row = 0;
	
	for (const GameCard& Card : mTempHand) {

		row = matchField->findCorrectRow(Card.value);
		currentRowSize = matchField->getPlayingField()[row].size();
		if (currentRowSize != shortestRowSizeInHand) {
			mGoodCardsInHand.erase(std::remove(mGoodCardsInHand.begin(), mGoodCardsInHand.end(), Card), mGoodCardsInHand.end());
		}
	}
}

GameCard SmartBot::CardWithLowestDiff(const std::shared_ptr<Field> matchField, const std::vector<GameCard>Hand)
{
	int currentDiff = 105;
	int LastCardInRowValue = 0;
	int Diff = 0;
	int row = 0;
	GameCard CurrentGameCard = RandomCard(Hand);

	for (const GameCard& Card : Hand) {
		row = matchField->findCorrectRow(Card.value);

			if (!matchField->getPlayingField()[row].empty()) {
				LastCardInRowValue = matchField->getPlayingField()[row].back().value;
				Diff = Card.value - LastCardInRowValue;

				if (Diff < currentDiff) {
					currentDiff = Diff;
					CurrentGameCard = Card;
				}
			}
	}

	return CurrentGameCard;
}

GameCard SmartBot::CardThatGoesShortestRow(const std::shared_ptr<Field> matchField, const std::vector<GameCard>Hand)
{
	int rowSize = 0;
	int row = 0;
	int currentShortestRowSize = 7;
	GameCard ShortestRowCard = RandomCard(Hand);

	for (const GameCard& Card : Hand) {

		row = matchField->findCorrectRow(Card.value);


			rowSize = matchField->getPlayingField()[row].size();

			if (rowSize < currentShortestRowSize) {
				ShortestRowCard = Card;
				currentShortestRowSize = rowSize;
			}
	}

	return ShortestRowCard;
}

int SmartBot::findShortestRowSizeInHand(const std::shared_ptr<Field> matchField, const std::vector<GameCard> Hand)
{
	int rowSize = 0;
	int row = 0;
	int currentShortestRowSize = 7;

	for (const GameCard& Card : Hand) {

		row = matchField->findCorrectRow(Card.value);

		rowSize = matchField->getPlayingField()[row].size();

		if (rowSize < currentShortestRowSize) {
			currentShortestRowSize = rowSize;
		}
	}

	return currentShortestRowSize;
}

GameCard SmartBot::RandomCard(const std::vector<GameCard>Hand)
{
	std::mt19937 mt1(time(nullptr));
	int randIndex = abs((int)mt1()) % Hand.size();
	return Hand[randIndex];

}

GameCard SmartBot::Lowestcard(const std::vector<GameCard> Hand)
{
	GameCard LowestCard = RandomCard(Hand);

	for (const GameCard& Card : Hand) {
		if (Card < LowestCard) LowestCard = Card;
	}
	return LowestCard;
}

