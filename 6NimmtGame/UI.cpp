#include "pch.h"
#include "UI.h"

UI::UI()
{
}

UI::~UI()
{
}

std::string UI::userInput()
{

	std::string output;
	std::cin >> output;
	if (std::cin.fail())
	{ 
		std::cin.clear(); 
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return output;

}

void UI::outputMessage(std::string message)
{
	std::cout << message << std::endl;
}

void UI::printField(std::shared_ptr<Field> PlayingField)
{

	for (int i = 0; i < 4; i++) {
		for (const GameCard &Card: PlayingField->mPlayingField[i]) {
			std::cout << " |  " << (int) Card.value << "(" << (int) Card.cost << ")" << "  | ";
		}
		for (int m = 0; m < 6 - PlayingField->mPlayingField[i].size(); m++) {
			std::cout << " |        | ";
		}
		std::cout << std::endl << std::endl;
	}
}

void UI::printHand(std::vector<GameCard> mHand)
{
	int i = 0;

	for (const GameCard& n : mHand) {
		i++;
		std::cout << i << ". |" << (int)n.value << "(" << (int)n.cost << ")" << "| ";
	}
	std::cout << std::endl;
}