#pragma once
#include "Enums.h"

namespace Helpers
{
	int ReadIntInRange(int aMinValue, int aMaxValue);
	int RollDice();
	int TableToIndex(const TableOption& table);
	int ResultToIndex(const Result& gameResult);
}