#pragma once
#include "Structs.h"

class OddOrEvenGame
{
public:
	OddOrEvenGame();
	int GetMoneyEarned() const;
	void SetMoneyEarned(int aNewMoney);

	bool IsDiceOdd(const int aDice) const;
	void PlayOddEvenRound(Account& aAccount);

private:
	const int EVEN_DIVISOR = 2;
	const int REMAINDER_ODD = 1;
	const int REMAINDER_EVEN = 0;
	const int BET_MULTI_ODD_OR_EVEN = 2;

	int myMoneyEarned;
};
