#pragma once
#include "Player.h"
#include "UI.h"
#include <vector>
#include <memory>


class HumanPlayer :
    public Player
{
public:
    HumanPlayer();
    ~HumanPlayer();

    GameCard chooseCard(std::shared_ptr<Field> matchField) override;

};

