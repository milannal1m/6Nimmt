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

void GameControl::startHumanControlledGame()
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
	mUI->outputMessage("___________________________");
	mUI->outputMessage("[5] Smart Bot");
	mUI->outputMessage("___________________________");
	mUI->outputMessage("[6] Smart Bot(achtet auf Differenz)");
	mUI->outputMessage("___________________________\n\n");

	mPlayer1 = initPlayer("1");

	mPlayer2 = initPlayer("2");

	int winner = startGame();

	if (winner == 1) 
	{
		std::string message = mPlayer1->getName() + " hat " + std::to_string(mPlayer1->getCost()) + " zu " + std::to_string(mPlayer2->getCost()) + " gewonnen.";
		mUI->outputMessage(message);
	}
	else if (winner == 2) 
	{
		std::string message = mPlayer2->getName() + " hat " + std::to_string(mPlayer2->getCost()) + " zu " + std::to_string(mPlayer1->getCost()) + " gewonnen.";
		mUI->outputMessage(message);
	}
	else 
	{
		mUI->outputMessage("Es ist unentschieden ausgegangen.");
	}
}

const int GameControl::startGame()
{
	// returning 1 means Player1 won, returning 2 means Player 2 won, returning 0 means it was a draw

	initField();

	mPlayer1->resetCost();
	mPlayer2->resetCost();

	mPlayer1->DrawHand(mCardDealer->Draw(10));
	mPlayer2->DrawHand(mCardDealer->Draw(10));

	mCurrentRound = 0;
	
	while (mCurrentRound != 10) 
	{
		mCurrentRound++;

		if(mPlayer1->mIsHumanPlayer || mPlayer2->mIsHumanPlayer)
		{
			mUI->printField(mMatchField->getPlayingField());
		}

		GameCard FirstCard = mPlayer1->chooseCard(mMatchField);
		GameCard SecondCard = mPlayer2->chooseCard(mMatchField);

		if (mPlayer1->mIsHumanPlayer || mPlayer2->mIsHumanPlayer) 
		{
			std::string message = mPlayer1->getName() +"(" + std::to_string(mPlayer1->getCost()) + ")" + " waehlt die Karte " + std::to_string(FirstCard.value) + "(" + std::to_string(FirstCard.cost) + ")\n";
			mUI->outputMessage(message);
			message = mPlayer2->getName() +"(" + std::to_string(mPlayer2->getCost()) + ")" + " waehlt die Karte " + std::to_string(SecondCard.value) + "(" + std::to_string(SecondCard.cost) + ")\n";
			mUI->outputMessage(message);
		}
		
		if (FirstCard.value < SecondCard.value) 
		{
			takeTurn(FirstCard, mPlayer1);
			takeTurn(SecondCard, mPlayer2);
		}
		else 
		{
			takeTurn(SecondCard, mPlayer2);
			takeTurn(FirstCard, mPlayer1);
		}
	}

	if (mPlayer1->getCost() < mPlayer2->getCost()) 
	{
		return 1;
	}
	else if (mPlayer1->getCost() > mPlayer2->getCost()) 
	{
		return 2;
	}
	else 
	{
		return 0;
	}
}

void GameControl::takeTurn(const GameCard Card, const std::shared_ptr<Player> P) const
{
	int row = mMatchField->findCorrectRow(Card.value);
	int cost = 0;

	if (row == 5) 
	{
		row = P->chooseRow(mMatchField);
		cost = mMatchField->getCostOfRow(row);
		mMatchField->resetRow(row, Card);
	}
	else 
	{
		mMatchField->placeCard(row, Card);

		if (mMatchField->isFullRow(row)) 
		{
			cost = mMatchField->getCostOfRow(row) - Card.cost;
			mMatchField->resetRow(row, Card);
		}
	}

	P->addCost(cost);
}

const std::shared_ptr<Player> GameControl::initPlayer(const std::string number)
{
	std::string mode;
	std::string message;
	message = "Spieler" + number;

	mUI->outputMessage(message);
	mUI->outputMessage("Welchen Modus soll dein Spieler haben?");
	mode = mUI->userInput();

	if (mode == "1") 
	{
		return std::make_shared<HumanPlayer>();
	}
	else if (mode == "2") 
	{
		return std::make_shared<LowestCardBot>();
	}
	else if (mode == "3") 
	{
		return std::make_shared<HighestCardBot>();
	}
	else if (mode == "4") 
	{
		return std::make_shared<RandomBot>();
	}
	else if (mode == "5") 
	{
		return std::make_shared<SmartBot>(false);
	}
	else if (mode == "6") 
	{
		return std::make_shared<SmartBot>(true);
	}
	else 
	{
		mUI->outputMessage("\nDiesen Modus gibt es nicht, versuchen wir es noch einmal.");
		return initPlayer(number);
	}
}

void GameControl::initField()
{
	mMatchField->clearField();

	std::vector <GameCard> initCards = mCardDealer->Draw(4);

	for (int i = 0; i < 4; i++) 
	{
		mMatchField->placeCard(i, initCards[i]);
	}
}

