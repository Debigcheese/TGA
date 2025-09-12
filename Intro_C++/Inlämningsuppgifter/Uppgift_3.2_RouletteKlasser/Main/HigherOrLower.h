#pragma once
#include "Structs.h"
#include "Enums.h"

class HigherOrLower
{
public:
	HigherOrLower();
	int GetMoneyEarned() const;
	void SetMoneyEarned(int aNewMoney);

	void PlayHigherOrLower(Account& account);
	//HigherOrLower
	int DrawRandomCard();
	bool CompareCards(int previousCard, int newCard) const;
	bool IsHigherOrLowerGameOver() const;

private:
	int myMoneyEarned;
	Cards cards;
	HighOrLowPoints points;
};

