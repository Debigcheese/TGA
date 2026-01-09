#include "SpinTheWheel.h"
#include "Casino.h"
#include "Helpers.h"
#include "Print.h"

#include <iostream>

using namespace Helpers;
using namespace Print;

SpinTheWheel::SpinTheWheel()
	: myMoneyEarned(0)
{
}

int SpinTheWheel::GetMoneyEarned() const
{
	return myMoneyEarned;
}

void SpinTheWheel::SetMoneyEarned(int aNewMoney)
{
	myMoneyEarned = aNewMoney;
}

// ---------- Spin the wheel ----------
void SpinTheWheel::PlaySpinWheelRound(Account& aAccount)
{
	std::cout << "\nSpin The Wheel (1):  ";
	ReadIntInRange(myDefaultValuePlay, myDefaultValuePlay);

	int dice1 = Casino::RollDice();
	int dice2 = Casino::RollDice();
	int dice3 = Casino::RollDice();

	std::cout << dice1 << " | " << dice2 << " | " << dice3 << "\n";

	if (dice1 == dice2 && dice2 == dice3)
	{
		myMoneyEarned += Casino::Payout(aAccount, myBetMultiBig);
		Casino::UpdateStats(true);
	}
	else if ((dice1 == dice2) || (dice2 == dice3) || (dice3 == dice1))
	{
		myMoneyEarned += Casino::Payout(aAccount, myBetMultiSmall);
		Casino::UpdateStats(true);
	}
	else
	{
		myMoneyEarned -= Casino::DeductBet(aAccount);
		Casino::UpdateStats(false);
	}

	system("pause");
}
