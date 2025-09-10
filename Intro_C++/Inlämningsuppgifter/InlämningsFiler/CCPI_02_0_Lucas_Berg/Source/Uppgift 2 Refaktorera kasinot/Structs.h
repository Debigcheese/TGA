#pragma once
#include "Enums.h"
#include "CONSTANTS.h"

struct Account
{
	int money = CONSTANTS::DEFAULT_MONEY;
	int bet = CONSTANTS::DEFAULT_BET;
};

struct Table
{
	TableOption currentTable = CONSTANTS::DEFAULT_TABLE;
	int statArr[CONSTANTS::STAT_ARRAY_SIZE];
	int moneyArr[CONSTANTS::MONEY_ARRAY_SIZE];
};

struct Cards
{
	const char* cardLabels[CONSTANTS::DECK_SIZE] = { "2","3","4","5","6","7","8","9","10","J","Q","K","A" };
	const int cardValues[CONSTANTS::DECK_SIZE] = { 2,3,4,5,6,7,8,9,10,11,12,13,14 };
	int cardsLeft[CONSTANTS::DECK_SIZE] = { 1,1,1,1,1,1,1,1,1,1,1,1,1 };
};

struct HighOrLowPoints
{
	int currentPoints = CONSTANTS::CURRENT_POINTS;
	const int requiredPoints = CONSTANTS::REQUIRED_POINTS;
};



