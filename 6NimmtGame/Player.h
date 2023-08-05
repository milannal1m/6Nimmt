#pragma once
#include <string>
#include <memory>
#include "Field.h"
#include "Dealer.h"
#include "GameCard.h"

class Player
{
public:
	Player();
	~Player();

	virtual GameCard chooseCard(const std::shared_ptr<Field> matchField) = 0;
	virtual int chooseRow(const std::shared_ptr<Field> matchField) const = 0;
	const int findCheapestRow(const std::shared_ptr<Field> matchField) const;
	void addCost(const int cost);
	void resetCost();
	int getCost() const;
	const std::string getName() const;
	void DrawHand(const std::vector<GameCard> Hand);

	bool mIsHumanPlayer = 0;

protected:
	static int mPlayerCount;
	std::string mName;
	std::vector<GameCard> mHand;
	int mCost;

	friend class TestLowestCardBot_PlaceCard_Test;
	friend class TestHighestCardBot_PlaceCard_Test;
	friend class TestSmartBot_DeleteBadCards_Test;
};

