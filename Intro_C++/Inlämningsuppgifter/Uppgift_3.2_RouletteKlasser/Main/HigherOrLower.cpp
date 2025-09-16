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
	: myMoneyEarned(0), cards(), points()
{
}

int HigherOrLower::GetMoneyEarned() const
{
	return myMoneyEarned;
}

void HigherOrLower::SetMoneyEarned(int aNewMoney)
{
	myMoneyEarned = aNewMoney;
}

// ---------- Play Higher Or Lower ----------
void HigherOrLower::PlayHigherOrLower(Account& aAccount)
{
	points.currentPoints = 0;
	int currentCardIndex = DrawRandomCard();
	bool gameOver = false;

	while (!gameOver)
	{

		Print::ShowPersonalDetails(aAccount, Casino::GetStatArr(), Casino::GetPlayerName());
		std::cout << "\n";

		std::cout << "Points: " << points.currentPoints << "\n";
		std::cout << "Current card: [" << cards.cardLabels[currentCardIndex] << "] \n\n";

		std::cout << "Is next card - \n";
		std::cout << "Higher: (1)\n";
		std::cout << "Lower:  (2)\n\n";
		std::cout << "Choice: ";

		int Higher = static_cast<int>(CardGuess::CardGuess_Higher);
		int Lower = static_cast<int>(CardGuess::CardGuess_Lower);

		int choice = ReadIntInRange(Higher, Lower);
		CardGuess cardGuess = static_cast<CardGuess>(choice);

		std::cout << "Drawing card... \n";
		system("pause");
		std::cout << "\n";

		int randomCardIndex = DrawRandomCard();
		bool cardIsHigher = CompareCards(cards.cardValues[currentCardIndex], cards.cardValues[randomCardIndex]);

		std::cout << "You drew: [" << cards.cardLabels[randomCardIndex] << "]\n";
		std::cout << "You guessed [" << cards.cardLabels[randomCardIndex] << "]"
			<< " is ";
		if (cardGuess == CardGuess::CardGuess_Higher)
		{
			std::cout << "HIGHER than ";
		}
		else
		{
			std::cout << "LOWER than ";
		}
		std::cout << "[" << cards.cardLabels[currentCardIndex] << "] ";

		if ((cardGuess == CardGuess::CardGuess_Higher && cardIsHigher) || (cardGuess == CardGuess::CardGuess_Lower && !cardIsHigher))
		{
			std::cout << "which is CORRECT \n";
			points.currentPoints++;
		}
		else
		{
			std::cout << "which is FALSE \n";
		}

		if (IsHigherOrLowerGameOver())
		{
			std::cout << "Deck of cards is empty!\n";
			std::cout << "You got: " << points.currentPoints << "/13 correct\n";
			std::cout << "Required points to win: " << points.requiredPoints << "/13 correct\n";

			if (points.currentPoints >= points.requiredPoints)
			{
				myMoneyEarned += Casino::Payout(aAccount, BET_MULTI_HIGHER_OR_LOWER);
				Casino::UpdateStats(true);
			}
			else
			{
				myMoneyEarned -= Casino::DeductBet(aAccount);
				Casino::UpdateStats(false);
			}
			gameOver = true;
		}

		system("pause");
		system("cls");
		currentCardIndex = randomCardIndex;
	}


}

//Higher or lower class specific functions
int HigherOrLower::DrawRandomCard()
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
		if (IsHigherOrLowerGameOver())
		{
			break;
		}
	}

	return randomCardIndex;
}
bool HigherOrLower::CompareCards(int aPreviousCard, int aNewCard) const
{
	if (aNewCard > aPreviousCard)
	{
		return true; //is higher
	}
	else
	{
		return false; //is lower
	}

}
bool HigherOrLower::IsHigherOrLowerGameOver() const
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

