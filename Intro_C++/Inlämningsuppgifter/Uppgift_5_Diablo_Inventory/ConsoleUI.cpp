#include "ConsoleUI.h"
#include "Utils.h"
#include "Player.h"
#include "Spell.h"

#include <iostream>
#include <cstdlib>

using namespace Utils;

namespace ConsoleUI
{
    void Clear()
    {
        system("cls");
    }

    void Pause()
    {
        system("pause");
    }

    void PrintUI(const Player& aPlayer, const Room* aCurrentRoom)
    {
        Clear();
        PrintPlayerUI(aPlayer, aCurrentRoom);
        aCurrentRoom->PrintEnemies();
    }

    void PrintNavigationMenu()
    {
        std::cout
            << "\n<--- Navigation --->\n"
            << "1) West\n"
            << "2) North\n"
            << "3) East\n"
            << "4) South\n"
            << "5) Return\n"
            << "Choice: ";
    }

    void PrintActionMenu(Room* aCurrentRoom)
    {
        std::cout << "\n<--- Action --->\n";
        if (aCurrentRoom->GetEnemies().empty())
        {
            std::cout << "1) Combat (No Enemies Nearby)\n";
        }
        else
        {
            std::cout << "1) Combat\n";
        }

        std::cout
            << "2) Navigate\n"
            << "3) Scavenge\n"
            << "4) Inventory\n"
            << "\n<--- Other --->\n"
            << "5) Attributes\n"
            << "6) Cheats\n"
            << "7) Quit Game\n"
            << "Choice: ";
    }

    void PrintPlayerWin(const Player& aPlayer)
    {
        std::cout << "\nYou reached the last room (" << aPlayer.GetName() << ")!\n";
        std::cout << "Closing game...\n";
    }

    void PrintScavengeMenu()
    {
        std::cout
            << "\n<--- Scavenge --->\n"
            << "1) Floor\n"
            << "2) Chests\n"
            << "3) Spells\n"
            << "4) Return\n"
            << "Choice: ";
    }

    void PrintPickupMenu(const std::vector<Item>& aItems)
    {
        std::cout << "\n<--- Pickup --->\n";

        if (aItems.empty())
        {
            std::cout << "(No loot here...)\n";
            return;
        }

        for (int i = 0; i < static_cast<int>(aItems.size()); ++i)
        {
            std::cout << (i + 1) << ") ";
            aItems[i].PrintItemOnDisplay();
            std::cout << "\n";
        }

        std::cout << static_cast<int>(aItems.size()) + 1 << ") Return\n"
            << "Choice: ";
    }

    void PrintChestMenu(const std::vector<Chest>& aChests)
    {
        std::cout << "\n<--- Open Chest --->\n";

        if (aChests.empty())
        {
            std::cout << "(No chests here...)\n";
            return;
        }

        for (int i = 0; i < static_cast<int>(aChests.size()); ++i)
        {
            std::cout << (i + 1) << ") "
                << "|" << aChests[i].GetName() << "|" << "\n";
        }

        std::cout << static_cast<int>(aChests.size()) + 1 << ") Return\n"
            << "Choice: ";
    }

    void PrintSpellBookMenu(const std::vector<Spell>& aSpells)
    {
        std::cout << "\n<--- Pickup spell --->\n";

        if (aSpells.empty())
        {
            std::cout << "(No spells here...)\n";
            return;
        }

        const int count = static_cast<int>(aSpells.size());
        for (int i = 0; i < count; ++i)
        {
            std::cout << (i + 1) << ") ";
            aSpells[i].PrintSpellOnDisplay();
            std::cout << "\n";
        }

        std::cout << count + 1 << ") Return\n"
            << "Choice: ";
    }

    void PrintItemActionMenu()
    {
        std::cout << "\nItem Action\n"
            << "1) Equip\n"
            << "2) Drop\n"
            << "3) Return\n"
            << "Choice: ";
    }

    void PrintInventoryMenu()
    {
        std::cout
            << "\n<--- Inventory --->\n"
            << "1) Equipment\n"
            << "2) Items\n"
            << "3) Spells\n"
            << "4) Return\n"
            << "Choice: ";
    }

    void PrintAttributesMenu()
    {
        std::cout
            << "\n<--- Attributes --->\n"
            << "1) Starting Attributes\n"
            << "2) Buffed Attributes\n"
            << "3) Return\n"
            << "Choice: ";
    }

    void PrintQuitGame()
    {
        std::cout << "Quitting Game...\n";
    }

    void PrintMap(const Position& aPlayerPos, const Position aWinPosition)
    {
        constexpr int minX = -2, maxX = 2;
        constexpr int minY = -1, maxY = 3;

        std::cout << '\n';
        for (int y = maxY; y >= minY; --y)
        {
            for (int x = minX; x <= maxX; ++x)
            {
                if (!WorldMap::HasRoom(x, y))
                {
                    std::cout << "   ";
                    continue;
                }
                if (aWinPosition == Position{x, y})
                {
                    std::cout << "[X]";
                }
                else
                {
                    std::cout << ((aPlayerPos.X == x && aPlayerPos.Y == y) ? "[O]" : "[ ]");
                }
            }
            std::cout << '\n';
        }
    }

    void PrintUserName(const Player& aPlayer)
    {
        std::cout << "Username: " << aPlayer.GetName();
    }


    void PrintPlayerUI(const Player& aPlayer, const Room* aCurrentRoom)
    {
        Clear();
        //Username
        PrintUserName(aPlayer);
        //Health
        std::cout << "Health: "
            << static_cast<int>(aPlayer.GetAttributes().currentHealth) << "/"
            << static_cast<int>(aPlayer.GetAttributes().maxHealth) << " hp" << "\n";
	
        std::cout << "Room: " << aCurrentRoom->GetRoomName() << "\n";
    }
    
    
    //prints attributes after items + buffs
    void PrintAttributes(const Player& aPlayer)
    {
        std::cout << "Player Username: " << aPlayer.GetName() << "\n\n";

        std::cout << "[Base Attributes] " << "\n";
        std::cout << "Strength:  " << static_cast<int>(aPlayer.GetAttributes().strength) << "/99" << "\n";
        std::cout << "Agility:   " << static_cast<int>(aPlayer.GetAttributes().agility) << "/99" << "\n";
        std::cout << "Endurance: " << static_cast<int>(aPlayer.GetAttributes().endurance) << "/99" << "\n\n";

        std::cout << "[Derived Attributes] " << "\n";
        std::cout << "Attack Damage: " << static_cast<int>(aPlayer.GetAttributes().damage) << " AD" << "\n";
        std::cout << "Max-Health :   " << static_cast<int>(aPlayer.GetAttributes().maxHealth) << " hp" << "\n";
        std::cout << "Defense:       " << static_cast<int>(aPlayer.GetAttributes().defense) << " def" << "\n";
        std::cout << "Carry Capacity: " << static_cast<int>(aPlayer.GetAttributes().carryCapacity) << "kg" << "\n\n";
    }

    
    void PrintBaseAttributes(const Player& aPlayer)
    {
        std::cout << "Player Username: " << aPlayer.GetName() << "\n\n";

        std::cout << "[Base Attributes] " << "\n";
        std::cout << "Strength:  " << static_cast<int>(aPlayer.GetBaseAttributes().strength) << "/99" << "\n";
        std::cout << "Agility:   " << static_cast<int>(aPlayer.GetBaseAttributes().agility) << "/99" << "\n";
        std::cout << "Endurance: " << static_cast<int>(aPlayer.GetBaseAttributes().endurance) << "/99" << "\n\n";

        std::cout << "[Derived Attributes] " << "\n";
        std::cout << "Attack Damage: " << static_cast<int>(aPlayer.GetBaseAttributes().damage) << " AD" << "\n";
        std::cout << "Max-Health :   " << static_cast<int>(aPlayer.GetBaseAttributes().maxHealth) << " hp" << "\n";
        std::cout << "Defense:       " << static_cast<int>(aPlayer.GetBaseAttributes().defense) << " def" << "\n";
        std::cout << "Carry Capacity: " << static_cast<int>(aPlayer.GetBaseAttributes().carryCapacity) << "kg" << "\n\n";
    }

    //prints base attributes + derived calculation
    void PrintDerivedAttributes(const Player& aPlayer)
    {
        std::cout << "Player Username: " << aPlayer.GetName() << "\n\n";

        std::cout << "[Base Attributes] " << "\n";
        std::cout << "Strength:  " << static_cast<int>(aPlayer.GetBaseAttributes().strength) << "/99" << "\n";
        std::cout << "Agility:   " << static_cast<int>(aPlayer.GetBaseAttributes().agility) << "/99" << "\n";
        std::cout << "Endurance: " << static_cast<int>(aPlayer.GetBaseAttributes().endurance) << "/99" << "\n\n";

        std::cout << "[Derived Attributes] " << "\n";
        std::cout << "Attack Damage: " << static_cast<int>(aPlayer.GetBaseAttributes().damage) << " AD" << " (Strength * Agility)" << "\n";
        std::cout << "Max-Health:    " << static_cast<int>(aPlayer.GetBaseAttributes().maxHealth) << " hp" <<
            " (Endurance * 4 + Strength * 6 + Agility * 3)" << "\n";
        std::cout << "Defense:       " << static_cast<int>(aPlayer.GetBaseAttributes().defense) << " def" << " (Endurance + Agility)" << "\n";
        std::cout << "Carry Capacity: " << static_cast<int>(aPlayer.GetBaseAttributes().carryCapacity) << "kg " << " (Strength + Agility / 3)" <<
            "\n\n";
    }
    // void PrintPlayerAttributes(const Attributes& aAttributes)
    // {
    //     PrintHeader("Player Attributes");
    //     std::cout
    //         << "Strength: "   << aAttributes.strength   << "\n"
    //         << "Agility: "    << aAttributes.agility    << "\n"
    //         << "Endurance: "  << aAttributes.endurance  << "\n"
    //         << "Intellect: "  << aAttributes.intellect  << "\n"
    //         << "Luck: "       << aAttributes.luck       << "\n"
    //         << "Health: "     << aAttributes.health     << "\n"
    //         << "Mana: "       << aAttributes.mana       << "\n";
    // }

    // void PrintInventory( std::vector<Item>& aItems, float aCarryWeight, float aCarryCap)
    // {
    //     PrintHeader("Inventory (" + std::to_string(static_cast<int>(aCarryWeight)) + "/" +
    //                 std::to_string(static_cast<int>(aCarryCap)) + " kg)");
    //     for (size_t i = 0; i < aItems.size(); ++i)
    //     {
    //         std::cout << (i + 1) << ") " << aItems[i].GetName()
    //                   << " (" << aItems[i].GetWeight() << "kg)\n";
    //     }
    // }
    //
    // void PrintEquipment(const std::vector<Item>& aEquipped)
    // {
    //     PrintHeader("Equipped Items");
    //     for (const auto& item : aEquipped)
    //     {
    //         std::cout << "- " << item.GetName() << "\n";
    //     }
    // }
    //
    // void PrintActiveSpells(const std::vector<Spell>& aActiveSpells)
    // {
    //     PrintHeader("Active Spells");
    //     for (const auto& spell : aActiveSpells)
    //     {
    //         std::cout << "- " << spell.GetName() << "\n";
    //     }
    // }

    // void PrintRoomOverview(const Room& aRoom)
    // {
    //     PrintHeader("Room Overview");
    //     std::cout << "Room ID: " << aRoom.GetId() << "\n";
    //     std::cout << "Enemies: " << aRoom.GetEnemies().size() << "\n";
    //     std::cout << "Chests: " << aRoom.GetChests().size() << "\n";
    // }
    //
    // void PrintEnemies(const std::vector<Enemy>& aEnemies)
    // {
    //     PrintHeader("Enemies");
    //     for (size_t i = 0; i < aEnemies.size(); ++i)
    //     {
    //         std::cout << (i + 1) << ") " << aEnemies[i].GetName()
    //                   << " (HP: " << aEnemies[i].GetAttributes().health << ")\n";
    //     }
    // }
    //
    // void PrintDoors(const std::vector<Door>& aDoors)
    // {
    //     PrintHeader("Doors");
    //     for (size_t i = 0; i < aDoors.size(); ++i)
    //     {
    //         std::cout << (i + 1) << ") " << aDoors[i].GetDirectionString()
    //                   << (aDoors[i].IsLocked() ? " [Locked]" : "") << "\n";
    //     }
    // }
}


//
