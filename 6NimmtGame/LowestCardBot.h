#pragma once
#include "Player.h"

class LowestCardBot :
    public Player
{
public: 

    LowestCardBot(std::shared_ptr<Dealer> CardDealer);
    ~LowestCardBot();

    GameCard chooseCard(std::shared_ptr<Field> matchField) override;
    int chooseRow(std::shared_ptr<Field> matchField) const override;

};

