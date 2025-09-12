#pragma once
#include "Structs.h"
#include "Enums.h"

class RouletteGame
{
public:
	RouletteGame();
	int GetMoneyEarned() const;
	void SetMoneyEarned(int aNewMoney);

	// ---------- Play Roulette ----------
	void PlayRoulette(Account& account);
	//Roulette class specific functions
	void DrawRouletteBoard() const;
	bool RouletteResult() const;
	int GetRoulettePayoutAmount() const;
	void PrintRouletteBet(const RouletteBetType& betType) const;

private:
	int myMoneyEarned;
	Roulette roulette;
};

