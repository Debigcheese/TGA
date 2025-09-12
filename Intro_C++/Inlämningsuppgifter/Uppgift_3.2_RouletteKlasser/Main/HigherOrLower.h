#pragma once
#include "Structs.h"
#include "Enums.h"

class HigherOrLower
{
public:
	HigherOrLower();
	HigherOrLower(int aMoneyEarned);
	int GetMoneyEarned();
	void SetMoneyEarned(int aNewMoney);

	void PlayHigherOrLower(Account& account, Table& table);
	//HigherOrLower
	int DrawRandomCard(Cards& cards);
	bool CompareCards(int previousCard, int newCard);
	bool IsHigherOrLowerGameOver(const Cards& cards);

private:
	int myMoneyEarned;
};

