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

    const GameCard chooseCard(const std::shared_ptr<Field> matchField) override;
    const int chooseRow(const std::shared_ptr<Field> matchField) const override;

    void removeCardsThatLeadToCost(const std::shared_ptr<Field> matchField);
    void removeCardsThatWontGoShortestRow(const std::shared_ptr<Field> matchField);

    const GameCard CardWithLowestDiff(const std::shared_ptr<Field> matchField, const std::vector<GameCard>Hand);
    const GameCard CardThatGoesShortestRow(const std::shared_ptr<Field> matchField, const std::vector<GameCard>Hand);
    const GameCard RandomCard(const std::vector<GameCard>Hand);
    const GameCard Lowestcard(const std::vector<GameCard>Hand);
    const int findShortestRowSizeInHand(const std::shared_ptr<Field> matchField, const std::vector<GameCard>Hand);

private:

    std::vector<GameCard> mGoodCardsInHand;
    std::vector<GameCard> mTempHand;
    const bool mConsiderLowestDiff;

    friend class TestSmartBot_DeleteBadCards_Test;
    friend class TestSmartBot_DeleteCardsThatWontGoShortestRow_Test;
    friend class TestSmartBot_findShortestRowSizeInHand_Test;
};

