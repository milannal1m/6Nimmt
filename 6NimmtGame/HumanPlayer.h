#pragma once
#include "Player.h"
#include "UI.h"
#include <vector>
#include <memory>
#include "Dealer.h"


class HumanPlayer :
    public Player
{
public:
    HumanPlayer(Dealer CardDealer);
    ~HumanPlayer();

    GameCard chooseCard(std::shared_ptr<Field> matchField) override;
    int chooseRow(std::shared_ptr<Field> matchField) override;

};
