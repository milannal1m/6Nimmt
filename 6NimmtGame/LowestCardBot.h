#pragma once
#include "Player.h"

class LowestCardBot :
    public Player
{

public: 

    LowestCardBot();
    ~LowestCardBot();

    const GameCard chooseCard(const std::shared_ptr<Field> matchField) override;
    const int chooseRow(const std::shared_ptr<Field> matchField) const override;

};

