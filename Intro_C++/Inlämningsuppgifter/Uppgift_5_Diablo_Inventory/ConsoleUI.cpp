#include "ConsoleUI.h"
#include "Utils.h"
#include "Player.h"
#include "Spell.h"

#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>

#include "CombatController.h"

using namespace Utils;
using namespace std::chrono_literals;

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

    void WaitForSeconds(int aSecond)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(aSecond));
    }

    void PrintOneLiner(std::string Line)
    {
        std::cout << Line;
    }

    void PrintUI(const Player& aPlayer, const Room* aCurrentRoom)
    {
        Clear();
        PrintPlayerUI(aPlayer, aCurrentRoom);
        PrintEnemies(aCurrentRoom);
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
            PrintSpellOnDisplay(aSpells[i]);
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
        std::cout << "\n";
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
        std::cout << "Carry Capacity: " << static_cast<int>(aPlayer.GetBaseAttributes().carryCapacity) << "kg" <<
            "\n\n";
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
        std::cout << "Attack Damage: " << static_cast<int>(aPlayer.GetBaseAttributes().damage) << " AD" <<
            " (Strength * Agility)" << "\n";
        std::cout << "Max-Health:    " << static_cast<int>(aPlayer.GetBaseAttributes().maxHealth) << " hp" <<
            " (Endurance * 4 + Strength * 6 + Agility * 3)" << "\n";
        std::cout << "Defense:       " << static_cast<int>(aPlayer.GetBaseAttributes().defense) << " def" <<
            " (Endurance + Agility)" << "\n";
        std::cout << "Carry Capacity: " << static_cast<int>(aPlayer.GetBaseAttributes().carryCapacity) << "kg " <<
            " (Strength + Agility / 3)" <<
            "\n\n";
    }

    void PrintDoorLock(const Lock& aLock)
    {
        std::cout << "\n<--- Door is Locked --->\n";
        std::cout << "Required " << LockTypeToString(aLock.agilityReq.lockType) << ": "
            << aLock.agilityReq.attributeValue << " to lock-pick the door\n";

        std::cout << "Required " << LockTypeToString(aLock.strengthReq.lockType) << ": "
            << aLock.strengthReq.attributeValue << " to break open the door\n";
    }

    void PrintLockMenu()
    {
        std::cout
            << "1) Try Lock-Pick\n"
            << "2) Try Breaking\n"
            << "3) Return\n"
            << "Choice: ";
    }

    void PrintCombatUI(const CombatController& aCombatController, const Player& aPlayer, const Room* aCurrentRoom)
    {
        const AttackData& data = aCombatController.GetAttackData();

        Clear();
        PrintPlayerUI(aPlayer, aCurrentRoom);

        const std::vector<Enemy>& enemies = aCurrentRoom->GetEnemies();
        if (aCombatController.IsInvalidAttackIndex())
        {
            PrintEnemies(aCurrentRoom);
            return;
        }
        const auto& targetEnemy = enemies[data.targetIndex];
        if (targetEnemy.IsDead())
        {
            return;
        }
        PrintEnemiesWithTarget(data.targetIndex, aCurrentRoom);
    }

    void PrintAttackTypeInfo(const CombatController& aCombatController, const Player& aPlayer)
    {
        std::cout << "\n<--- Attack Info --->\n"
            << "Quick Attack ["
            << aPlayer.GetAttributes().damage
            << "] AD - fixed damage.\n"
            << "Heavy Attack ["
            << aCombatController.GetHeavyDamageRange().min
            << " - " << aCombatController.GetHeavyDamageRange().max
            << "] AD - random within range.\n"
            << "Slash Attack ["
            << static_cast<int>(aCombatController.GetSlashDamage())
            << "] AD - hits all enemies.\n\n";
        Pause();
    }

    void PrintRoomName(const Room* aCurrentRoom)
    {
        std::cout << "Room: " << aCurrentRoom->GetRoomName();
    }

    void PrintEnemies(const Room* aCurrentRoom)
    {
        const auto& enemies = aCurrentRoom->GetEnemies();

        if (static_cast<int>(enemies.size()) <= ARRAY_COUNT_ZERO)
        {
            std::cout << "\n[No monsters in room]\n";
            return;
        }
        std::cout << "\n[Monsters in room]\n";
        for (int i = 0; i < static_cast<int>(enemies.size()); i++)
        {
            std::cout << "[" << i + ARRAY_INDEX_OFFSET << "]" << " - "
                << enemies[i].GetEnemyAttributes().name << ": "
                << static_cast<int>(enemies[i].GetCurrentHealth()) << "/"
                << static_cast<int>(enemies[i].GetEnemyAttributes().maxHealth) << " hp | "
                << static_cast<int>(enemies[i].GetEnemyAttributes().damage) << " AD" << "\n";
        }
    }

    void PrintEnemiesWithTarget(int aTargetIndex, const Room* aCurrentRoom)
    {
        const auto& enemies = aCurrentRoom->GetEnemies();
        if (static_cast<int>(enemies.size()) <= ARRAY_COUNT_ZERO)
        {
            std::cout << "\n[No monsters in room]\n";
            return;
        }

        auto RED = "\x1b[31m";
        auto RESET = "\x1b[0m";
        std::cout << "\n[Monsters in room]\n";
        for (int i = 0; i < static_cast<int>(enemies.size()); i++)
        {
            if (aTargetIndex == i)
            {
                RED = "\x1b[31m";
                RESET = "\x1b[0m";
            }
            else
            {
                RED = "";
                RESET = "";
            }
            std::cout << RED
                << "[" << i + ARRAY_INDEX_OFFSET << "]" << " - "
                << enemies[i].GetEnemyAttributes().name << ": "
                << static_cast<int>(enemies[i].GetCurrentHealth()) << "/"
                << static_cast<int>(enemies[i].GetEnemyAttributes().maxHealth) << " hp | "
                << static_cast<int>(enemies[i].GetEnemyAttributes().damage) << " AD"
                << RESET << "\n";
        }
    }

    void PrintSpellAttributes(const Spell& aSpell)
    {
        const auto& spell = aSpell;
        // Print non-zero attributes
        const Attributes& a = aSpell.GetAttributes();
        if (a.strength != 0.0f)
        {
            std::cout << "Strength: "
                << GetPrefixSign(a.strength)
                << a.strength << "\n";
        }
        if (a.agility != 0.0f)
        {
            std::cout << "Agility: "
                << GetPrefixSign(a.agility)
                << a.agility << "\n";
        }
        if (a.endurance != 0.0f)
        {
            std::cout << "Endurance: "
                << GetPrefixSign(a.endurance)
                << a.endurance << "\n";
        }
        if (a.maxHealth != 0.0f)
        {
            std::cout << "Max Health: "
                << GetPrefixSign(a.maxHealth)
                << a.maxHealth << "\n";
        }
        if (a.currentHealth != 0.0f)
        {
            std::cout << "Current Health: "
                << GetPrefixSign(a.currentHealth)
                << a.currentHealth << "\n";
        }
        if (a.carryCapacity != 0.0f)
        {
            std::cout << "Carry Capacity: "
                << GetPrefixSign(a.carryCapacity)
                << a.carryCapacity << "\n";
        }
        if (a.damage != 0.0f)
        {
            std::cout << "Damage: "
                << GetPrefixSign(a.damage)
                << a.damage << "\n";
        }
        if (a.defense != 0.0f)
        {
            std::cout << "Defense: "
                << GetPrefixSign(a.defense)
                << a.defense << "\n";
        }
        std::cout << "Hit Count: "
            << spell.GetState().hitCount
            << "/"
            << spell.GetHitCount() << "\n";
    }

    void PrintSpellOnPickup(const Spell& aSpell)
    {
        const auto& spell = aSpell;
        std::cout << GetColorCode(GetColorFromRarity(spell.GetSpellAttributes().rarity), true)
            << "\n<------ " << RarityToString(spell.GetSpellAttributes().rarity) << " ------>"
            << GetColorCode(GetColorFromRarity(spell.GetSpellAttributes().rarity), false)
            << "\n"
            << "         {" << spell.GetSpellAttributes().name << "}" << "\n";

        PrintSpellAttributes(spell);

        std::cout << "\n";
    }

    void PrintSpellOnDisplay(const Spell& aSpell)
    {
        const auto& spell = aSpell;
        PrintSpellName(spell);
        std::cout << "\n";
        PrintSpellAttributes(spell);
    }

    void PrintSpellName(const Spell& aSpell)
    {
        const auto& spell = aSpell;
        std::cout << GetColorCode(GetColorFromRarity(spell.GetSpellAttributes().rarity), true)
            << "{" << spell.GetSpellAttributes().name << "}"
            << GetColorCode(GetColorFromRarity(spell.GetSpellAttributes().rarity), false);
    }
}
