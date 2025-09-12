#include "GuessingGame.h"
#include "Casino.h"
#include "Helpers.h"
#include "Print.h"
#include "CONSTANTS.h"

#include <iostream>

using namespace Helpers;
using namespace Print;
using namespace CONSTANTS;

GuessingGame::GuessingGame()
	: myMoneyEarned(0)
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
// ---------- Guessing Game ----------
void GuessingGame::PlayGuessingRound(Account& account)
{
	std::cout << "\nEnter your guess (2-12): ";
	int guess = ReadIntInRange(2, 12);

	int diceOne = RollDice();
	int diceTwo = RollDice();
	int sum = diceOne + diceTwo;

	std::cout << "\nDice 1: " << diceOne << ", Dice 2: " << diceTwo << "  -> Sum: " << sum << "\n";

	if (guess == sum)
	{
		myMoneyEarned += Casino::Payout(account, BET_MULTI_GUESS);
		Casino::UpdateStats(true);
	}
	else
	{
		myMoneyEarned -= Casino::DeductBet(account);
		Casino::UpdateStats(false);
	}

	system("pause");
}


