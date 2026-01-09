#include "Cheats.h"
#include "Utils.h"
#include <iostream>

using namespace Utils;

namespace
{
	Cheats::CheatState myCheats;
}

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
		CheatType cheatType = static_cast<CheatType>(ReadIntInRange(static_cast<int>(CheatType::Invincible),
		                                                            static_cast<int>(CheatType::None)));
		switch (cheatType)
		{
			case CheatType::Invincible:
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
			case CheatType::OneShot:
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
			case CheatType::Ghost:
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
			case CheatType::None:
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
			<< GetColorCode(TextColor::Red, true)
			<< "1) Invincible"
			<< GetColorCode(TextColor::Red, false)
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
			<< GetColorCode(TextColor::Red, true)
			<< "2) One-Shot"
			<< GetColorCode(TextColor::Red, false)
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
			<< GetColorCode(TextColor::Red, true)
			<< "3) Ghost"
			<< GetColorCode(TextColor::Red, false)
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
