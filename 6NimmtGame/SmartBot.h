#pragma once
#include "Player.h"
#include <random>
#include <ctime>

class SmartBot :
    public Player
{
public:
    SmartBot();
    ~SmartBot();

    GameCard chooseCard(std::shared_ptr<Field> matchField) override;
    int chooseRow(std::shared_ptr<Field> matchField) const override;
    void removeCardsThatLeadToCost(std::shared_ptr<Field> matchField);


private:
    std::vector<GameCard> mGoodCardsInHand;
};

