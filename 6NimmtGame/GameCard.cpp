#include "pch.h"
#include "GameCard.h"

bool GameCard::operator<(const GameCard& other) const
{
	return value < other.value;
}
