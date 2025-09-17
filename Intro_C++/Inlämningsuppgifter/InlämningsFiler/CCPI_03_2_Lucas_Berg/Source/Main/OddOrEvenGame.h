#pragma once
#include "Structs.h"
#include "Enums.h"

class OddOrEvenGame
{

public:
	OddOrEvenGame();
	int GetMoneyEarned() const;
	void SetMoneyEarned(int aNewMoney);

	void PlayOddEvenRound(Account& aAccount);
	bool IsDiceOdd(const int aDice) const;

private:
	int myMoneyEarned;
};

