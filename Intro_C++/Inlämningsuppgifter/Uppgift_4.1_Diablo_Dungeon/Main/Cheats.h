#pragma once
#include "GameStructs.h"

namespace Cheats
{
	struct CheatState
	{
		bool invincible = false;
		bool oneShot = false;
	};

	void UpdateCheats();
	void PrintCheatMenu();
	CheatState& GetCheats();
}