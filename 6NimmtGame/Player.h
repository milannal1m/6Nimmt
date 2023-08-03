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

	virtual GameCard chooseCard(std::shared_ptr<Field> matchField) = 0;
	virtual int chooseRow(std::shared_ptr<Field> matchField) const = 0;
	int findCheapestRow(std::shared_ptr<Field> matchField) const;
	void addCost(int cost);
	int getCost() const;
	const std::string getName() const;
	void createMockedHand(std::vector<GameCard> Hand);

	bool mIsHumanPlayer = 0;

protected:
	static int mPlayerCount;
	std::string mName;
	std::vector<GameCard> mHand;
	int mCost;

	friend class LowestCardBot_PlaceCard_Test;
	friend class HighestCardBot_PlaceCard_Test;
	friend class TestSmartBot_DeleteBadCards_Test;
};

