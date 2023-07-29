#include "pch.h"
#include "Field.h"


Field::Field()
{
	
}

Field::~Field()
{
}

void Field::CreateMockedField(std::array<std::vector <int>, 4> mockedPlayingField)
{

	GameCardCreator Creator;
	for( int m = 0; m < 4 ; m++){
		for (const int& number : mockedPlayingField[m]) {

			mPlayingField[m].push_back(Creator.CreateGameCard(number));
		}
	}

}

std::array<std::vector<GameCard>, 4> Field::getPlayingField()
{
	return mPlayingField;
}

void Field::placeCard(int row, GameCard Card)
{
	mPlayingField[row].push_back(Card);
}

int Field::getCostOfRow(int row)
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

