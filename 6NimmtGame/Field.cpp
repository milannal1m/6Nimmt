#include "pch.h"
#include "Field.h"


Field::Field()
{

}

Field::~Field()
{
	clearField();
}

void Field::CreateMockedField(std::array<std::vector <int>, 4> mockedPlayingField)
{

	GameCardCreator Creator;

	for (int i = 0; i < 4; i++) {
		mPlayingField[i].clear();
	}

	for( int m = 0; m < 4 ; m++){
		for (const int& number : mockedPlayingField[m]) {

			mPlayingField[m].push_back(Creator.CreateGameCard(number));
		}
	}

}

std::array<std::vector<GameCard>, 4> Field::getPlayingField() const
{
	return mPlayingField;
}

void Field::placeCard(int row, GameCard Card)
{
	mPlayingField[row].push_back(Card);
}

int Field::getCostOfRow(int row) const
{
	int cost = 0;

	for (const GameCard& Card : mPlayingField[row]) {
		cost += Card.cost;
	}

	return cost;
}

void Field::resetRow(int row, GameCard NewCard)
{
	mPlayingField[row].clear();
	mPlayingField[row].push_back(NewCard);
}

void Field::clearField()
{
	for (int i = 0; i < 4; i++) {
		mPlayingField[i].clear();
	}
}

bool Field::isFullRow(int row)
{
	if (mPlayingField[row].size() == 6) {

		return true;

	}
	else {
		return false;
	}
}

int Field::findCorrectRow(int value) const
{
	//returns the row in which the new Card belongs, returns 5 if the card doesnt fit any Row

	int currentRow = 5;
	int currentDiff = 105;

	for (int i = 0; i < 4; i++) {
		if (mPlayingField[i].size() == 0) {

			if (i < currentRow) currentRow = i;

		}
		else if (mPlayingField[i].back().value < value && value - mPlayingField[i].back().value < currentDiff) {

			currentDiff = value - mPlayingField[i].back().value;
			currentRow = i;
		}
	}
	return currentRow;
}
