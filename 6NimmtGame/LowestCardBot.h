#pragma once
#include "Player.h"

class LowestCardBot :
    public Player
{
public: 

    LowestCardBot();
    ~LowestCardBot();

    GameCard chooseCard(const std::shared_ptr<Field> matchField) override;
    int chooseRow(const std::shared_ptr<Field> matchField) const override;

};

