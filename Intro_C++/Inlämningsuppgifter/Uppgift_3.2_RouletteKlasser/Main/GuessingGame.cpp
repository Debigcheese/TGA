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
{
}

GuessingGame::GuessingGame(int aMoneyEarned = 0) : myMoneyEarned(aMoneyEarned) {}

int GuessingGame::GetMoneyEarned()
{
	return myMoneyEarned;
}

void GuessingGame::SetMoneyEarned(int aNewMoney)
{
	myMoneyEarned = aNewMoney;
}
// ---------- Guessing Game ----------
void GuessingGame::PlayGuessingRound(Account& account, Table& table)
{
	std::cout << "\nEnter your guess (2-12): ";
	int guess = ReadIntInRange(2, 12);

	int diceOne = RollDice();
	int diceTwo = RollDice();
	int sum = diceOne + diceTwo;

	std::cout << "\nDice 1: " << diceOne << ", Dice 2: " << diceTwo << "  -> Sum: " << sum << "\n";

	if (guess == sum)
	{
		int win = account.bet * BET_MULTI_GUESS;
		account.money += win;
		table.moneyArr[TableToIndex(TableOption::GuessingGame)] += win;
		std::cout << "BINGO! Your payout: " << win << " kr.\n";
		Casino::UpdateStats(table, true);
	}
	else
	{
		account.money -= account.bet;
		table.moneyArr[TableToIndex(TableOption::GuessingGame)] -= account.bet;
		std::cout << "Miss! You lose " << account.bet << " kr.\n";
		Casino::UpdateStats(table, false);
	}
	system("pause");
}


