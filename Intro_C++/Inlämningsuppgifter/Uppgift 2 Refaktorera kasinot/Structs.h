#pragma once
#include "Enums.h"

struct Account
{
	int money = 1000;
	int bet = 20;
};

struct BetMultiplier
{
	int betMultiGuess = 5;
	int betMultiOddOrEven = 2;
	int betMultiSpinWheelSmall = 2;
	int betMultiSpinWheelBig = 40;
};

struct Table
{
	TableOption currentTable = TableOption::Menu;
	int statArr[5];
	int moneyArr[3];
	int maxEarnings = 450;
	int maxLosses = -150;
	BetMultiplier betMulti;
};
