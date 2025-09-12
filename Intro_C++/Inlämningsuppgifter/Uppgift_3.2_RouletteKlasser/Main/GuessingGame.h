#pragma once
#include "Structs.h"
#include "Enums.h"

class GuessingGame
{
public:
	GuessingGame();
	GuessingGame(int aMoneyEarned);
	int GetMoneyEarned();
	void SetMoneyEarned(int aNewMoney);

	void PlayGuessingRound(Account& account, Table& table);

private:
	int myMoneyEarned;
};

