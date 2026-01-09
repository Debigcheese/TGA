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
	const int myBetMulti = 2;
	int myMoneyEarned;
};
