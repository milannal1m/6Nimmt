//Milan Tóth 7348917

#include "HumanPlayer.h"
#include "Field.h"
#include "UI.h"
#include <string>

int main() {

	UI nUI;
	std::shared_ptr<Field> matchField(new Field);
	HumanPlayer Player;

	GameCard Card = Player.chooseCard(matchField);
	
	nUI.outputMessage(std::to_string( Card.value));

	Card = Player.chooseCard(matchField);
}