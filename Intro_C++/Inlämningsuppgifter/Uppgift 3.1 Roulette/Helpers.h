#pragma once
#include "Enums.h"
#include "Structs.h"

namespace Helpers
{
	int ReadIntInRange(int aMinValue, int aMaxValue);
	int RollDice();
	int TableToIndex(const TableOption& table);
	int ResultToIndex(const Result& gameResult);
	RouletteColor GetColorFromIndex(const char rouletteLayout[], const int i);
	void PrintIndexWithColor(const RouletteColor color, const int i);
	void PrintBracketsWithColor(const RouletteColor color, const int side);
}