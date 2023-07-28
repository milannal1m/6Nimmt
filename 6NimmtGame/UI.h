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

	std::string userInput();
	void outputMessage(std::string message);
	void printField(std::shared_ptr<Field> PlayingField);
	void printHand(std::vector<GameCard> mHand);

};

