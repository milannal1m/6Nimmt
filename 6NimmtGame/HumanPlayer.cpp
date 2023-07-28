#include "pch.h"
#include "HumanPlayer.h"

HumanPlayer::HumanPlayer():Player()
{
    UI nUI;

    nUI.outputMessage("Wie lautet dein Name?");
    mName = nUI.userInput();
    mIsHumanPlayer = true;
}

HumanPlayer::~HumanPlayer()
{
}

GameCard HumanPlayer::chooseCard(std::shared_ptr<Field> matchField)
{
    UI nUI;

    nUI.printHand(mHand);
    nUI.outputMessage("Wähle eine Karte aus");

    std::string input = nUI.userInput();

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
