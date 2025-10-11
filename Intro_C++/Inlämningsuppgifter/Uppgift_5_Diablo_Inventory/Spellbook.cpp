#include "Spellbook.h"

#include <algorithm>
#include <iostream>


Spellbook::Spellbook() : mySpells(), myAttributes()
{
}

void Spellbook::UpdateAttributes()
{
    myAttributes.Clear();
    for (const auto& spell : GetActiveSpells())
    {
        myAttributes += spell->GetAttributes();
    }
}

void Spellbook::AddSpell(const Spell& aSpell)
{
    std::cout << "\n";
    aSpell.PrintSpellName();
    std::cout << " has been added to Spellbook!\n";
    mySpells.push_back(aSpell);
}

void Spellbook::ApplySpell(int aSpellId)
{
    auto& spell = FindSpell(aSpellId);
    if (!spell.GetState().isActive)
    {
        spell.ActivateSpell();
        std::cout << "\n";
        spell.PrintSpellName();
        std::cout << " spell buff has been applied\n";
        UpdateAttributes();
    }
}

void Spellbook::RemoveSpell(int aSpellId)
{
    std::erase_if(mySpells, [aSpellId](const Spell& spell)
    {
        return spell.GetId() == aSpellId && spell.GetState().isActive;
    });
    UpdateAttributes();
}

void Spellbook::UpdateSpellsOnHitCount()
{
    for (auto& spell : mySpells)
    {
        if (spell.GetState().isActive)
        {
            spell.UpdateOnHitCount();
            if (spell.GetSpellFinished())
            {
                RemoveSpell(spell.GetId());
            }
        }
    }
}

Spell& Spellbook::FindSpell(int aSpellId)
{
    auto it = std::ranges::find_if(mySpells, [aSpellId](const Spell& spell)
    {
        return spell.GetId() == aSpellId;
    });
    if (it != mySpells.end())
    {
        return *it;
    }
    auto& spell = *it;
    return spell;
}

std::vector<const Spell*> Spellbook::GetInactiveSpells() const
{
    std::vector<const Spell*> spells;
    spells.reserve(mySpells.size());
    for (const auto& spell : mySpells)
    {
        if (!spell.GetState().isActive)
        {
            spells.push_back(&spell);
        }
    }
    return spells;
}

std::vector<const Spell*> Spellbook::GetActiveSpells() const
{
    std::vector<const Spell*> spells;
    spells.reserve(mySpells.size());
    for (const auto& spell : mySpells)
    {
        if (spell.GetState().isActive)
        {
            spells.push_back(&spell);
        }
    }
    return spells;
}

void Spellbook::PrintSpells() const
{
    std::cout << "\n<--- Spellbook --->\n";
    const auto inactive = GetInactiveSpells();
    if (inactive.empty())
    {
        std::cout << "Empty...\n";
    }
    else
    {
        for (int i = 0; i < static_cast<int>(inactive.size()); i++)
        {
            std::cout << i + 1 << ") ";
            inactive[i]->PrintSpellOnDisplay();
            std::cout << " \n";
        }
    }

    std::cout << "\n<--- Active Spells --->\n";
    const auto active = GetActiveSpells();
    if (active.empty())
    {
        std::cout << "Empty...\n";
    }
    else
    {
        for (const auto* spell : active)
        {
            spell->PrintSpellOnDisplay();
            std::cout << " \n";
        }
    }

    std::cout << inactive.size() + 1 << ") Return\n"
        << "Choice: ";
}
