#include "SpinTheWheel.h"
#include "Casino.h"
#include "Helpers.h"
#include "Print.h"
#include "CONSTANTS.h"

#include <iostream>

using namespace Helpers;
using namespace Print;
using namespace CONSTANTS;

SpinTheWheel::SpinTheWheel()
{
}

SpinTheWheel::SpinTheWheel(int aMoneyEarned) : myMoneyEarned(aMoneyEarned) {}

int SpinTheWheel::GetMoneyEarned()
{
	return myMoneyEarned;
}

void SpinTheWheel::SetMoneyEarned(int aNewMoney)
{
	myMoneyEarned = aNewMoney;
}


// ---------- Spin the wheel ----------
void SpinTheWheel::PlaySpinWheelRound(Account& account, Table& table)
{
	std::cout << "\nSpin The Wheel (1):  ";
	ReadIntInRange(1, 1);

	int dice1 = RollDice();
	int dice2 = RollDice();
	int dice3 = RollDice();

	std::cout << dice1 << " | " << dice2 << " | " << dice3 << "\n";

	int win = 0;

	if (dice1 == dice2 && dice2 == dice3)
	{

		win = account.bet * BET_MULTI_SPIN_WHEEL_BIG;
		account.money += win;
		table.moneyArr[TableToIndex(TableOption::SpinTheWheel)] += win;
		std::cout << "<--- 40X WIN! --->\n";
		std::cout << "Your payout: " << win << " kr.\n";
		Casino::UpdateStats(table, true);

	}
	else if ((dice1 == dice2) || (dice2 == dice3) || (dice3 == dice1))
	{

		win = account.bet * BET_MULTI_SPIN_WHEEL_SMALL;
		account.money += win;
		table.moneyArr[TableToIndex(TableOption::SpinTheWheel)] += win;
		std::cout << "<--- 2X WIN! --->\n";
		std::cout << "Your payout: " << win << " kr.\n";
		Casino::UpdateStats(table, true);
	}
	else
	{
		account.money -= account.bet;
		table.moneyArr[TableToIndex(TableOption::SpinTheWheel)] -= account.bet;
		std::cout << "House wins. You lose " << account.bet << " kr.\n";
		Casino::UpdateStats(table, false);
	}
	system("pause");
}