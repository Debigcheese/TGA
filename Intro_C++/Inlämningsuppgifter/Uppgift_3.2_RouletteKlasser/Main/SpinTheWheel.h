#pragma once
#include "Structs.h"
#include "Enums.h"

class SpinTheWheel
{
public:
	SpinTheWheel();
	SpinTheWheel(int aMoneyEarned);
	int GetMoneyEarned();
	void SetMoneyEarned(int aNewMoney);

	void PlaySpinWheelRound(Account& account, Table& table);

private:
	int myMoneyEarned;
};

