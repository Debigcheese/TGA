#pragma once

namespace CONSTANTS
{
	//Account
	const int DEFAULT_MONEY = 55000;
	const int DEFAULT_BET = 1000;

	//Per Table
	const TableOption DEFAULT_TABLE = TableOption::Menu;
	const int STAT_ARRAY_SIZE = 5;
	const int MONEY_ARRAY_SIZE = 5;
	const int EARNINGS_MAX = 30000;
	const int LOSSES_MAX = -20000;
	const int DICE_MIN = 1;
	const int DICE_MAX = 6;

	// SPIN THE WHEEL PAYOUT
	const int BET_MULTI_GUESS = 5;
	const int BET_MULTI_ODD_OR_EVEN = 2;
	const int BET_MULTI_SPIN_WHEEL_SMALL = 2;
	const int BET_MULTI_SPIN_WHEEL_BIG = 40;
	const int BET_MULTI_HIGHER_OR_LOWER = 3;

	//HIGHER OR LOWER PAYOUT
	const int DECK_SIZE = 13;
	const int REQUIRED_POINTS = 9;
	const int CURRENT_POINTS = 0;

	// ROULETTE
	const int ROULETTE_ARRAY_SIZE = 37;
	const int COLUMN_TOTAL_AMOUNT = 3;
	const int ROULETTE_STRAIGHT = 0;
	const int ROULETTE_BOARD_SINGLE_DIGIT_THRESHOLD = 10;
	const RouletteColor ROULETTE_COLOR = RouletteColor::Black;
	const OddOrEven ROULETTE_ODD_OR_EVEN = OddOrEven::Odd;
	const Columns ROULETTE_COLUMN = Columns::Middle;

	// ROULETTE PAYOUT
	const int BET_MULTI_ROULETTE_STRAIGHT = 36;
	const int BET_MULTI_ROULETTE_COLOR = 1;
	const int BET_MULTI_ROULETTE_ODDOREVEN = 1;
	const int BET_MULTI_ROULETTE_COLUMN = 3;

	//MY_TO_STRING
	const int MY_TO_STRING_BUFFER_SIZE = 12;
	const int MY_TO_STRING_INDEX = 11;
	const int MY_TO_STRING_DECIMAL_BASE = 10;

}