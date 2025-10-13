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

        constexpr int returnIndex = static_cast<int>(InventoryChoice::SpellBook) + RETURN_INDEX_OFFSET;

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

        const int returnIndex = static_cast<int>(equipment.GetEquipment().size()) + RETURN_INDEX_OFFSET;
        std::cout << returnIndex << ") Return\n";

        int menuChoice = Utils::ReadIntInRange(RETURN_INDEX_OFFSET, returnIndex);
        if (menuChoice == returnIndex)
        {
            return;
        }

        const int itemSlotIndex = menuChoice - RETURN_INDEX_OFFSET;
        auto& item = equipment.GetEquipment()[itemSlotIndex];
        std::cout << "\n";
        item->PrintItemOnDisplay();

        std::cout << "\nUnequip item?\n"
            << "1) Yes\n"
            << "2) No\n"
            << "Choice: ";

        auto unequipChoice = static_cast<Choice>(Utils::ReadIntInRange(
            static_cast<int>(Choice::Yes),
            static_cast<int>(Choice::No)));

        if (unequipChoice == Choice::No)
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

        const int returnIndex = static_cast<int>(inventory.GetItems().size()) + RETURN_INDEX_OFFSET;

        int menuChoice = Utils::ReadIntInRange(RETURN_INDEX_OFFSET, returnIndex);

        if (menuChoice == returnIndex)
        {
            return;
        }

        const int itemIndex = menuChoice - RETURN_INDEX_OFFSET;
        const auto& item = inventory.GetItems()[itemIndex];

        if (itemIndex < 0 || itemIndex >= static_cast<int>(inventory.GetItems().size()))
        {
            continue;
        }

        std::cout << "\n";
        item.PrintItemOnDisplay();

        PrintItemActionMenu();

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

        int spellsUnactiveCount = static_cast<int>(spellbook.GetInactiveSpells().size());

        const int returnIndex = spellsUnactiveCount + RETURN_INDEX_OFFSET;
        int menuChoice = Utils::ReadIntInRange(RETURN_INDEX_OFFSET, returnIndex);

        if (menuChoice == returnIndex)
        {
            return;
        }

        const int spellIndex = menuChoice - RETURN_INDEX_OFFSET;
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
