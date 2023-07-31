#include "pch.h"
#include "GameCardCreator.h"
#include "Dealer.h"
#include <iostream>
#include "Field.h"
#include "GameControl.h"
#include "Player.h"
#include "LowestCardBot.h"
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

TEST(TestDealer, EmptyAfter104)
{
	Dealer dealer;
	std::set<GameCard> gameCards;
	auto cards = dealer.Draw(104);
	gameCards.insert(cards.begin(), cards.end());

	EXPECT_EQ(gameCards.size(), 104);

	auto empty = dealer.Draw(1);
	EXPECT_EQ(empty.size(), 0);
}

TEST(TestDealer, TestReset)
{
	Dealer dealer;
	auto cards = dealer.Draw(104);

	auto empty = dealer.Draw(1);
	EXPECT_EQ(empty.size(), 0);

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

TEST(TestGameControl, FindingTheCorrectRow)
{
	Field matchField;

	GameControl Controller;

	matchField.CreateMockedField({{{99},{34},{2},{104,5}}});

	EXPECT_EQ(Controller.findCorrectRow(100,matchField.getPlayingField()), 0);
	EXPECT_EQ(Controller.findCorrectRow(98, matchField.getPlayingField()), 1);
	EXPECT_EQ(Controller.findCorrectRow(35, matchField.getPlayingField()), 1);
	EXPECT_EQ(Controller.findCorrectRow(7, matchField.getPlayingField()), 3);
	EXPECT_EQ(Controller.findCorrectRow(3, matchField.getPlayingField()), 2);
	EXPECT_EQ(Controller.findCorrectRow(1, matchField.getPlayingField()), 5);
	EXPECT_EQ(Controller.findCorrectRow(6, matchField.getPlayingField()), 3);

	matchField.CreateMockedField({{{},{34},{},{104,5}}});

	EXPECT_EQ(Controller.findCorrectRow(4, matchField.getPlayingField()), 0);
	EXPECT_EQ(Controller.findCorrectRow(1, matchField.getPlayingField()), 0);
	EXPECT_EQ(Controller.findCorrectRow(6, matchField.getPlayingField()), 3);
	EXPECT_EQ(Controller.findCorrectRow(35, matchField.getPlayingField()), 1);

}

TEST(TestGameControl, CheckingForFullRow)
{
	Field matchField;

	GameControl Controller;

	matchField.CreateMockedField({ {{99,77,5,4,3},{34,3,44,12,18,29},{2},{104,5,6,4,3,2}} });

	EXPECT_FALSE(Controller.isFullRow(0,matchField.getPlayingField()));
	EXPECT_TRUE(Controller.isFullRow(1, matchField.getPlayingField()));
	EXPECT_FALSE(Controller.isFullRow(2, matchField.getPlayingField()));
	EXPECT_TRUE(Controller.isFullRow(3, matchField.getPlayingField()));


}

TEST(Bot, FindLowestCostRow)
{
	std::shared_ptr<Field> matchField;
	Dealer CardDealer;
	std::unique_ptr<Player> Bot(new LowestCardBot(CardDealer));

	matchField->CreateMockedField({ {{99,77,5,4,3},{34,3,44,12,18,29},{2},{104,5,6,4,3,2}} });

	EXPECT_EQ(Bot->findLowestCostRow(matchField), 2);


}

