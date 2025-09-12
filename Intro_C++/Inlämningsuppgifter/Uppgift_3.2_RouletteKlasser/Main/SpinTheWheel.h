#pragma once
#include "Structs.h"
#include "Enums.h"

class SpinTheWheel
{
public:
	SpinTheWheel();
	int GetMoneyEarned() const;
	void SetMoneyEarned(int aNewMoney);

	void PlaySpinWheelRound(Account& account);

private:
	int myMoneyEarned;
};

