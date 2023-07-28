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
