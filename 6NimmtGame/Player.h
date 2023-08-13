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

	void DrawHand(const std::vector<GameCard> Hand);
	void addCost(const int cost);
	void resetCost();

	const std::string getName() const;
	const int findCheapestRow(const std::shared_ptr<Field> matchField) const;
	const int getCost() const;

	virtual const GameCard chooseCard(const std::shared_ptr<Field> matchField) = 0;
	virtual const int chooseRow(const std::shared_ptr<Field> matchField) const = 0;
	
	bool mIsHumanPlayer = 0;

protected:

	std::string mName;
	std::vector<GameCard> mHand;
	static int mPlayerCount;
	int mCost;

	friend class TestLowestCardBot_PlaceCard_Test;
	friend class TestHighestCardBot_PlaceCard_Test;
	friend class TestSmartBot_DeleteBadCards_Test;

};

