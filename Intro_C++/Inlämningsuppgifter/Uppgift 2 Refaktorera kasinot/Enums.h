#pragma once

enum class TableOption
{
	Menu = 0,
	GuessingGame = 1,
	OddOrEven = 2,
	SpinTheWheel = 3,
	HighOrLow = 4,
	Stats = 5,
	Quit = 6,
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



