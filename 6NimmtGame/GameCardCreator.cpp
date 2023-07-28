#include "pch.h"
#include "GameCardCreator.h"

std::vector<GameCard> GameCardCreator::CreateGameCards() 
{
    std::vector<GameCard> result;
    for (uint8_t i = 1; i <= 104; i++)
    {
        result.push_back(CreateGameCard(i));
    }
    return result;
}

GameCard GameCardCreator::CreateGameCard(uint8_t value)
{
    return { value, CalculateCost(value) };
}

uint8_t GameCardCreator::CalculateCost(uint8_t value)
{
    uint8_t result = 1;
    if (value % 5 == 0)
    {
        result = 2;
    }
    if (value % 10 == 0)
    {
        result = 3;
    }
    if (IsDoubleDigitSchnappsNumber(value))
    {
        result = 5;
    }
    if (value == 55)
    {
        result = 7;
    }
    return result;
}

bool GameCardCreator::IsDoubleDigitSchnappsNumber(uint8_t value)
{
    return value % 11 == 0;
}
