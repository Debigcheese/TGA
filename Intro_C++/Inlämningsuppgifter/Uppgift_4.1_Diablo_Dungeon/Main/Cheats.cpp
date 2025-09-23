#include "Cheats.h"
#include "Utils.h"
#include <iostream>

using namespace Utils;

namespace { Cheats::CheatState myCheats; }

Cheats::CheatState& Cheats::GetCheats()
{
	return myCheats;
}

void Cheats::UpdateCheats()
{
	while (true)
	{
		system("cls");
		Cheats::PrintCheatMenu();
		int cheatsChoice = ReadIntInRange(static_cast<int>(CheatType::CheatType_Invincible), static_cast<int>(CheatType::CheatType_Ghost));
		CheatType cheatType = static_cast<CheatType>(cheatsChoice);
		switch (cheatType)
		{
		case CheatType::CheatType_Invincible:
		{
			if (!myCheats.invincible)
			{
				myCheats.invincible = true;
			}
			else
			{
				myCheats.invincible = false;
			}
			break;
		}
		case CheatType::CheatType_OneShot:
		{
			if (!myCheats.oneShot)
			{
				myCheats.oneShot = true;
			}
			else
			{
				myCheats.oneShot = false;
			}
			break;
		}
		case CheatType::CheatType_Ghost:
		{
			if (!myCheats.ghost)
			{
				myCheats.ghost = true;
			}
			else
			{
				myCheats.ghost = false;
			}
			break;
		}
		case CheatType::CheatType_None:
		{
			return;
		}
		}
	}
}

void Cheats::PrintCheatMenu()
{
	std::cout
		<< "\n<--- Cheats --->\n";
	if (myCheats.invincible)
	{
		std::cout
			<< PrintRedText(true)
			<< "1) Invincible"
			<< PrintRedText(false)
			<< "\n";
	}
	else
	{
		std::cout
			<< "1) Invincible\n";
	}

	if (myCheats.oneShot)
	{
		std::cout
			<< PrintRedText(true)
			<< "2) One-Shot"
			<< PrintRedText(false)
			<< "\n";
	}
	else
	{
		std::cout
			<< "2) One-Shot\n";
	}

	if (myCheats.ghost)
	{
		std::cout
			<< PrintRedText(true)
			<< "3) Ghost"
			<< PrintRedText(false)
			<< "\n";
	}
	else
	{
		std::cout
			<< "3) Ghost\n";
	}
	std::cout
		<< "4) Return\n"
		<< "Choice: ";
}

