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
	: myMoneyEarned(0)
{
}

int OddOrEvenGame::GetMoneyEarned() const
{
	return myMoneyEarned;
}

void OddOrEvenGame::SetMoneyEarned(int aNewMoney)
{
	myMoneyEarned = aNewMoney;
}

// ---------- Odd or Even ----------
void OddOrEvenGame::PlayOddEvenRound(Account& aAccount)
{
	std::cout << "\nChoose: Odd (1) or Even (2): ";
	int pick = ReadIntInRange(static_cast<int>(OddOrEven::OddOrEven_Odd), static_cast<int>(OddOrEven::OddOrEven_Even));

	int dice1 = RollDice();
	int dice2 = RollDice();
	std::cout << "Dice 1: " << dice1 << ", Dice 2: " << dice2 << "\n";

	bool dice1Odd = IsDiceOdd(dice1);
	bool dice2Odd = IsDiceOdd(dice2);

	bool bothOdd = dice1Odd && dice2Odd;
	bool bothEven = !dice1Odd && !dice2Odd;

	bool pickedOdd = (pick == static_cast<int>(OddOrEven::OddOrEven_Odd));
	bool playerWins = (pickedOdd && bothOdd) || (!pickedOdd && bothEven);

	if (playerWins)
	{
		myMoneyEarned += Casino::Payout(aAccount, BET_MULTI_ODD_OR_EVEN);
		Casino::UpdateStats(true);
	}
	else
	{
		myMoneyEarned -= Casino::DeductBet(aAccount);
		Casino::UpdateStats(false);
	}

	system("pause");
}

bool OddOrEvenGame::IsDiceOdd(const int aDice) const
{
	return (aDice % CONSTANTS::EVEN_DIVISOR == CONSTANTS::REMAINDER_ODD);
}
