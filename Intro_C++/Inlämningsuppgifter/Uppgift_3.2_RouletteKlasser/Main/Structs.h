#pragma once
#include "Enums.h"
#include "CONSTANTS.h"
#include <string>

struct Account
{
	int money = CONSTANTS::DEFAULT_MONEY;
	int bet = CONSTANTS::DEFAULT_BET;
	char name[CONSTANTS::NAME_ARRAY_SIZE] = "";
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

struct RouletteBetPerType
{
	int straight = CONSTANTS::ROULETTE_STRAIGHT;
	RouletteColor color = CONSTANTS::ROULETTE_COLOR;
	OddOrEven OddOrEven = CONSTANTS::ROULETTE_ODD_OR_EVEN;
	Columns column = CONSTANTS::ROULETTE_COLUMN;
};

struct Roulette
{
	const char rouletteLayout[CONSTANTS::ROULETTE_ARRAY_SIZE] =
	{ '0',
		'R','B','R',
		'B','R','B',
		'R','B','R',
		'B','B','R',

		'B','R','B',
		'R','B','R',
		'R','B','R',
		'B','R','B',

		'R','B','R',
		'B','B','R',
		'B','R','B',
		'R','B','R',
	};

	RouletteBetType betType = RouletteBetType::None;

	RouletteBetPerType betPerType = {};
	RouletteBetPerType winningType = {};

	std::string betTypeString = "";
	std::string winningBetTypeString = "";
};




