#include "LoadoutController.h"
#include "Player.h"
#include "Utils.h"
#include "Item.h"
#include "ConsoleUI.h"

#include <vector>
#include <iostream>

using namespace ConsoleUI;

enum class InventoryChoice
{
    Equipment = 1,
    Inventory = 2,
    SpellBook = 3
};

LoadoutController::LoadoutController(Player& aPlayer)
    : myPlayer(aPlayer), myCurrentRoom(nullptr)
{
}

void LoadoutController::UpdateLoadout(Room* aCurrentRoom)
{
    myCurrentRoom = aCurrentRoom;
    while (true && !myPlayer.IsDead())
    {
        PrintUI(myPlayer, *myCurrentRoom);
        PrintInventoryMenu();

        constexpr int returnIndex = static_cast<int>(InventoryChoice::SpellBook) + 1;

        auto choiceIndex = Utils::ReadIntInRange(
            static_cast<int>(InventoryChoice::Equipment),
            returnIndex);

        if (choiceIndex == returnIndex)
        {
            return;
        }

        auto choice = static_cast<InventoryChoice>(choiceIndex);

        switch (choice)
        {
            case InventoryChoice::Equipment:
            {
                UpdateEquipment();
                break;
            }
            case InventoryChoice::Inventory:
            {
                UpdateInventory();
                break;
            }
            case InventoryChoice::SpellBook:
            {
                UpdateSpellBook();
                break;
            }
        }
    }
}

void LoadoutController::UpdateEquipment() const
{
    while (true && !myPlayer.IsDead())
    {
        PrintUI(myPlayer, *myCurrentRoom);

        const auto& equipment = myPlayer.GetEquipment();
        equipment.PrintEquipment();

        constexpr int offsetIndex = 1;
        const int returnIndex = static_cast<int>(equipment.GetEquipment().size()) + offsetIndex;

        std::cout << returnIndex << ") Return\n";

        int menuChoice = Utils::ReadIntInRange(offsetIndex, returnIndex);

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

        int unequipChoice = Utils::ReadIntInRange(1, 2);

        if (unequipChoice == 2)
        {
            return;
        }

        myPlayer.UnequipItem(itemSlotIndex);
        Pause();
    }
}

void LoadoutController::UpdateInventory() const
{
    while (true && !myPlayer.IsDead())
    {
        PrintUI(myPlayer, *myCurrentRoom);
        const auto& inventory = myPlayer.GetInventory();
        inventory.PrintInventory(myPlayer.GetAttributes().carryCapacity);

        constexpr int offsetIndex = 1;
        const int returnIndex = static_cast<int>(inventory.GetItems().size()) + offsetIndex;

        int menuChoice = Utils::ReadIntInRange(offsetIndex, returnIndex);

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

        menuChoice = Utils::ReadIntInRange(static_cast<int>(ItemAction::Equip), static_cast<int>(ItemAction::Count));
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
        Pause();
    }
}

void LoadoutController::UpdateSpellBook() const
{
    while (true && !myPlayer.IsDead())
    {
        PrintUI(myPlayer, *myCurrentRoom);

        const auto& spellbook = myPlayer.GetSpellBook();
        spellbook.PrintSpells();

        constexpr int offsetIndex = 1;
        int spellsUnactiveCount = static_cast<int>(spellbook.GetInactiveSpells().size());

        const int returnIndex = spellsUnactiveCount + offsetIndex;
        int menuChoice = Utils::ReadIntInRange(offsetIndex, returnIndex);

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
        myPlayer.ActivateSpell(spellId);
        Pause();
    }
}
