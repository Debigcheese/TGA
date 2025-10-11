#include "PlayerController.h"
#include "WorldMap.h"
#include "Door.h"
#include "Enemy.h"
#include "Utils.h"
#include "Cheats.h"
#include "Item.h"
#include "ConsoleUI.h"

#include <vector>
#include <iostream>
#include <cmath>

using namespace Utils;

PlayerController::PlayerController(WorldMap& aWorldMap, Player& aPlayer)
    : myCurrentRoom(nullptr), myWorldMap(aWorldMap), myPlayer(aPlayer), myCombatController(myPlayer),
      myScavengeController(myPlayer)
{
}

void PlayerController::UpdateAction()
{
    while (true && !myPlayer.IsDead())
    {
        myCurrentRoom = myWorldMap.GetRoomWithId(myPlayer.GetRoomId());
        myPlayer.SetRoomId(myCurrentRoom->GetRoomId());
        ConsoleUI::PrintUI(myPlayer, *myCurrentRoom);

        if (myCurrentRoom->GetEnemies().empty())
        {
            ConsoleUI::PrintActionMenu(false, true);
        }
        else
        {
            ConsoleUI::PrintActionMenu(true, true);
        }

        auto actionChoice = static_cast<Action>(ReadIntInRange(
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
                UpdateNavigation();
                break;
            }
            case Action::LookAround:
            {
                myScavengeController.UpdateScavenge(myCurrentRoom);
                break;
            }
            case Action::Inventory:
            {
                UpdateInventory();
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
                std::cout << "Quitting Game...\n";
                ConsoleUI::Pause();
                return;
            }
            default:
            {
                return;
            }
        }
    }
}

void PlayerController::UpdateNavigation()
{
    while (true && !myPlayer.IsDead())
    {
        ConsoleUI::PrintUI(myPlayer, *myCurrentRoom);
        myWorldMap.PrintMap(myPlayer.GetPosition());
        ConsoleUI::PrintNavigation();

        int navChoice = ReadIntInRange(
            static_cast<int>(Direction::West),
            static_cast<int>(Direction::South) +
            NAV_DIRECTION_CHOICE_OFFSET);

        if (navChoice == static_cast<int>(Direction::South) + NAV_DIRECTION_CHOICE_OFFSET)
        {
            break;
        }

        bool roomFound = false;

        Position lookForPos = myPlayer.GetPosition() + GetPosFromDirection(static_cast<Direction>(navChoice));
        Room* lookForRoom = nullptr;

        for (Room& room : myWorldMap.GetRooms())
        {
            if (lookForPos == room.GetPosition()) // find room position in direction we want to go
            {
                roomFound = true;
                lookForRoom = &room;
            }
        }

        if (!roomFound)
        {
            std::cout << "\nThere is no door in that direction.\n";
            system("pause");
            continue;
        }

        if (!myCurrentRoom->GetEnemies().empty() && !Cheats::GetCheats().ghost)
        {
            std::cout << "You try walking to the door but get attacked!\n\n";
            for (Enemy& enemy : myCurrentRoom->GetEnemies())
            {
                enemy.Attack(myPlayer);
            }
            system("pause");
            break;
        }

        bool doorHasLock = false;
        bool doorFound = false;

        for (Door& door : myWorldMap.GetDoors())
        {
            if (door.HasMatchingRoomIds(
                lookForRoom->GetRoomId(),
                myCurrentRoom->GetRoomId())) // does door exist between my room and look for room
            {
                doorFound = true;
                if (door.HasLock())
                {
                    doorHasLock = true;
                    door.UpdateDoorLock(myPlayer);
                    doorHasLock = door.HasLock();
                }
            }
            if (doorFound && !doorHasLock)
            {
                myPlayer.SetPosition(lookForRoom->GetPosition());
                myPlayer.SetRoomId(lookForRoom->GetRoomId());
                myCurrentRoom = myWorldMap.GetRoomWithId(lookForRoom->GetRoomId());
                break;
            }
        }

        if (doorHasLock)
        {
            ConsoleUI::Pause();
            continue;
        }

        std::cout << "\nEntered room: " << myCurrentRoom->GetRoomName() << "\n";
        std::cout << "You healed to full hp: " << std::round(myPlayer.GetAttributes().currentHealth)
            << " -> " << std::round(myPlayer.GetAttributes().maxHealth) << "\n";
        myPlayer.HealFullHealth();


        if (myWorldMap.GetReachedWinRoom(myPlayer.GetPosition()))
        {
            Win();
            return;
        }
        ConsoleUI::Pause();
        return;
    }
}

void PlayerController::UpdateInventory() const
{
    while (true && !myPlayer.IsDead())
    {
        ConsoleUI::PrintUI(myPlayer, *myCurrentRoom);
        ConsoleUI::PrintInventoryMenu();

        constexpr int equipmentIndex = 1;
        constexpr int returnIndex = 4;

        int menuChoice = ReadIntInRange(equipmentIndex, returnIndex);

        if (menuChoice == returnIndex)
        {
            return;
        }

        switch (menuChoice)
        {
            case 1:
            {
                UpdateEquipment();
                break;
            }
            case 2:
            {
                UpdateInventoryItems();
                break;
            }
            case 3:
            {
                UpdateSpellBook();
                break;
            }
        }
    }
}

void PlayerController::UpdateEquipment() const
{
    while (true && !myPlayer.IsDead())
    {
        ConsoleUI::PrintUI(myPlayer, *myCurrentRoom);

        const auto& equipment = myPlayer.GetEquipment();
        equipment.PrintEquipment();

        constexpr int offsetIndex = 1;
        const int returnIndex = static_cast<int>(equipment.GetEquipment().size()) + offsetIndex;

        std::cout << returnIndex << ") Return\n";

        int menuChoice = ReadIntInRange(offsetIndex, returnIndex);

        if (menuChoice == returnIndex)
        {
            return;
        }
        const int itemSlotIndex = menuChoice - offsetIndex;
        auto& item = equipment.GetEquipment()[itemSlotIndex];
        std::cout << "\n";
        item->PrintItemOnDisplay();

        std::cout << "\nUnequip item?\n"
            << "1) Yes\n"
            << "2) No\n"
            << "Choice: ";

        int unequipChoice = ReadIntInRange(1, 2);

        if (unequipChoice == 2)
        {
            return;
        }

        myPlayer.UnequipItem(itemSlotIndex);
        ConsoleUI::Pause();
    }
}

void PlayerController::UpdateInventoryItems() const
{
    while (true && !myPlayer.IsDead())
    {
        ConsoleUI::PrintUI(myPlayer, *myCurrentRoom);
        const auto& inventory = myPlayer.GetInventory();
        inventory.PrintInventory(myPlayer.GetAttributes().carryCapacity);

        constexpr int offsetIndex = 1;
        const int returnIndex = static_cast<int>(inventory.GetItems().size()) + offsetIndex;

        int menuChoice = ReadIntInRange(offsetIndex, returnIndex);

        if (menuChoice == returnIndex)
        {
            return;
        }

        const int itemIndex = menuChoice - offsetIndex;
        const auto& item = inventory.GetItems()[itemIndex];

        if (itemIndex < 0 || itemIndex >= static_cast<int>(inventory.GetItems().size()))
        {
            continue;
        }

        std::cout << "\n";
        item.PrintItemOnDisplay();

        std::cout << "\nItem Action\n"
            << "1) Equip\n"
            << "2) Drop\n"
            << "3) Return\n"
            << "Choice: ";

        menuChoice = ReadIntInRange(static_cast<int>(ItemAction::Equip), static_cast<int>(ItemAction::Count));
        auto itemAction = static_cast<ItemAction>(menuChoice);

        switch (itemAction)
        {
            case ItemAction::Equip:
            {
                if (myPlayer.GetEquipment().CanEquipItem(item))
                {
                    myPlayer.EquipItem(item.GetId());
                }
                else
                {
                    std::cout << "\nCan't equip item if item slot is occupied!\n";
                }
                break;
            }
            case ItemAction::Drop:
            {
                myCurrentRoom->AddItemToRoom(item);
                myPlayer.DropItem(item.GetId());
                break;
            }
            default:
            {
                return;
            }
        }
        ConsoleUI::Pause();
    }
}

void PlayerController::UpdateSpellBook() const
{
    while (true && !myPlayer.IsDead())
    {
        ConsoleUI::PrintUI(myPlayer, *myCurrentRoom);

        const auto& spellbook = myPlayer.GetSpellBook();
        spellbook.PrintSpells();

        constexpr int offsetIndex = 1;
        int spellsUnactiveCount = static_cast<int>(spellbook.GetInactiveSpells().size());

        const int returnIndex = spellsUnactiveCount + offsetIndex;
        int menuChoice = ReadIntInRange(offsetIndex, returnIndex);

        if (menuChoice == returnIndex)
        {
            return;
        }

        const int spellIndex = menuChoice - offsetIndex;
        if (spellIndex < 0 || spellIndex >= spellsUnactiveCount)
        {
            continue;
        }
        const Spell* spell = spellbook.GetInactiveSpells()[spellIndex];
        const int spellId = spell->GetId();

        std::cout << "\nRead spell?\n"
            << "1) Yes\n"
            << "2) No\n"
            << "Choice: ";

        int spellChoiceInt = ReadIntInRange(static_cast<int>(Choice::Yes), static_cast<int>(Choice::No));
        auto spellChoice = static_cast<Choice>(spellChoiceInt);

        if (spellChoice == Choice::No)
        {
            return;
        }
        myPlayer.ActivateSpell(spellId);
        ConsoleUI::Pause();
    }
}

void PlayerController::UpdateAttributes() const
{
    while (true)
    {
        ConsoleUI::PrintUI(myPlayer, *myCurrentRoom);

        std::cout
            << "\n<--- Attributes --->\n"
            << "1) Starting Attributes\n"
            << "2) Buffed Attributes\n"
            << "3) Return\n"
            << "Choice: ";

        auto menuChoice = static_cast<AttriMenu>(ReadIntInRange(
            static_cast<int>(AttriMenu::Attributes),
            static_cast<int>(AttriMenu::Return)));

        if (menuChoice == AttriMenu::Return)
        {
            return;
        }

        system("cls");
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
        system("pause");
        return;
    }
}

void PlayerController::Win() const
{
    ConsoleUI::PrintPlayerWin(myPlayer);
    ConsoleUI::Pause();
    myPlayer.SetIsDead(true);
}
