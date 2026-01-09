#pragma once

namespace CONSTANTS
{
	//Account
	const int DEFAULT_MONEY = 555000;
	const int DEFAULT_BET = 1000;

	//CASINO
	const TableOption DEFAULT_TABLE = TableOption::TableOption_Menu;
	const Stakes DEFAULT_STAKES = Stakes::Stakes_None;
	const int STAT_ARRAY_SIZE = 5;
	const int EARNINGS_MAX = 30000;
	const int LOSSES_MAX = -20000;
	const int NAME_ARRAY_SIZE = 18;
	const int NAME_SIZE_MIN = 2;
	const int NAME_SIZE_MAX = 16;
	const int ZERO_INDEX = 0;
	const int ENUM_TO_INDEX_OFFSET = 1;

	// PAYOUT
	const int BET_MULTI_GUESS = 5;
	const int BET_MULTI_ODD_OR_EVEN = 2;
	const int BET_MULTI_SPIN_WHEEL_SMALL = 2;
	const int BET_MULTI_SPIN_WHEEL_BIG = 40;
	const int BET_MULTI_HIGHER_OR_LOWER = 3;
	const int BET_MULTI_ROULETTE_STRAIGHT = 36;
	const int BET_MULTI_ROULETTE_COLOR = 1;
	const int BET_MULTI_ROULETTE_ODDOREVEN = 1;
	const int BET_MULTI_ROULETTE_COLUMN = 3;

	//GUESSING GAME STAKE
	const int GUESSING_GAME_STAKE_LOW_MIN = 1;
	const int GUESSING_GAME_STAKE_LOW_MAX = 1000;
	const int GUESSING_GAME_STAKE_HIGH_MIN = 1000;
	const int GUESSING_GAME_STAKE_HIGH_MAX = 100000;

	//ODD OR EVEN
	const int EVEN_DIVISOR = 2;
	const int REMAINDER_ODD = 1;
	const int REMAINDER_EVEN = 0;

	//SPIN THE WHEEL
	const int SPIN_THE_WHEEL_DEFAULT_VALUE_PLAY = 1;

	//HIGHER OR LOWER 
	const int DECK_SIZE = 13;
	const int DECK_SIZE_TO_INDEX_OFFSET = 1;
	const int REQUIRED_POINTS = 9;
	const int CURRENT_POINTS = 0;

	// ROULETTE
	const int ROULETTE_ARRAY_SIZE = 37;
	const int ROULETTE_SIZE_TO_INDEX_OFFSET = 1;
	const int COLUMN_TOTAL_AMOUNT = 3;
	const int ROULETTE_STRAIGHT = 0;
	const int ROULETTE_BOARD_SINGLE_DIGIT_THRESHOLD = 10;
	const RouletteColor ROULETTE_COLOR = RouletteColor::RouletteColor_Black;
	const OddOrEven ROULETTE_ODD_OR_EVEN = OddOrEven::OddOrEven_Odd;
	const Columns ROULETTE_COLUMN = Columns::Columns_Middle;
	const int COLUMN_LEFT_REMAINDER = 1;
	const int COLUMN_MIDDLE_REMAINDER = 2;
	const int COLUMN_RIGHT_REMAINDER = 0;

	//HELPERS
	const int DICE_MIN = 1;
	const int DICE_MAX = 6;
	const int MY_TO_STRING_BUFFER_SIZE = 12;
	const int MY_TO_STRING_INDEX = 11;
	const int MY_TO_STRING_DECIMAL_BASE = 10;

}