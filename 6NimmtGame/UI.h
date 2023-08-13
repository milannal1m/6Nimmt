#pragma once
#include <string>
#include <iostream>
#include "Field.h"
#include "GameCard.h"
#include "Player.h"

class UI
{

public:

	UI();
	~UI();

	const std::string userInput() const;
	void outputMessage(const std::string message) const;
	void printField(const std::array<std::vector <GameCard>, 4> PlayingField) const;
	void printHand(const std::vector<GameCard> mHand) const;

};

