#pragma once
#include "Enums.h"
#include "Structs.h"
#include <string>

namespace Helpers
{
	int ReadIntInRange(int aMinValue, int aMaxValue);
	int GenerateRandomNumber(int aMin, int aMaxValue);
	int RollDice();
	int TableToIndex(const TableOption& table);
	int ResultToIndex(const Result& gameResult);

	void PrintIndexWithColor(const RouletteColor color, const int index);
	void PrintBracketsWithColor(const RouletteColor color, const Side side);
	RouletteColor GetColorFromIndex(const char rouletteLayout[], const int index);
	OddOrEven GetOddOrEvenFromIndex(const int index);
	Columns GetColumnFromIndex(const int index);
	std::string GetStringFromRoulette(const RouletteBetPerType betPerType, const RouletteBetType betType);
	std::string myToString(int value);

}