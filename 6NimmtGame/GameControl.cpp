#include "pch.h" 
#include "GameControl.h"

GameControl::GameControl():
	mUI(std::make_shared<UI>()),
	mCardDealer(std::make_shared<Dealer>()),
	mMatchField(std::make_shared<Field>())
{
	mCurrentRound = 0;

}

GameControl::~GameControl()
{
}

void GameControl::startGame()
{


	mUI->outputMessage("Willkommen bei 6 Nimmt a la Milan!");
	mUI->outputMessage("___________________________");
	mUI->outputMessage("Es gibt folgende Spieler:");
	mUI->outputMessage("___________________________");
	mUI->outputMessage("[1] Menschlicher Spieler");
	mUI->outputMessage("___________________________");
	mUI->outputMessage("[2] Lowest Card Bot");
	mUI->outputMessage("___________________________");
	mUI->outputMessage("[3] Highest Card Bot");
	mUI->outputMessage("___________________________");
	mUI->outputMessage("[4] Random Card Bot");
	mUI->outputMessage("___________________________\n\n");

	Player1 = initPlayer("1");

	Player2 = initPlayer("2");

	int winner = startRound();

	if (winner == 1) {
		std::string message = Player1->getName() + " hat " + std::to_string(Player1->getCost()) + " zu " + std::to_string(Player2->getCost()) + " gewonnen.";
		mUI->outputMessage(message);
	}
	else if (winner == 2) {
		std::string message = Player2->getName() + " hat " + std::to_string(Player2->getCost()) + " zu " + std::to_string(Player1->getCost()) + " gewonnen.";
		mUI->outputMessage(message);
	}
	else {
		mUI->outputMessage("Es ist unentschieden ausgegangen.");
	}
}

int GameControl::startRound()
{
	// returning 1 means Player1 won, returning 2 means Player 2 won, returning 0 means there was a draw

	initField();

	mCurrentRound = 0;

	while (mCurrentRound != 10) {

		mCurrentRound++;

		if(Player1->mIsHumanPlayer || Player2->mIsHumanPlayer){
			mUI->printField(mMatchField->getPlayingField());
		}

		GameCard FirstCard = Player1->chooseCard(mMatchField);
		GameCard SecondCard = Player2->chooseCard(mMatchField);

		if (Player1->mIsHumanPlayer || Player2->mIsHumanPlayer) {
			
			std::string message = Player1->getName() +"(" + std::to_string(Player1->getCost()) + ")" + " waehlt die Karte " + std::to_string(FirstCard.value) + "(" + std::to_string(FirstCard.cost) + ")\n";
			mUI->outputMessage(message);
			message = Player2->getName() +"(" + std::to_string(Player2->getCost()) + ")" + " waehlt die Karte " + std::to_string(SecondCard.value) + "(" + std::to_string(SecondCard.cost) + ")\n";
			mUI->outputMessage(message);
		}
		
		if (FirstCard.value < SecondCard.value) {
			placeCardLogic(FirstCard, Player1);
			placeCardLogic(SecondCard, Player2);
		}
		else {
			placeCardLogic(SecondCard, Player2);
			placeCardLogic(FirstCard, Player1);
		}
	}

	if (Player1->getCost() < Player2->getCost()) {
		return 1;
	}
	else if (Player1->getCost() > Player2->getCost()) {
		return 2;
	}
	else {
		return 0;
	}
}

void GameControl::placeCardLogic(GameCard Card, std::shared_ptr<Player> P)
{
	int row = findCorrectRow(Card.value);
	int cost = 0;

	if (row == 5) {
		row = P->chooseRow(mMatchField);
		cost = mMatchField->getCostOfRow(row);
		mMatchField->resetRow(row, Card);
	}
	else {
		mMatchField->placeCard(row, Card);
		if (mMatchField->isFullRow(row)) {
			cost = mMatchField->getCostOfRow(row)-Card.cost;
			mMatchField->resetRow(row, Card);
		}
	}
	P->addCost(cost);
}

int GameControl::findCorrectRow(int value) const
{
	//returns the row in which the new Card belongs, returns 5 if the card doesnt fit any Row

	int currentRow = 5;
	int currentDiff = 105;

	std::array<std::vector <GameCard>, 4> matchField = mMatchField->getPlayingField();

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


std::shared_ptr<Player> GameControl::initPlayer(std::string number)
{
	std::string mode;
	std::string message;
	message = "Spieler" + number;

	mUI->outputMessage(message);
	mUI->outputMessage("Welchen Modus soll dein Spieler haben?");
	mode = mUI->userInput();

	if (mode == "1") {
		std::shared_ptr<Player> P(new HumanPlayer(mCardDealer));
		return P;

	}
	else if (mode == "2") {
		std::shared_ptr<Player> P(new LowestCardBot(mCardDealer));
		return P;
	}
	else if (mode == "3") {
		std::shared_ptr<Player> P(new HighestCardBot(mCardDealer));
		return P;
	}
	else if (mode == "4") {
		std::shared_ptr<Player> P(new RandomBot(mCardDealer));
		return P;
	}
	else {
		mUI->outputMessage("\nDiesen Modus gibt es nicht, versuchen wir es noch einmal.");
		return initPlayer(number);
	}
}

void GameControl::initField()
{
	mMatchField->clearField();

	std::vector <GameCard> initCards = mCardDealer->Draw(4);

	for (int i = 0; i < 4; i++) {
		mMatchField->placeCard(i, initCards[i]);
	}
}

