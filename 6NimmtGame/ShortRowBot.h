#pragma once
#include "Player.h"

class ShortRowBot :
    public Player
{
public: 

    ShortRowBot(Dealer CardDealer);
    ~ShortRowBot();

    GameCard chooseCard(std::shared_ptr<Field> matchField) override;
    int chooseRow(std::shared_ptr<Field> matchField) const override;

};

