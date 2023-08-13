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

    const GameCard chooseCard(const std::shared_ptr<Field> matchField) override;
    const int chooseRow(const std::shared_ptr<Field> matchField) const override;

};

