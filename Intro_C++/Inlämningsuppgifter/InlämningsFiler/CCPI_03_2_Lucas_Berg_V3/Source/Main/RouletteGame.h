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
	const int myColumnAmount = 3;
	const int myBoardSingleDigitThreshold = 10;

	const int myColumnLeftRemainder = 1;
	const int myColumnMiddleRemainder = 2;
	const int myColumnRightRemainder = 0;

	//PAYOUT
	const int myBetMultiStraight = 36;
	const int myBetMultiColor = 1;
	const int myBetMultiOddOrEven = 1;
	const int myBetMultiRoulette = 3;

	int myMoneyEarned;
	Roulette myRoulette;
};
