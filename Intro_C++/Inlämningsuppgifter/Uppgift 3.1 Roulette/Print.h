#pragma once
#include "Structs.h"
#include "Enums.h"

namespace Print
{
	// Print to console
	void ShowIntro(const Account& account);
	void ShowPersonalDetails(const Account& account);
	void ShowOptions(const Table& table);
	void ShowRules(const Table& table);
	void ShowStats(const Table& table);
	void PrintRouletteType(const Roulette& roulette);
	void PrintRouletteBet();
}
