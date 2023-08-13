#pragma once
#include "Player.h"

class HighestCardBot :
    public Player
{

public:

    HighestCardBot();
    ~HighestCardBot();

    const GameCard chooseCard(const std::shared_ptr<Field> matchField) override;
    const int chooseRow(const std::shared_ptr<Field> matchField) const override;

};

