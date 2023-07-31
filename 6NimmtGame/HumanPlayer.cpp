#include "pch.h"
#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(Dealer CardDealer):Player(CardDealer)
{
    UI nUI;

    nUI.outputMessage("\nWie lautet dein Name?");
    mName = nUI.userInput();
    nUI.outputMessage("\n");
    mIsHumanPlayer = true;
}

HumanPlayer::~HumanPlayer()
{
}

GameCard HumanPlayer::chooseCard(std::shared_ptr<Field> matchField)
{
    UI nUI;
    
    nUI.outputMessage("\nDein Deck:");
    nUI.printHand(mHand);
    std::string message = mName + "(" + std::to_string(mCost) + ")" + ", waehle eine Karte aus.";
    nUI.outputMessage(message);

    std::string input = nUI.userInput();
    nUI.outputMessage("");

    if (isdigit(input[0])) {
        int cardIndex = stoi(input)-1;
        if (cardIndex <= mHand.size()) {
            GameCard chosenGameCard = mHand[cardIndex];
            mHand.erase(mHand.begin() + cardIndex);

            return chosenGameCard;
        }
        else {
            nUI.outputMessage("Diese Karte gibt es leider nicht.");
            return chooseCard(matchField);
        }
        
    }
    else {
        nUI.outputMessage("Das war leider keine Zahl.");
        return chooseCard(matchField);
    }
}

int HumanPlayer::chooseRow(std::shared_ptr<Field> matchField) const
{
    UI nUI;

    std::string message = mName + ", deine Karte passt leider in keine Reihe.";

    nUI.outputMessage(message);
    nUI.outputMessage("Nun musst du dir eine Reihe (1-4) aussuchen von der du alle Hornochsen eintuetest.");
    std::string input = nUI.userInput();

    if (isdigit(input[0]) && stoi(input) < 5) {

        return stoi(input) - 1;
    }
    else {
        nUI.outputMessage("Diese Reihe gibt es nicht.");
        return chooseRow(matchField);
    }
}
