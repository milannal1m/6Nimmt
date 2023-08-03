#include "pch.h"
#include "Dealer.h"
#include "GameCardCreator.h"
#include <cassert>
#include <algorithm>
#include <random>

Dealer::Dealer()
{
    Reset();
}

void Dealer::Reset()
{
    mGameCards = GameCardCreator::CreateGameCards();
    ShuffleCards();
}

std::vector<GameCard> Dealer::Draw(int numberOfCards)
{
    if (AreEnoughCardsRemaining(numberOfCards))
    {
        return ExecuteDraw(numberOfCards);
    }
    else {
        Reset();
        return Draw(numberOfCards);
    }
}


void Dealer::ShuffleCards()
{
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(mGameCards.begin(), mGameCards.end(), g);
}

std::vector<GameCard> Dealer::ExecuteDraw(int numberOfCards)
{
    std::vector<GameCard> result;
    for (int i = 0; i < numberOfCards; i++)
    {
        result.push_back(mGameCards.back());
        mGameCards.pop_back();
    }
    return result;
}

bool Dealer::AreEnoughCardsRemaining(int numberOfCards) const
{
    return numberOfCards > 0 && numberOfCards <= mGameCards.size();
}
