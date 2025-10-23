#include "Utils.h"
#include "GameEnums.h"
#include "GameConstants.h"
#include <iostream>

namespace Utils
{
    RandomGeneratorState::RandomGeneratorState(unsigned int seed)
        : rng(seed)
    {
    }

    int GenerateRandomNumber(int aMin, int aMaxValue)
    {
        std::uniform_int_distribution<int> dist(aMin, aMaxValue);
        return dist(myRng.rng);
    }

    int ReadIntInRange(int aMinValue, int aMaxValue)
    {
        int value;
        while (true)
        {
            std::cin >> value;
            if (value >= aMinValue && value <= aMaxValue)
            {
                return value;
            }
            std::cin.clear();
            std::cin.ignore(CIN_IGNORE, '\n');
            std::cout << "Invalid. Enter a number between " << aMinValue << " and " << aMaxValue << ": ";
        }
    }

    Position GetPosFromDirection(const Direction& aDirection)
    {
        switch (aDirection)
        {
            case Direction::West:
            {
                return {-1, 0};
            }
            case Direction::North:
            {
                return {0, 1};
            }
            case Direction::East:
            {
                return {1, 0};
            }
            case Direction::South:
            {
                return {0, -1};
            }
            case Direction::None:
            {
                return {0, 0};
            }
        }
        return {0, 0};
    }


    const char* GetColorCode(TextColor color, bool aStart)
    {
        if (!aStart)
            return "\x1b[0m"; // reset

        switch (color)
        {
            case TextColor::Red:
            {
                return "\x1b[31m"; // Red
            }
            case TextColor::Brown:
            {
                return "\x1b[38;5;94m"; // Brown-ish (ANSI only has yellow, looks like dark brown on some terms)
            }
            case TextColor::Silver:
            {
                return "\x1b[38;5;117m"; //"\x1b[38;5;250m"; // White/grey
            }
            case TextColor::Gold:
            {
                return "\x1b[38;5;178m"; // Bright yellow (gold-like)
            }
            case TextColor::Magenta:
            {
                return "\x1b[38;5;201m"; // Magenta
            }
            default:
            {
                return "\x1b[0m"; // fallback reset
            }
        }
    }

    TextColor GetColorFromRarity(Rarity rarity) //none = red
    {
        return static_cast<TextColor>(rarity);
    }

    const char* RarityToString(Rarity rarity)
    {
        switch (rarity)
        {
            case Rarity::Bronze:
            {
                return "Bronze";
            }
            case Rarity::Silver:
            {
                return "Silver";
            }
            case Rarity::Gold:
            {
                return "Gold";
            }
            case Rarity::Legendary:
            {
                return "Legendary";
            }
        }
        return nullptr;
    }

    std::string LockTypeToString(const LockType& aLockType)
    {
        switch (aLockType)
        {
            case LockType::Unlocked:
            {
                return "Unlocked";
            }
            case LockType::Agility:
            {
                return "Agility";
            }
            case LockType::Strength:
            {
                return "Strength";
            }
            case LockType::None:
            {
                return "none";
            }
        }
        return "";
    }

    const char* GetPrefixSign(float aValue)
    {
        return aValue > 0 ? "+" : ""; // when value < 0 then it will show subtract sign so no need for double --
    }

    std::vector<Rarity> GetRaritiesFromMax(Rarity aRarity)
    {
        std::vector<Rarity> out;
        const int max = static_cast<int>(aRarity);
        out.reserve(max + 1);
        for (int i = 0; i <= max; ++i)
        {
            // note: <=
            out.push_back(static_cast<Rarity>(i));
        }
        return out;
    }
}
