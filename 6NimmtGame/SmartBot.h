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
    void removeCardsThatWontGoShortestRow(std::shared_ptr<Field> matchField);
    GameCard CardWithLowestDiff(std::shared_ptr<Field> matchField);
    GameCard CardThatGoesShortestRow(std::shared_ptr<Field> matchField);
    int findShortestRowSizeInHand(std::shared_ptr<Field> matchField, std::vector<GameCard>Hand);
    GameCard RandomCard(std::vector<GameCard>Hand);
    GameCard LowestCard(std::vector<GameCard>Hand);


private:
    std::vector<GameCard> mGoodCardsInHand;
    std::vector<GameCard> mTempCards;

    friend class TestSmartBot_DeleteBadCards_Test;
};

