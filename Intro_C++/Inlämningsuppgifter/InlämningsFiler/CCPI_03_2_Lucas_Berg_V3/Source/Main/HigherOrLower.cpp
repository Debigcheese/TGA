#include "Casino.h"
#include "HigherOrLower.h"
#include "Helpers.h"
#include "Print.h"

#include <iostream>

using namespace Helpers;
using namespace Print;

HigherOrLower::HigherOrLower()
	: myMoneyEarned(0), myCards(), myPoints({ myCurrentPoints, myRequiredPoints })
{
	for (int i = 0; i < DECK_SIZE; i++)
	{
		myCards.cardsLeft[i] = myDefaultCardsLeft[i];
	}
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
	myPoints.currentPoints = myCurrentPoints;
	int currentCardIndex = DrawRandomCard();
	bool gameOver = false;

	while (!gameOver)
	{
		Print::ShowPersonalDetails(aAccount, Casino::GetStatArr(), Casino::GetPlayerName());
		std::cout << "\n";

		std::cout << "Points: " << myPoints.currentPoints << "\n";
		std::cout << "Current card: [" << myCards.myCardLabels[currentCardIndex] << "] \n\n";

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

		int randomCardIndex = DrawRandomCard();
		bool cardIsHigher = CompareCards(myCards.myCardValues[currentCardIndex], myCards.myCardValues[randomCardIndex]);

		std::cout << "You drew: [" << myCards.myCardLabels[randomCardIndex] << "]\n";
		std::cout << "You guessed [" << myCards.myCardLabels[randomCardIndex] << "]"
			<< " is ";
		if (cardGuess == CardGuess::Higher)
		{
			std::cout << "HIGHER than ";
		}
		else
		{
			std::cout << "LOWER than ";
		}
		std::cout << "[" << myCards.myCardLabels[currentCardIndex] << "] ";

		if ((cardGuess == CardGuess::Higher && cardIsHigher) || (cardGuess == CardGuess::Lower && !cardIsHigher))
		{
			std::cout << "which is CORRECT \n";
			myPoints.currentPoints++;
		}
		else
		{
			std::cout << "which is FALSE \n";
		}

		if (IsHigherOrLowerGameOver())
		{
			std::cout << "Deck of cards is empty!\n";
			std::cout << "You got: " << myPoints.currentPoints << "/13 correct\n";
			std::cout << "Required points to win: " << myPoints.requiredPoints << "/13 correct\n";

			if (myPoints.currentPoints >= myPoints.requiredPoints)
			{
				myMoneyEarned += Casino::Payout(aAccount, myBetMulti);
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
		randomCardIndex = GenerateRandomNumber(0, DECK_SIZE - myDeckSizeOffset);

		if (myCards.cardsLeft[randomCardIndex] != 0)
		{
			myCards.cardsLeft[randomCardIndex] = 0;
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
	for (int card : myCards.cardsLeft)
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
