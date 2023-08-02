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

	std::string userInput() const;
	void outputMessage(std::string message) const;
	void printField(std::array<std::vector <GameCard>, 4> PlayingField) const;
	void printHand(std::vector<GameCard> mHand) const;

};

