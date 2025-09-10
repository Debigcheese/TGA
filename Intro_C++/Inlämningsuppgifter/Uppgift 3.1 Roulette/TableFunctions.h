#pragma once
#include "Structs.h"
#include "Enums.h"

namespace TableFunctions
{
	void ChangeBet(Account& account);
	void UpdateStats(Table& table, bool isWin);
	bool EvaluateTableEarnings(Account& account, Table& table);
	void HandleBankruptcy(Account& account, Table& table);
	void RoulettePayout(Account& account, Table& table, RouletteBetType rouletteBetType);
	//HigherOrLower
	int DrawRandomCard(Cards& cards);
	bool CompareCards(int previousCard, int newCard);
	bool IsHigherOrLowerGameOver(Cards cards);
	//Roulette
	void DrawRouletteBoard(const Roulette& roulette);
	int GenerateRouletteNumber(const Roulette& roulette);
	void RouletteCorrectGuess(Roulette& roulette, const int winningNumber);
}