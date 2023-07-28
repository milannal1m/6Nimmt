#pragma once
#include "GameCard.h"
#include <vector>

class GameCardCreator
{
public:
	static std::vector<GameCard> CreateGameCards();
	static GameCard CreateGameCard(uint8_t value);
private:
	static uint8_t CalculateCost(uint8_t value);
	static bool IsDoubleDigitSchnappsNumber(uint8_t value);
};

