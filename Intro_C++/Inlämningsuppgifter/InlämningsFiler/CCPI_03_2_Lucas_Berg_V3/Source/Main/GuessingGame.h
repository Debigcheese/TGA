#pragma once
#include "Structs.h"

class GuessingGame
{
public:
	GuessingGame();
	GuessingGame(int aBetMin, int aBetMax);
	int GetMoneyEarned() const;
	void SetMoneyEarned(int aNewMoney);
	int GetBetMaximum() const;
	int GetBetMinimum() const;

	void PlayGuessingRound(Account& aAccount);

private:
	int myBetMaximum;
	int myBetMinimum;
	int myMoneyEarned;
	//constants
	const int myBetMulti = 5;
};
