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

	void CreateMockedField(const std::array<std::vector <int>, 4> mockedPlayingField);
	void placeCard(const int row, const  GameCard Card);
	void resetRow(const int row, const GameCard NewCard);
	void clearField();

	const std::array<std::vector <GameCard>, 4> getPlayingField() const;
	const int getCostOfRow(const int row) const;
	const bool isFullRow(const int row) const;
	const int findCorrectRow(const int value) const;

private:

	std::array<std::vector <GameCard>,4> mPlayingField;

};

