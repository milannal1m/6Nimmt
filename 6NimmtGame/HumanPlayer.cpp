#include "pch.h"
#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(std::shared_ptr<Dealer> CardDealer):Player(CardDealer),
    mUI(std::make_shared<UI>())
{
    mUI->outputMessage("\nWie lautet dein Name?");
    mName = mUI->userInput();
    mUI->outputMessage("\n");
    mIsHumanPlayer = true;
}

HumanPlayer::~HumanPlayer()
{
}

GameCard HumanPlayer::chooseCard(std::shared_ptr<Field> matchField)
{
    
    mUI->outputMessage("\nDein Deck:");
    mUI->printHand(mHand);
    std::string message = mName + "(" + std::to_string(mCost) + ")" + ", waehle eine Karte aus.";
    mUI->outputMessage(message);

    std::string input = mUI->userInput();
    mUI->outputMessage("");

    if (isdigit(input[0])) {
        int cardIndex = stoi(input)-1;
        if (cardIndex <= mHand.size()-1) {
            GameCard chosenGameCard = mHand[cardIndex];
            mHand.erase(mHand.begin() + cardIndex);

            return chosenGameCard;
        }
        else {
            mUI->outputMessage("Diese Karte gibt es leider nicht.");
            return chooseCard(matchField);
        }
        
    }
    else {
        mUI->outputMessage("Das war leider keine Zahl.");
        return chooseCard(matchField);
    }
}

int HumanPlayer::chooseRow(std::shared_ptr<Field> matchField) const
{
   

    std::string message = mName + ", deine Karte passt leider in keine Reihe.";

    mUI->outputMessage(message);
    mUI->outputMessage("Nun musst du dir eine Reihe (1-4) aussuchen von der du alle Hornochsen eintuetest.");
    std::string input = mUI->userInput();

    if (isdigit(input[0]) && stoi(input) < 5) {

        return stoi(input) - 1;
    }
    else {
        mUI->outputMessage("Diese Reihe gibt es nicht.");
        return chooseRow(matchField);
    }
}
