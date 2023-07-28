#pragma once
#include <cstdint>
struct GameCard
{
	bool operator<(const GameCard& other) const;
	uint8_t value;
	uint8_t cost;
};

