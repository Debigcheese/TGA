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
		int cheatsChoice = ReadIntInRange(1, 3);
		switch (cheatsChoice)
		{
		case 1:
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
		case 2:
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
		case 3:
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
	std::cout
		<< "3) Return\n"
		<< "Choice: ";
}

