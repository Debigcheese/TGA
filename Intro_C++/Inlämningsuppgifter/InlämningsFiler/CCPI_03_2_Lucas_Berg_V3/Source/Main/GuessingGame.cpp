#include "GuessingGame.h"
#include "Casino.h"
#include "Helpers.h"
#include "Print.h"

#include <iostream>

using namespace Helpers;
using namespace Print;

GuessingGame::GuessingGame()
	: myMoneyEarned(0), myBetMinimum(0), myBetMaximum(0)
{
}

GuessingGame::GuessingGame(int aBetMin, int aBetMax)
	: myMoneyEarned(0), myBetMinimum(aBetMin), myBetMaximum(aBetMax)
{
}

int GuessingGame::GetMoneyEarned() const
{
	return myMoneyEarned;
}

void GuessingGame::SetMoneyEarned(int aNewMoney)
{
	myMoneyEarned = aNewMoney;
}

int GuessingGame::GetBetMaximum() const
{
	return myBetMaximum;
}

int GuessingGame::GetBetMinimum() const
{
	return myBetMinimum;
}

// ---------- Guessing Game ----------
void GuessingGame::PlayGuessingRound(Account& aAccount)
{
	std::cout << "\nEnter your guess (2-12): ";
	int doubleDiceMin = DICE_MIN + DICE_MIN;
	int doubleDiceMax = DICE_MAX + DICE_MAX;

	int guess = ReadIntInRange(doubleDiceMin, doubleDiceMax);

	int diceOne = Casino::RollDice();
	int diceTwo = Casino::RollDice();
	int sum = diceOne + diceTwo;

	std::cout << "\nDice 1: " << diceOne << ", Dice 2: " << diceTwo << "  -> Sum: " << sum << "\n";

	if (guess == sum)
	{
		myMoneyEarned += Casino::Payout(aAccount, myBetMulti);
		Casino::UpdateStats(true);
	}
	else
	{
		myMoneyEarned -= Casino::DeductBet(aAccount);
		Casino::UpdateStats(false);
	}

	system("pause");
}
