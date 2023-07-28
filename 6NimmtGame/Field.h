#pragma once
#include <array>
#include <vector>
#include "GameCard.h"
#include "GameCardCreator.h"
#include <string>

class Field
{
public:
	Field();
	~Field();

	void CreateMockedField(std::array<std::vector <int>, 4> mockedPlayingField);

private:
	std::array<std::vector <GameCard>,4> mPlayingField;
	friend class UI;
};

