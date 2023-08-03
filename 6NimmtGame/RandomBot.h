#pragma once
#include "Player.h"
#include <random>
#include <ctime>

class RandomBot :
    public Player
{
public:
    RandomBot();
    ~RandomBot();

    GameCard chooseCard(std::shared_ptr<Field> matchField) override;
    int chooseRow(std::shared_ptr<Field> matchField) const override;
};

