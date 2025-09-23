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
		int cheatsChoice = ReadIntInRange(1, 4);
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
		case 4:
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

