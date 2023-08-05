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

    GameCard chooseCard(const std::shared_ptr<Field> matchField) override;
    int chooseRow(const std::shared_ptr<Field> matchField) const override;

private:
    const std::shared_ptr<UI> mUI;

};
