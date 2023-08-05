#include "pch.h"
#include "UI.h"

UI::UI()
{
}

UI::~UI()
{
}

std::string UI::userInput() const
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

void UI::outputMessage(const std::string message) const
{
	std::cout << message << std::endl;
}

void UI::printField(const std::array<std::vector <GameCard>, 4> PlayingField) const
{

	for (int i = 0; i < 4; i++) {
		for (const GameCard &Card: PlayingField[i]) {
			std::cout << " |  " << (int) Card.value << "(" << (int) Card.cost << ")" << "  | ";
		}
		for (int m = 0; m < 6 - PlayingField[i].size(); m++) {
			std::cout << " |        | ";
		}
		std::cout << std::endl << std::endl;
	}
}

void UI::printHand(const std::vector<GameCard> Hand) const
{
	int i = 0;

	for (const GameCard& n : Hand) {
		i++;
		std::cout << i << ". |" << (int)n.value << "(" << (int)n.cost << ")" << "| ";
	}
	std::cout << std::endl;
}