#pragma once
#include "Player.h"
class HighestCardBot :
    public Player
{
public:

    HighestCardBot();
    ~HighestCardBot();

    GameCard chooseCard(const std::shared_ptr<Field> matchField) override;
    int chooseRow(const std::shared_ptr<Field> matchField) const override;
};

