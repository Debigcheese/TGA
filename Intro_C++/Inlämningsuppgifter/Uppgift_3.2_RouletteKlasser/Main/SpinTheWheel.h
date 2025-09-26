#pragma once
#include "Structs.h"

class SpinTheWheel
{
public:
	SpinTheWheel();
	int GetMoneyEarned() const;
	void SetMoneyEarned(int aNewMoney);

	void PlaySpinWheelRound(Account& aAccount);

private:
	//SPIN THE WHEEL
	const int SPIN_THE_WHEEL_DEFAULT_VALUE_PLAY = 1;
	const int BET_MULTI_SPIN_WHEEL_SMALL = 2;
	const int BET_MULTI_SPIN_WHEEL_BIG = 40;

	int myMoneyEarned;
};
