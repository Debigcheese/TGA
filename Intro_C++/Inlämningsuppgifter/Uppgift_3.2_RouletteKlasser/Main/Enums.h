#pragma once

enum class TableOption
{
	Menu = 0,
	GuessingGame = 1,
	OddOrEven = 2,
	SpinTheWheel = 3,
	HighOrLow = 4,
	Roulette = 5,
	Stats = 6,
	Quit = 7,
	Stakes = 8,
};

enum class GameAction
{
	Play = 1,
	ChangeBet = 2,
	ShowRules = 3,
	LeaveTable = 4,
};

enum class Result
{
	Empty = 0,
	Win = 1,
	Loss = -1,
};

enum class CardGuess
{
	Higher = 1,
	Lower = 2,
};

enum class RouletteBetType
{
	None = 0,
	Straight = 1,
	RedBlack = 2,
	OddEven = 3,
	Column = 4,
};

enum class OddOrEven
{
	None = 0,
	Odd = 1,
	Even = 2,
};

enum class Color
{
	None = 0,
	Red = 1,
	Black = 2,
	Green = 3,
};

enum class Columns
{
	None = 0,
	Left = 1,
	Middle = 2,
	Right = 3,
};

enum class Side
{
	None = 0,
	Left = 1,
	Right = 2,
};

enum class Stakes
{
	None = 3,
	Low = 1,
	High = 2,
};
