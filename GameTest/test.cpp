#include "pch.h"
#include "GameCardCreator.h"
#include "Dealer.h"
#include <iostream>
#include "Field.h"
#include "GameControl.h"
#include "Player.h"
#include "LowestCardBot.h"
#include "HighestCardBot.h"
#include <memory>


TEST(TestGameCard, SmallerOperatorSortedByValue)
{
	GameCard card1 { 1, 1 };
	GameCard card2 { 2, 1 };
	EXPECT_TRUE(card1 < card2);
}

TEST(TestGameCard, SmallerOperatorIdempotence)
{
	GameCard card1 { 1, 1 };
	GameCard card2 { 2, 1 };
	EXPECT_TRUE(card1 < card2);
	EXPECT_FALSE(card2 < card1);
}

TEST(TestGameCard, SmallerOperatorValueDoesntMatter)
{
	GameCard card1 { 1, 10000 };
	GameCard card2 { 2, 1 };
	EXPECT_TRUE(card1 < card2);
	EXPECT_FALSE(card2 < card1);
}

TEST(TestGameCard, SmallerOperatorHigherValues)
{
	GameCard card1 { 25, 1 };
	GameCard card2 { 67, 1 };
	EXPECT_TRUE(card1 < card2);
	EXPECT_FALSE(card2 < card1);
}

TEST(TestGameCard, SmallerOperatorMaxRange)
{
	GameCard card1 { 1, 1 };
	GameCard card2 { 104, 1 };
	EXPECT_TRUE(card1 < card2);
	EXPECT_FALSE(card2 < card1);
}

TEST(TestGameCardCreator, CorrectCount) 
{
	auto gameCards = GameCardCreator::CreateGameCards();
	EXPECT_EQ(gameCards.size(), 104);
}

TEST(TestGameCardCreator, CorrectValues) 
{
	auto gameCards = GameCardCreator::CreateGameCards();
	for (int i = 0; i < 104; i++)
	{
		EXPECT_EQ(gameCards[i].value, i+1);
	}
}

TEST(TestGameCardCreator, SmokeTestValues)
{
	auto gameCards = GameCardCreator::CreateGameCards();
	EXPECT_EQ(gameCards[1 - 1].cost, 1);
	EXPECT_EQ(gameCards[104 - 1].cost, 1);

	EXPECT_EQ(gameCards[5 - 1].cost, 2);
	EXPECT_EQ(gameCards[15 - 1].cost, 2);
	EXPECT_EQ(gameCards[25 - 1].cost, 2);
	EXPECT_EQ(gameCards[35 - 1].cost, 2);
	EXPECT_EQ(gameCards[45 - 1].cost, 2);
	EXPECT_EQ(gameCards[65 - 1].cost, 2);
	EXPECT_EQ(gameCards[75 - 1].cost, 2);
	EXPECT_EQ(gameCards[85 - 1].cost, 2);
	EXPECT_EQ(gameCards[95 - 1].cost, 2);

	EXPECT_EQ(gameCards[10 - 1].cost, 3);
	EXPECT_EQ(gameCards[20 - 1].cost, 3);
	EXPECT_EQ(gameCards[30 - 1].cost, 3);
	EXPECT_EQ(gameCards[40 - 1].cost, 3);
	EXPECT_EQ(gameCards[50 - 1].cost, 3);
	EXPECT_EQ(gameCards[60 - 1].cost, 3);
	EXPECT_EQ(gameCards[70 - 1].cost, 3);
	EXPECT_EQ(gameCards[80 - 1].cost, 3);
	EXPECT_EQ(gameCards[90 - 1].cost, 3);
	EXPECT_EQ(gameCards[100 - 1].cost, 3);

	EXPECT_EQ(gameCards[11 - 1].cost, 5);
	EXPECT_EQ(gameCards[22 - 1].cost, 5);
	EXPECT_EQ(gameCards[33 - 1].cost, 5);
	EXPECT_EQ(gameCards[44 - 1].cost, 5);
	EXPECT_EQ(gameCards[66 - 1].cost, 5);
	EXPECT_EQ(gameCards[77 - 1].cost, 5);
	EXPECT_EQ(gameCards[88 - 1].cost, 5);
	EXPECT_EQ(gameCards[99 - 1].cost, 5);

	EXPECT_EQ(gameCards[55 - 1].cost, 7);
}

TEST(TestDealer, TestDraw)
{
	Dealer dealer;
	auto cards = dealer.Draw(10);
	EXPECT_EQ(cards.size(), 10);
}

TEST(TestDealer, TestNoDuplicates)
{
	Dealer dealer;
	std::set<GameCard> gameCards;
	for (int i = 0; i < 10; i++)
	{
		auto cards = dealer.Draw(10);
		gameCards.insert(cards.begin(), cards.end());
	}
	EXPECT_EQ(gameCards.size(), 100);
}

TEST(TestDealer, TestReset)
{
	Dealer dealer;
	auto cards = dealer.Draw(104);

	dealer.Reset();

	auto hundredFreshCards = dealer.Draw(100);
	EXPECT_EQ(hundredFreshCards.size(), 100);
}

TEST(TestField, CostCount)
{
	Field matchField;

	matchField.CreateMockedField({{{11,5,55,104},{3},{104,33,12,30},{44,50,100,6,12,45}}});

	EXPECT_EQ(matchField.getCostOfRow(0), 15);
	EXPECT_EQ(matchField.getCostOfRow(1), 1);
	EXPECT_EQ(matchField.getCostOfRow(2), 10);
	EXPECT_EQ(matchField.getCostOfRow(3), 15);

}


TEST(TestField, ResettingRows)
{

	Field matchField;

	GameCard Card = {7,1};

	matchField.CreateMockedField({{{11,5,55,104},{3},{104,33,12,30},{44,50,100,6,12,45}}});

	matchField.resetRow(0,Card);

	EXPECT_EQ(matchField.getPlayingField()[0].front().value, Card.value);
	EXPECT_EQ(matchField.getPlayingField()[0].back().value, Card.value);

}

TEST(TestField, PlacingCard)
{

	Field matchField;

	GameCard Card = { 7,1 };

	matchField.CreateMockedField({ {{11,5,55,104},{3},{104,33,12,30},{44,50,100,6,12,45}} });

	matchField.placeCard(1, Card);

	EXPECT_EQ(matchField.getPlayingField()[1].back().value, Card.value);

}

TEST(TestField, CheckingForFullRow)
{

	Field matchField;

	matchField.CreateMockedField({ {{99,77,5,4,3},{34,3,44,12,18,29},{2},{104,5,6,4,3,2}} });

	EXPECT_FALSE(matchField.isFullRow(0));
	EXPECT_TRUE(matchField.isFullRow(1));
	EXPECT_FALSE(matchField.isFullRow(2));
	EXPECT_TRUE(matchField.isFullRow(3));


}

TEST(TestField, FindingTheCorrectRow)
{
	Field matchField;

	matchField.CreateMockedField({ {{99},{34},{2},{5}} });

	EXPECT_EQ(matchField.findCorrectRow(100), 0);
	EXPECT_EQ(matchField.findCorrectRow(98), 1);
	EXPECT_EQ(matchField.findCorrectRow(35), 1);
	EXPECT_EQ(matchField.findCorrectRow(7), 3);
	EXPECT_EQ(matchField.findCorrectRow(3), 2);
	EXPECT_EQ(matchField.findCorrectRow(1), 5);
	EXPECT_EQ(matchField.findCorrectRow(6), 3);

	matchField.CreateMockedField({{{88},{34},{2},{5}}});

	EXPECT_EQ(matchField.findCorrectRow(4), 2);
	EXPECT_EQ(matchField.findCorrectRow(1), 5);
	EXPECT_EQ(matchField.findCorrectRow(6), 3);
	EXPECT_EQ(matchField.findCorrectRow(35), 1);

}

TEST(TestBot, FindCheapestRow)
{
	std::shared_ptr<Field> matchField(new Field);
	std::unique_ptr<Player> Bot(new LowestCardBot());

	matchField->CreateMockedField({ {{99,77,5,4,3},{34,3,44,12,18,29},{2},{104,5,6,4,3,2}} });

	EXPECT_EQ(Bot->findCheapestRow(matchField), 2);

}

TEST(TestLowestCardBot, PlaceCard) 
{
	std::unique_ptr<Player> Bot(new LowestCardBot());
	std::shared_ptr<Field> matchField(new Field);

	Bot->DrawHand({ {1,1},{104,1},{55,7} });

	EXPECT_EQ(Bot->chooseCard(matchField).value,1);
	EXPECT_EQ(Bot->mHand[0].value, 104);

}

TEST(TestHighestCardBot, PlaceCard)
{
	std::unique_ptr<Player> Bot(new HighestCardBot());
	std::shared_ptr<Field> matchField(new Field);

	Bot->DrawHand({ {1,1},{104,1},{55,7} });

	EXPECT_EQ(Bot->chooseCard(matchField).value, 104);
	EXPECT_EQ(Bot->mHand[0].value, 1);
}


TEST(TestSmartBot, DeleteBadCards)
{
	SmartBot Bot(false);
	std::shared_ptr<Field> matchField(new Field);

	matchField->CreateMockedField({ {{99},{34},{42},{24}} });

	Bot.DrawHand({ {1,1} });
	Bot.mGoodCardsInHand = Bot.mHand;
	Bot.removeCardsThatLeadToCost(matchField);

	EXPECT_EQ(Bot.mGoodCardsInHand.size(), 0);

	Bot.DrawHand({{2,1},{104,1}});
	Bot.mGoodCardsInHand = Bot.mHand;
	Bot.removeCardsThatLeadToCost(matchField);

	EXPECT_EQ(Bot.mGoodCardsInHand.size(), 1);
	EXPECT_EQ(Bot.mGoodCardsInHand[0].value, 104);


	matchField->CreateMockedField({ {{53,83,85},{4,8,21,38,82},{66,89},{84,100}} });

	Bot.DrawHand({ {30,3},{79,1},{45,2},{46,1},{59,1},{33,1}});
	Bot.mGoodCardsInHand = Bot.mHand;
	Bot.removeCardsThatLeadToCost(matchField);

	EXPECT_EQ(Bot.mGoodCardsInHand.size(), 0);

}

TEST(TestSmartBot, FindingTheLowestCard)
{
	SmartBot Bot(false);
	std::vector<GameCard> Hand = { {3,1},{5,2},{33,5} };

	EXPECT_EQ(Bot.Lowestcard(Hand).value, 3);
}

TEST(TestSmartBot, FindingCardThatGoesShortestRow)
{
	SmartBot Bot(false);
	std::shared_ptr<Field> matchField(new Field);

	matchField->CreateMockedField({ {{53,83,85},{4,8,21,38,82},{66,89},{84,100,101,103}} });

	std::vector<GameCard> Hand = { {104,1},{86,1},{83,1},{90,3},{91,1} };

	EXPECT_EQ(Bot.CardThatGoesShortestRow(matchField,Hand).value, 90);
}

TEST(TestSmartBot, ChoosingCard) 
{
	SmartBot Bot(false);
	std::shared_ptr<Field> matchField(new Field);

	matchField->CreateMockedField({ {{53,83,85},{4,8,21,38,82},{66,89},{84,100,101,103}} });

	Bot.DrawHand({{2,1},{86,1},{104,1},{99,1},{5,2},{17,1},{90,1}});

	EXPECT_EQ(Bot.chooseCard(matchField).value, 99);

	Bot.DrawHand({ {2,1},{14,1},{1,1},{5,2},{17,1}});

	EXPECT_EQ(Bot.chooseCard(matchField).value, 1);
}

bool considerLowestDiff = false;

TEST(BotvBot, SmartvHigh)
{
	GameControl Controller;

	Controller.Player1 = std::make_shared<HighestCardBot>();
	Controller.Player2 = std::make_shared<SmartBot>(considerLowestDiff);;

	float player2 = 0;

	for (int i = 0; i < 1000; i++) {
		int winner = Controller.startRound();
		if (winner == 2) {
			player2++;
		}
	}
	std::cout << player2/(float)10 << "%" << std::endl;

	EXPECT_TRUE(player2/(float)1000 >= 0.8);
}

TEST(BotvBot, SmartvLow)
{
	GameControl Controller;

	Controller.Player1 = std::make_shared<LowestCardBot>();
	Controller.Player2 = std::make_shared<SmartBot>(considerLowestDiff);

	float player2 = 0;

	for (int i = 0; i < 1000; i++) {
		int winner = Controller.startRound();
		if (winner == 2) {
			player2++;
		}
	}
	std::cout << player2 / (float)10 << "%" << std::endl;

	EXPECT_TRUE(player2 / (float)1000 >= 0.8);
}

TEST(BotvBot, SmartvRand)
{
	GameControl Controller;

	Controller.Player1 = std::make_shared<RandomBot>();
	Controller.Player2 = std::make_shared<SmartBot>(considerLowestDiff);

	float player2 = 0;

	for (int i = 0; i < 1000; i++) {
		int winner = Controller.startRound();
		if (winner == 2) {
			player2++;
		}
	}
	std::cout << player2 / (float)10 << "%" << std::endl;

	EXPECT_TRUE(player2 / (float)1000 >= 0.8);
}

TEST(BotvBot, SmartvSmartDiff)
{
	GameControl Controller;

	Controller.Player1 = std::make_shared<SmartBot>(true);

	Controller.Player2 = std::make_shared<SmartBot>(false);

	float player2 = 0;
	float player1 = 0;

	for (int i = 0; i < 1000; i++) {
		int winner = Controller.startRound();
		if (winner == 2) {
			player2++;
		}
		else if (winner == 1) {
			player1++;
		}
	}
	
	if(player1 > player2){
		std::cout << std::endl << "SmartBot der Differenzen beruecksichtigt gewinnt " << player1 << ":" << player2 << std::endl << std::endl;
	}
	else {
		std::cout << std::endl << "SmartBot der keine Differenzen beruecksichtigt gewinnt " << player2 << ":" << player1 << std::endl << std::endl;
	}

}
