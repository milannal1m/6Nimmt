#include "pch.h"
#include "GameControl.h"

GameControl::GameControl()
{
	mCurrentRound = 0;
}

GameControl::~GameControl()
{
}

void GameControl::startGame()
{
	UI nUI;

	nUI.outputMessage("Willkommen bei 6 Nimmt a la Milan!");
	nUI.outputMessage("___________________________");
	nUI.outputMessage("Es gibt folgende Spieler:");
	nUI.outputMessage("___________________________");
	nUI.outputMessage("[1] Menschlicher Spieler");
	nUI.outputMessage("___________________________");
	nUI.outputMessage("[2] Short Row Bot");
	nUI.outputMessage("___________________________\n\n");

	std::shared_ptr<Player> P1 = initPlayer("1");

	std::shared_ptr<Player> P2 = initPlayer("2");

	int winner = startRound(P1, P2);

	if (winner == 1) {
		nUI.outputMessage("Spieler 1 hat gewonnen.");
	}
	else if (winner == 2) {
		nUI.outputMessage("Spieler 2 hat gewonnen.");
	}
	else {
		nUI.outputMessage("Unentschieden");
	}
}

int GameControl::startRound(std::shared_ptr<Player> P1, std::shared_ptr<Player> P2)
{
	// returning 1 means Player1 won, returning 2 means Player 2 won, returning 0 means there was a draw
	mCurrentRound = 0;
	std::shared_ptr<Field> matchField(new Field);
	UI nUI;

	while (mCurrentRound != 10) {

		mCurrentRound++;

		if(P1->mIsHumanPlayer || P2->mIsHumanPlayer){
			nUI.printField(matchField);
		}

		GameCard FirstCard = P1->chooseCard(matchField);
		GameCard SecondCard = P2->chooseCard(matchField);

		if (P1->mIsHumanPlayer || P2->mIsHumanPlayer) {
			
			std::string message = P1->getName() + " waehlt die Karte " + std::to_string(FirstCard.value) + "(" + std::to_string(FirstCard.cost) + ")\n";
			nUI.outputMessage(message);
			message = P2->getName() + " waehlt die Karte " + std::to_string(SecondCard.value) + "(" + std::to_string(SecondCard.cost) + ")\n";
			nUI.outputMessage(message);
		}
		
		if (FirstCard.value < SecondCard.value) {
			placeCardLogic(FirstCard, matchField, P1);
			placeCardLogic(SecondCard, matchField, P2);
		}
		else {
			placeCardLogic(SecondCard, matchField, P2);
			placeCardLogic(FirstCard, matchField, P1);
		}
	}

	if (P1->getCost() < P2->getCost()) {
		return 1;
	}
	else if (P1->getCost() > P2->getCost()) {
		return 2;
	}
	else {
		return 0;
	}
}

void GameControl::placeCardLogic(GameCard Card, std::shared_ptr<Field> matchField, std::shared_ptr<Player> P)
{
	int row = findCorrectRow(Card.value, matchField->getPlayingField());
	int cost = 0;

	if (row == 5) {
		row = P->chooseRow(matchField);
		cost = matchField->getCostOfRow(row);
		matchField->resetRow(row, Card);
	}
	else {
		matchField->placeCard(row, Card);
		if (isFullRow(row, matchField->getPlayingField())) {
			cost = matchField->getCostOfRow(row);
			matchField->resetRow(row, Card);
		}
	}
	P->addCost(cost);
}

int GameControl::findCorrectRow(int value, std::array<std::vector <GameCard>, 4> matchField)
{
	//returns the row in which the new Card belongs, returns 5 if the card doesnt fit any Row

	int currentRow = 5;
	int currentDiff = 105;

	for (int i = 0; i < 4; i++) {
		if (matchField[i].size() == 0) {

			if (i < currentRow) currentRow = i;

		}
		else if (matchField[i].back().value < value && value - matchField[i].back().value < currentDiff) {

			currentDiff = value - matchField[i].back().value;
			currentRow = i;
		}
	}
	return currentRow;
}

bool GameControl::isFullRow(int row, std::array<std::vector<GameCard>, 4> matchField)
{

		if (matchField[row].size() == 6) {

			return true;

		}
		else {
			return false;
		}
}


std::shared_ptr<Player> GameControl::initPlayer(std::string number)
{
	UI nUI;
	Dealer CardDealer;
	std::string mode;
	std::string message;
	message = "Spieler" + number;

	nUI.outputMessage(message);
	nUI.outputMessage("Welchen Modus soll dein Spieler haben?");
	mode = nUI.userInput();

	if (mode == "1") {
		std::shared_ptr<Player> P(new HumanPlayer(CardDealer));
		return P;

	}
	else if (mode == "2") {
		std::shared_ptr<Player> P(new ShortRowBot(CardDealer));
		return P;
	}
	else {
		nUI.outputMessage("\nDiesen Modus gibt es nicht, versuchen wir es noch einmal.");
		return initPlayer(number);
	}
}
