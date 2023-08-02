#pragma once
#include "Player.h"
#include "UI.h"
#include <vector>
#include <memory>


class HumanPlayer :
    public Player
{
public:
    HumanPlayer(std::shared_ptr<Dealer> CardDealer);
    ~HumanPlayer();

    GameCard chooseCard(std::shared_ptr<Field> matchField) override;
    int chooseRow(std::shared_ptr<Field> matchField) const override;

private:
    const std::shared_ptr<UI> mUI;

};
