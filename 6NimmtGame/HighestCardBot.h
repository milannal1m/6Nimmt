#pragma once
#include "Player.h"
class HighestCardBot :
    public Player
{
public:

    HighestCardBot();
    ~HighestCardBot();

    GameCard chooseCard(std::shared_ptr<Field> matchField) override;
    int chooseRow(std::shared_ptr<Field> matchField) const override;
};

