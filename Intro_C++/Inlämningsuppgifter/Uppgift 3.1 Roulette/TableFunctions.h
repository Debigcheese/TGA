#pragma once
#include "Structs.h"
#include "Enums.h"

namespace TableFunctions
{
	void ChangeBet(Account& account);
	void UpdateStats(Table& table, bool isWin);
	bool EvaluateTableEarnings(Table& table);
	void HandleBankruptcy(Account& account, Table& table);
	//HigherOrLower
	int DrawRandomCard(Cards& cards);
	bool CompareCards(int previousCard, int newCard);
	bool IsHigherOrLowerGameOver(const Cards& cards);
	//Roulette
	void DrawRouletteBoard(const Roulette& roulette);
	int GenerateRouletteNumber(const Roulette& roulette);
	bool RouletteResult(const Roulette& roulette);
	void RouletteBetPayout(Account& account, Table& table, const RouletteBetType& betType);

}