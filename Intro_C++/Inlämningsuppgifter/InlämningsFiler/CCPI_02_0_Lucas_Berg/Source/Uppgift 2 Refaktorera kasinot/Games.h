#pragma once
#include "Structs.h"
#include "Enums.h"

namespace Games
{
	// Games logic
	void PlayGuessingRound(Account& account, Table& table);
	void PlayOddEvenRound(Account& account, Table& table);
	void PlaySpinWheelRound(Account& account, Table& table);
	void PlayHigherOrLower(Account& account, Table& table);
}