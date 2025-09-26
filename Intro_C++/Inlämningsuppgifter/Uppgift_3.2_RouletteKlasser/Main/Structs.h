#pragma once
#include "Enums.h"
#include <string>

struct Account
{
	int money;
	int bet;
};


struct HighOrLowPoints
{
	int currentPoints;
	int requiredPoints;
};

struct RouletteBetPerType
{
	int straight;
	Color color;
	OddOrEven oddOrEven;
	Columns column;
};

struct Roulette
{
	RouletteBetType betType;

	RouletteBetPerType betPerType;
	RouletteBetPerType winningType;

	std::string betTypeString;
	std::string winningBetTypeString;
};
