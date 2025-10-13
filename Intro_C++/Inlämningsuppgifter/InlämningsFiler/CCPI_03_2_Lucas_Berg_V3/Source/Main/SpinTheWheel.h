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
	const int myDefaultValuePlay = 1;
	const int myBetMultiSmall = 2;
	const int myBetMultiBig = 40;

	int myMoneyEarned;
};
