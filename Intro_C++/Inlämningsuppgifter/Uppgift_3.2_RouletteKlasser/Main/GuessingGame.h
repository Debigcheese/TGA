#pragma once
#include "Structs.h"
#include "Enums.h"

class GuessingGame
{
public:
	GuessingGame();
	int GetMoneyEarned() const;
	void SetMoneyEarned(int aNewMoney);

	void PlayGuessingRound(Account& account);

private:
	int myMoneyEarned;
};

