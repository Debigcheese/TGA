#pragma once
#include "Structs.h"
#include "Enums.h"

class OddOrEvenGame
{

public:
	OddOrEvenGame();
	int GetMoneyEarned() const;
	void SetMoneyEarned(int aNewMoney);

	void PlayOddEvenRound(Account& account);
	bool IsDiceOdd(const int dice) const;

private:
	int myMoneyEarned;
};

