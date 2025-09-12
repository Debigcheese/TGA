#pragma once
#include "Structs.h"
#include "Enums.h"

class OddOrEvenGame
{

public:
	OddOrEvenGame();
	OddOrEvenGame(int aMoneyEarned);
	int GetMoneyEarned();
	void SetMoneyEarned(int aNewMoney);

	void PlayOddEvenRound(Account& account, Table& table);

private:
	int myMoneyEarned;
};

