#pragma once

namespace CONSTANTS
{
	//Account
	static const int DEFAULT_MONEY = 55000;
	static const int DEFAULT_BET = 1000;

	//Per Table
	static const TableOption DEFAULT_TABLE = TableOption::Menu;
	static const int STAT_ARRAY_SIZE = 5;
	static const int MONEY_ARRAY_SIZE = 5;
	static const int EARNINGS_MAX = 30000;
	static const int LOSSES_MAX = -20000;
	static const int DICE_MIN = 1;
	static const int DICE_MAX = 6;

	// SPIN THE WHEEL PAYOUT
	static const int BET_MULTI_GUESS = 5;
	static const int BET_MULTI_ODD_OR_EVEN = 2;
	static const int BET_MULTI_SPIN_WHEEL_SMALL = 2;
	static const int BET_MULTI_SPIN_WHEEL_BIG = 40;
	static const int BET_MULTI_HIGHER_OR_LOWER = 3;

	//HIGHER OR LOWER PAYOUT
	static const int DECK_SIZE = 13;
	static const int REQUIRED_POINTS = 9;
	static const int CURRENT_POINTS = 0;

	// ROULETTE
	static const int ROULETTE_ARRAY_SIZE = 37;
	static const int COLUMN_TOTAL_AMOUNT = 3;
	static const int ROULETTE_STRAIGHT = 0;
	static const RouletteColor ROULETTE_COLOR = RouletteColor::Black;
	static const OddOrEven ROULETTE_ODD_OR_EVEN = OddOrEven::Odd;
	static const Columns ROULETTE_COLUMN = Columns::Middle;

	// ROULETTE PAYOUT
	static const int BET_MULTI_ROULETTE_STRAIGHT = 36;
	static const int BET_MULTI_ROULETTE_COLOR = 2;
	static const int BET_MULTI_ROULETTE_ODDOREVEN = 2;
	static const int BET_MULTI_ROULETTE_COLUMN = 3;

}