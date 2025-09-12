#include "Casino.h"
#include "HigherOrLower.h"
#include "Helpers.h"
#include "Print.h"
#include "CONSTANTS.h"

#include <iostream>

using namespace Helpers;
using namespace Print;
using namespace CONSTANTS;

HigherOrLower::HigherOrLower()
{
}

HigherOrLower::HigherOrLower(int aMoneyEarned) : myMoneyEarned(aMoneyEarned) {}

int HigherOrLower::GetMoneyEarned()
{
	return myMoneyEarned;
}

void HigherOrLower::SetMoneyEarned(int aNewMoney)
{
	myMoneyEarned = aNewMoney;
}

// ---------- Play Higher Or Lower ----------
void HigherOrLower::PlayHigherOrLower(Account& account, Table& table)
{
	Cards cards = {};
	HighOrLowPoints points = {};

	points.currentPoints = 0;
	int currentCardIndex = DrawRandomCard(cards);
	bool gameOver = false;

	while (!gameOver)
	{

		Print::ShowPersonalDetails(account);
		std::cout << "\n";

		std::cout << "Points: " << points.currentPoints << "\n";
		std::cout << "Current card: [" << cards.cardLabels[currentCardIndex] << "] \n\n";

		std::cout << "Is next card - \n";
		std::cout << "Higher: (1)\n";
		std::cout << "Lower:  (2)\n\n";
		std::cout << "Choice: ";

		int Higher = static_cast<int>(CardGuess::Higher);
		int Lower = static_cast<int>(CardGuess::Lower);

		int choice = ReadIntInRange(Higher, Lower);
		CardGuess cardGuess = static_cast<CardGuess>(choice);

		std::cout << "Drawing card... \n";
		system("pause");
		std::cout << "\n";

		int randomCardIndex = DrawRandomCard(cards);
		bool cardIsHigher = CompareCards(cards.cardValues[currentCardIndex], cards.cardValues[randomCardIndex]);

		std::cout << "You drew: [" << cards.cardLabels[randomCardIndex] << "]\n";
		std::cout << "You guessed [" << cards.cardLabels[randomCardIndex] << "]"
			<< " is ";
		if (cardGuess == CardGuess::Higher)
		{
			std::cout << "HIGHER than ";
		}
		else
		{
			std::cout << "LOWER than ";
		}
		std::cout << "[" << cards.cardLabels[currentCardIndex] << "] ";

		if ((cardGuess == CardGuess::Higher && cardIsHigher) || (cardGuess == CardGuess::Lower && !cardIsHigher))
		{
			std::cout << "which is CORRECT \n";
			points.currentPoints++;
		}
		else
		{
			std::cout << "which is FALSE \n";
		}

		if (IsHigherOrLowerGameOver(cards))
		{
			std::cout << "Deck of cards is empty!\n";
			std::cout << "You got: " << points.currentPoints << "/13 correct\n";
			std::cout << "Required points to win: " << points.requiredPoints << "/13 correct\n";

			if (points.currentPoints >= points.requiredPoints)
			{
				int win = account.bet * BET_MULTI_HIGHER_OR_LOWER;
				account.money += win;
				table.moneyArr[TableToIndex(TableOption::HighOrLow)] += win;
				std::cout << "<--- 3X WIN! --->\n";
				std::cout << "Payout: " << win << " kr.\n""\n";
				Casino::UpdateStats(table, true);
			}
			else
			{
				account.money -= account.bet;
				table.moneyArr[TableToIndex(TableOption::HighOrLow)] -= account.bet;
				std::cout << "\nYou lost: " << account.bet << " kr.\n";
				Casino::UpdateStats(table, false);
			}
			gameOver = true;
		}

		system("pause");
		system("cls");
		currentCardIndex = randomCardIndex;
	}


}

//Higher or lower class specific functions
int HigherOrLower::DrawRandomCard(Cards& cards)
{
	int randomCardIndex;
	while (true)
	{
		randomCardIndex = GenerateRandomNumber(0, DECK_SIZE - 1);

		if (cards.cardsLeft[randomCardIndex] != 0)
		{
			cards.cardsLeft[randomCardIndex] = 0;
			break;
		}
		if (IsHigherOrLowerGameOver(cards))
		{
			break;
		}
	}

	return randomCardIndex;
}
bool HigherOrLower::CompareCards(int previousCard, int newCard)
{
	if (newCard > previousCard)
	{
		return true; //is higher
	}
	else
	{
		return false; //is lower
	}

}
bool HigherOrLower::IsHigherOrLowerGameOver(const Cards& cards)
{
	int countCardsLeft = 0;
	for (int card : cards.cardsLeft)
	{
		if (card == 0)
		{
			countCardsLeft++;
		}
		if (countCardsLeft >= DECK_SIZE)
		{
			return true;
		}
	}
	return false;
}

