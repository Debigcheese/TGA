#pragma once

namespace CONSTANTS
{
	//Account
	static const int DEFAULT_MONEY = 55000;
	static const int DEFAULT_BET = 1000;

	//CASINO
	static const TableOption DEFAULT_TABLE = TableOption::Menu;
	static const Stakes DEFAULT_STAKES = Stakes::None;
	static const int STAT_ARRAY_SIZE = 5;
	static const int EARNINGS_MAX = 30000;
	static const int LOSSES_MAX = -20000;
	static const int NAME_ARRAY_SIZE = 17;
	static const int NAME_SIZE_MIN = 2;
	static const int NAME_SIZE_MAX = 16;

	// PAYOUT
	static const int BET_MULTI_GUESS = 5;
	static const int BET_MULTI_ODD_OR_EVEN = 2;
	static const int BET_MULTI_SPIN_WHEEL_SMALL = 2;
	static const int BET_MULTI_SPIN_WHEEL_BIG = 40;
	static const int BET_MULTI_HIGHER_OR_LOWER = 3;
	static const int BET_MULTI_ROULETTE_STRAIGHT = 36;
	static const int BET_MULTI_ROULETTE_COLOR = 1;
	static const int BET_MULTI_ROULETTE_ODDOREVEN = 1;
	static const int BET_MULTI_ROULETTE_COLUMN = 3;

	//ODD OR EVEN
	static const int GUESSING_GAME_STAKE_LOW_MIN = 1;
	static const int GUESSING_GAME_STAKE_LOW_MAX = 1000;
	static const int GUESSING_GAME_STAKE_HIGH_MIN = 1000;
	static const int GUESSING_GAME_STAKE_HIGH_MAX = 100000;

	//ODD OR EVEN
	static const int EVEN_DIVISOR = 2;
	static const int REMAINDER_ODD = 1;

	//HIGHER OR LOWER 
	static const int DECK_SIZE = 13;
	static const int REQUIRED_POINTS = 9;
	static const int CURRENT_POINTS = 0;

	// ROULETTE
	static const int ROULETTE_ARRAY_SIZE = 37;
	static const int COLUMN_TOTAL_AMOUNT = 3;
	static const int ROULETTE_STRAIGHT = 0;
	static const int ROULETTE_BOARD_SINGLE_DIGIT_THRESHOLD = 10;
	static const RouletteColor ROULETTE_COLOR = RouletteColor::Black;
	static const OddOrEven ROULETTE_ODD_OR_EVEN = OddOrEven::Odd;
	static const Columns ROULETTE_COLUMN = Columns::Middle;

	//HELPERS
	static const int DICE_MIN = 1;
	static const int DICE_MAX = 6;
	static const int MY_TO_STRING_BUFFER_SIZE = 12;
	static const int MY_TO_STRING_INDEX = 11;
	static const int MY_TO_STRING_DECIMAL_BASE = 10;

}