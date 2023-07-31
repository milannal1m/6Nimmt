#pragma once
#include "Player.h"

class LowestCardBot :
    public Player
{
public: 

    LowestCardBot(Dealer CardDealer);
    ~LowestCardBot();

    GameCard chooseCard(std::shared_ptr<Field> matchField) override;
    int chooseRow(std::shared_ptr<Field> matchField) const override;

};

