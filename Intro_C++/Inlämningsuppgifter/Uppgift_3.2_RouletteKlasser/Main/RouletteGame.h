#pragma once
#include "Structs.h"
#include "Enums.h"

class RouletteGame
{
public:
	RouletteGame();
	RouletteGame(int aMoneyEarned);
	int GetMoneyEarned();
	void SetMoneyEarned(int aNewMoney);

	// ---------- Play Roulette ----------
	void PlayRoulette(Account& account, Table& table);
	//Roulette class specific functions
	void DrawRouletteBoard(const Roulette& roulette);
	bool RouletteResult(const Roulette& roulette);
	int RouletteBetPayout(const Roulette& roulette);
	void PrintRouletteBet(const RouletteBetType& betType);

private:
	int myMoneyEarned;

};

