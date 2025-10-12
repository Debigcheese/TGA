#include "PlayerController.h"
#include "Player.h"
#include "WorldMap.h"
#include "Utils.h"
#include "Cheats.h"
#include "ConsoleUI.h"

#include <vector>

PlayerController::PlayerController(WorldMap& aWorldMap, Player& aPlayer)
	: myCurrentRoom(nullptr), myWorldMap(aWorldMap), myPlayer(aPlayer), myCombatController(myPlayer),
	  myScavengeController(myPlayer), myLoadoutController(myPlayer), myNavController(myWorldMap, myPlayer)
{
}

void PlayerController::UpdateAction()
{
	while (true && !myPlayer.IsDead())
	{
		myCurrentRoom = myWorldMap.GetRoomWithId(myPlayer.GetRoomId());
		myPlayer.SetRoomId(myCurrentRoom->GetRoomId());

		if (IsInFinalRoom())
		{
			Win();
			return;
		}

		ConsoleUI::PrintUI(myPlayer, *myCurrentRoom);
		ConsoleUI::PrintActionMenu(myCurrentRoom);

		auto actionChoice = static_cast<Action>(Utils::ReadIntInRange(
			static_cast<int>(Action::Combat),
			static_cast<int>(Action::Quit)));

		switch (actionChoice)
		{
			case Action::Combat:
			{
				myCombatController.UpdateCombat(myCurrentRoom);
				break;
			}
			case Action::Navigation:
			{
				myNavController.UpdateNavigation(myCurrentRoom);
				break;
			}
			case Action::LookAround:
			{
				myScavengeController.UpdateScavenge(myCurrentRoom);
				break;
			}
			case Action::Inventory:
			{
				myLoadoutController.UpdateLoadout(myCurrentRoom);
				break;
			}
			case Action::Attributes:
			{
				UpdateAttributes();
				break;
			}
			case Action::Cheats:
			{
				Cheats::UpdateCheats();
				break;
			}
			case Action::Quit:
			{
				ConsoleUI::PrintQuitGame();
				ConsoleUI::Pause();
				return;
			}
			default:
			{
				break;
			}
		}
	}
}

void PlayerController::UpdateAttributes() const
{
	while (true)
	{
		ConsoleUI::PrintUI(myPlayer, *myCurrentRoom);
		ConsoleUI::PrintAttributesMenu();

		auto menuChoice = static_cast<AttriMenu>(Utils::ReadIntInRange(
			static_cast<int>(AttriMenu::Attributes),
			static_cast<int>(AttriMenu::Return)));

		if (menuChoice == AttriMenu::Return)
		{
			return;
		}

		ConsoleUI::Clear();
		myPlayer.PrintPlayerUI();
		myCurrentRoom->PrintEnemies();

		switch (menuChoice)
		{
			case AttriMenu::Attributes:
			{
				myPlayer.PrintDerivedAttributes();
				break;
			}
			case AttriMenu::DerivedAttributes:
			{
				myPlayer.PrintAttributes();
				break;
			}
			case AttriMenu::Return:
			{
				return;
			}
		}
		ConsoleUI::Pause();
		return;
	}
}

bool PlayerController::IsInFinalRoom() const
{
	return myWorldMap.GetReachedWinRoom(myPlayer.GetPosition());
}

void PlayerController::Win() const
{
	ConsoleUI::PrintPlayerWin(myPlayer);
	ConsoleUI::Pause();
	myPlayer.SetIsDead(true);
}
