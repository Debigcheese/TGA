#pragma once

enum class TableOption
{
	TableOption_Menu = 0,
	TableOption_GuessingGame = 1,
	TableOption_OddOrEven = 2,
	TableOption_SpinTheWheel = 3,
	TableOption_HighOrLow = 4,
	TableOption_Roulette = 5,
	TableOption_Stats = 6,
	TableOption_Quit = 7,
	TableOption_Stakes = 8,
};

enum class GameAction
{
	GameAction_Play = 1,
	GameAction_ChangeBet = 2,
	GameAction_ShowRules = 3,
	GameAction_LeaveTable = 4,
};

enum class Result
{
	Result_Empty = 0,
	Result_Win = 1,
	Result_Loss = -1,
};

enum class CardGuess
{
	CardGuess_Higher = 1,
	CardGuess_Lower = 2,
};

enum class RouletteBetType
{
	RouletteBetType_None = 0,
	RouletteBetType_Straight = 1,
	RouletteBetType_RedBlack = 2,
	RouletteBetType_OddEven = 3,
	RouletteBetType_Column = 4,
};

enum class OddOrEven
{
	OddOrEven_None = 0,
	OddOrEven_Odd = 1,
	OddOrEven_Even = 2,
};

enum class RouletteColor
{
	RouletteColor_None = 0,
	RouletteColor_Red = 1,
	RouletteColor_Black = 2,
};

enum class Columns
{
	Columns_None = 0,
	Columns_Left = 1,
	Columns_Middle = 2,
	Columns_Right = 3,
};

enum class Side
{
	Side_None = 0,
	Side_Left = 1,
	Side_Right = 2,
};

enum class Stakes
{
	Stakes_None = 3,
	Stakes_Low = 1,
	Stakes_High = 2,

};



