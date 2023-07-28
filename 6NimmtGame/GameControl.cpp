#include "pch.h"
#include "GameControl.h"

GameControl::GameControl()
{
	mCurrentRound = 0;
}

GameControl::~GameControl()
{
}

void GameControl::startgame()
{
	UI nUI;

	nUI.outputMessage("Willkommen bei 6 Nimmt a la Milan!");
	nUI.outputMessage("___________________________");
	nUI.outputMessage("Es gibt folgende Spieler:");
	nUI.outputMessage("___________________________");
	nUI.outputMessage("[1] Menschlicher Spieler");
	nUI.outputMessage("___________________________");

	std::shared_ptr<Player> P1 = initPlayer("1");

	std::shared_ptr<Player> P2 = initPlayer("");

	startRound(P1, P2);
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


	}
	return 0;
}

std::shared_ptr<Player> GameControl::initPlayer(std::string number)
{
	UI nUI;
	std::string mode;
	std::string message;
	message = "Spieler" + number;

	nUI.outputMessage(message);
	nUI.outputMessage("Welchen Modus soll dein Spieler haben?");
	mode = nUI.userInput();

	if (mode == "1") {
		std::shared_ptr<Player> P(new HumanPlayer);
		return P;
	}
	else {
		nUI.outputMessage("Diesen Spieler gibt es nicht, versuchen wir es noch einmal.");
		return initPlayer(number);
	}
}
