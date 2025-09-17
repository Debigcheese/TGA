#pragma once
#include "Structs.h"
#include "Enums.h"

class HigherOrLower
{
public:
	HigherOrLower();
	int GetMoneyEarned() const;
	void SetMoneyEarned(int aNewMoney);

	void PlayHigherOrLower(Account& aAccount);
	//HigherOrLower
	int DrawRandomCard();
	bool CompareCards(int aPreviousCard, int aNewCard) const;
	bool IsHigherOrLowerGameOver() const;

private:
	int myMoneyEarned;
	Cards cards;
	HighOrLowPoints points;
};

