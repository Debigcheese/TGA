#pragma once
#include "Structs.h"
#include "Enums.h"
#include <string>

class RouletteGame
{
public:
	RouletteGame();
	int GetMoneyEarned() const;
	void SetMoneyEarned(int aNewMoney);

	// ---------- Play Roulette ----------
	void PlayRoulette(Account& aAccount);
	//Roulette class specific functions
	void DrawRouletteBoard() const;
	bool GetRouletteResult() const;
	int GetRoulettePayoutAmount() const;
	void PrintRouletteBet(const RouletteBetType& aBetType) const;

	std::string GetStringFromRoulette(const RouletteBetPerType aBetPerType) const;
	Color GetColorFromIndex(const int aIndex) const;
	OddOrEven GetOddOrEvenFromIndex(const int aIndex) const;
	Columns GetColumnFromIndex(const int aIndex) const;

private:
	static const int ROULETTE_ARRAY_SIZE = 37;
	static const char ROULETTE_LAYOUT[ROULETTE_ARRAY_SIZE];
	static const int ROULETTE_SIZE_TO_INDEX_OFFSET = 1;
	const int COLUMN_TOTAL_AMOUNT = 3;
	const int ROULETTE_BOARD_SINGLE_DIGIT_THRESHOLD = 10;

	const int COLUMN_LEFT_REMAINDER = 1;
	const int COLUMN_MIDDLE_REMAINDER = 2;
	const int COLUMN_RIGHT_REMAINDER = 0;

	//PAYOUT
	const int BET_MULTI_ROULETTE_STRAIGHT = 36;
	const int BET_MULTI_ROULETTE_COLOR = 1;
	const int BET_MULTI_ROULETTE_ODDOREVEN = 1;
	const int BET_MULTI_ROULETTE_COLUMN = 3;

	const int EVEN_DIVISOR = 2;
	const int REMAINDER_ODD = 1;
	const int REMAINDER_EVEN = 0;
	const int ZERO_INDEX = 0;

	int myMoneyEarned;
	Roulette myRoulette;
};
