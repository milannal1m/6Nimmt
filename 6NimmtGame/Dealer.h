#pragma once
#include "GameCard.h"
#include <vector>

class Dealer
{

public:

	Dealer();
	void Reset();

	std::vector<GameCard> Draw(int numberOfCards);

private:

	void ShuffleCards();
	std::vector<GameCard> ExecuteDraw(int numberOfCards);
	bool AreEnoughCardsRemaining(int numberOfCards) const;
	std::vector<GameCard> mGameCards;

};

