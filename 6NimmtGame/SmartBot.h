#pragma once
#include "Player.h"
#include <random>
#include <ctime>

class SmartBot :
    public Player
{
public:
    SmartBot(bool considerLowestDiff);
    ~SmartBot();

    GameCard chooseCard(const std::shared_ptr<Field> matchField) override;
    int chooseRow(const std::shared_ptr<Field> matchField) const override;
    void removeCardsThatLeadToCost(const std::shared_ptr<Field> matchField);
    void removeCardsThatWontGoShortestRow(const std::shared_ptr<Field> matchField);
    GameCard CardWithLowestDiff(const std::shared_ptr<Field> matchField, const std::vector<GameCard>Hand);
    GameCard CardThatGoesShortestRow(const std::shared_ptr<Field> matchField, const std::vector<GameCard>Hand);
    int findShortestRowSizeInHand(const std::shared_ptr<Field> matchField, const std::vector<GameCard>Hand);
    GameCard RandomCard(const std::vector<GameCard>Hand);
    GameCard Lowestcard(const std::vector<GameCard>Hand);


private:
    std::vector<GameCard> mGoodCardsInHand;
    std::vector<GameCard> mTempHand;
    const bool mConsiderLowestDiff;

    friend class TestSmartBot_DeleteBadCards_Test;
};

