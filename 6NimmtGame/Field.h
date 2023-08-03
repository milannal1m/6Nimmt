#pragma once
#include <array>
#include <vector>
#include "GameCard.h"
#include "GameCardCreator.h"
#include <string>
#include <memory>
#include "Dealer.h"

class Field
{
public:
	Field();
	~Field();

	void CreateMockedField(std::array<std::vector <int>, 4> mockedPlayingField);
	std::array<std::vector <GameCard>, 4> getPlayingField() const;
	void placeCard(int row, GameCard Card);
	int getCostOfRow(int row) const;
	void resetRow(int row, GameCard NewCard);
	void clearField();
	bool isFullRow(int row);
	int findCorrectRow(int value) const;

private:
	std::array<std::vector <GameCard>,4> mPlayingField;
};

