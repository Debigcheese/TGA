#pragma once
#include "Enums.h"

struct Account
{
	int money = 1000;
	int bet = 20;
};

struct BetMultiplier
{
	static constexpr int betMultiGuess = 5;
	static constexpr int betMultiOddOrEven = 2;
	static constexpr int betMultiSpinWheelSmall = 2;
	static constexpr int betMultiSpinWheelBig = 40;
	static constexpr int betMultiHigherOrLower = 3;
};

struct Table
{
	TableOption currentTable = TableOption::Menu;
	int statArr[5];
	int moneyArr[4];
	static constexpr int maxEarnings = 450;
	static constexpr int maxLosses = -150;
	static BetMultiplier betMulti;
};

struct Dice
{
	static constexpr int diceMin = 1;
	static constexpr int diceMax = 6;
};

struct Cards
{
	static constexpr int deckSize = 13;
	const char* cardLabels[deckSize] = { "2","3","4","5","6","7","8","9","10","J","Q","K","A" };
	const int cardValues[deckSize] = { 2,3,4,5,6,7,8,9,10,11,12,13,14 };
	int cardsLeft[deckSize] = { 1,1,1,1,1,1,1,1,1,1,1,1,1 };
};

struct HighOrLowPoints
{
	int currentPoints;
	static constexpr int requiredPoints = 9;
};



