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
	ReadIntInRange(SPIN_THE_WHEEL_DEFAULT_VALUE_PLAY, SPIN_THE_WHEEL_DEFAULT_VALUE_PLAY);

	int dice1 = RollDice();
	int dice2 = RollDice();
	int dice3 = RollDice();

	std::cout << dice1 << " | " << dice2 << " | " << dice3 << "\n";

	if (dice1 == dice2 && dice2 == dice3)
	{
		myMoneyEarned += Casino::Payout(aAccount, BET_MULTI_SPIN_WHEEL_BIG);
		Casino::UpdateStats(true);
	}
	else if ((dice1 == dice2) || (dice2 == dice3) || (dice3 == dice1))
	{
		myMoneyEarned += Casino::Payout(aAccount, BET_MULTI_SPIN_WHEEL_SMALL);
		Casino::UpdateStats(true);
	}
	else
	{
		myMoneyEarned -= Casino::DeductBet(aAccount);
		Casino::UpdateStats(false);
	}

	system("pause");
}