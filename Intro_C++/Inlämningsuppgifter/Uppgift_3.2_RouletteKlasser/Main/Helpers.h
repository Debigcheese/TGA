#pragma once
#include "Enums.h"
#include "Structs.h"
#include <string>

namespace Helpers
{
	int ReadIntInRange(int aMinValue, int aMaxValue);
	int GenerateRandomNumber(int aMin, int aMaxValue);
	int RollDice();
	int TableToIndex(const TableOption& aTable);
	int ResultToIndex(const Result& aGameResult);

	void PrintIndexWithColor(const RouletteColor aColor, const int aIndex);
	void PrintBracketsWithColor(const RouletteColor aColor, const Side aSide);
	RouletteColor GetColorFromIndex(const char aRouletteLayout[], const int aIndex);
	OddOrEven GetOddOrEvenFromIndex(const int aIndex);
	Columns GetColumnFromIndex(const int aIndex);
	std::string GetStringFromRoulette(const RouletteBetPerType aBetPerType, const RouletteBetType aBetType);
	std::string myToString(int aValue);

}