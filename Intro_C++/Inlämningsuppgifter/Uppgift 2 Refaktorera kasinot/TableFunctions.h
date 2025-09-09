#pragma once
#include "Structs.h"
#include "Enums.h"

namespace TableFunctions
{
	void ChangeBet(Account& account);
	void UpdateStats(Table& table, bool isWin);
	void EvaluateTableEarnings(Account& account, Table& table);
	void HandleBankruptcy(Account& account, Table& table);
	int DrawRandomCard(int cardsLeft[], Cards cards);
	bool CompareCards(int previousCard, int newCard);
	bool IsHigherOrLowerGameOver(Cards cards);
}