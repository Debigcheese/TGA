#pragma once
#include "Structs.h"
#include "Enums.h"

namespace TableFunctions
{
	void ChangeBet(Account& account);
	void UpdateStats(Table& table, bool isWin);
	bool EvaluateTableEarnings(Table& table);
	void HandleBankruptcy(Account& account, Table& table);
	int DrawRandomCard(Cards& cards);
	bool CompareCards(int previousCard, int newCard);
	bool IsHigherOrLowerGameOver(const Cards& cards);
}