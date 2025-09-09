#pragma once

enum class TableOption
{
	Menu = 0,
	GuessingGame = 1,
	OddOrEven = 2,
	SpinTheWheel = 3,
	Stats = 4,
	Quit = 5,
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
