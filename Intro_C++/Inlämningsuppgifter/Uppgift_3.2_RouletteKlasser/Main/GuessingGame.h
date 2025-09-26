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
	const int BET_MULTI_GUESS = 5;
	const int DICE_MIN = 1;
	const int DICE_MAX = 6;
};
