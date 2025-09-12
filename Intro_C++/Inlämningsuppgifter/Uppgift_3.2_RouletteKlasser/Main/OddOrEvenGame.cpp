#include "Casino.h"
#include "OddOrEvenGame.h"
#include "Helpers.h"
#include "Print.h"
#include "CONSTANTS.h"

#include <iostream>

using namespace Helpers;
using namespace Print;
using namespace CONSTANTS;

OddOrEvenGame::OddOrEvenGame()
{
}

OddOrEvenGame::OddOrEvenGame(int aMoneyEarned) : myMoneyEarned(aMoneyEarned) {}

int OddOrEvenGame::GetMoneyEarned()
{
	return myMoneyEarned;
}

void OddOrEvenGame::SetMoneyEarned(int aNewMoney)
{
	myMoneyEarned = aNewMoney;
}

// ---------- Odd or Even ----------
void OddOrEvenGame::PlayOddEvenRound(Account& account, Table& table)
{
	std::cout << "\nChoose: Odd (1) or Even (2): ";
	int pick = ReadIntInRange(1, 2);

	int dice1 = RollDice();
	int dice2 = RollDice();
	std::cout << "Dice 1: " << dice1 << ", Dice 2: " << dice2 << "\n";

	bool dice1Odd = (dice1 % 2 == 1);
	bool dice2Odd = (dice2 % 2 == 1);

	bool bothOdd = dice1Odd && dice2Odd;
	bool bothEven = !dice1Odd && !dice2Odd;

	bool pickedOdd = (pick == 1);
	bool playerWins = (pickedOdd && bothOdd) || (!pickedOdd && bothEven);

	if (playerWins)
	{
		int win = account.bet * BET_MULTI_ODD_OR_EVEN;
		account.money += win;
		table.moneyArr[TableToIndex(TableOption::OddOrEven)] += win;
		std::cout << "You win! Your payout: " << win << " kr.\n";
		Casino::UpdateStats(table, true);
	}
	else
	{
		account.money -= account.bet;
		table.moneyArr[TableToIndex(TableOption::OddOrEven)] -= account.bet;
		std::cout << "House wins. You lose " << account.bet << " kr.\n";
		Casino::UpdateStats(table, false);
	}
	system("pause");
}
