#include "Spellbook.h"

#include <algorithm>
#include <iostream>


Spellbook::Spellbook() : mySpells(), myAttributes()
{
}

void Spellbook::UpdateAttributes()
{
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
	auto& spell = GetSpellAt(aSpellId);
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

Spell& Spellbook::GetSpellAt(int aSpellId)
{
	auto it = std::ranges::find_if(mySpells, [aSpellId](const Spell& spell)
	{
		return spell.GetId() == aSpellId;
	});
	if (it != mySpells.end())
	{
	}
	auto& spell = *it;
	return spell;
}

std::vector<int> Spellbook::GetInactiveSpells() const
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
	spells.shrink_to_fit();
	return spells;
}

std::vector<int> Spellbook::GetActiveSpells() const
{
	std::vector<const Spell*> spells;
	spells.reserve(mySpells.size());
	for (auto spell : mySpells)
	{
		if (spell.GetState().isActive)
		{
			spells.push_back(&spell);
		}
	}
	spells.shrink_to_fit();
	return spells;
}

void Spellbook::PrintSpells() const
{
	std::cout << "\n<--- Spellbook --->\n";
	if (GetInactiveSpells().empty())
	{
		std::cout << "Empty...\n";
	}
	else
	{
		for (int i = 0; i < static_cast<int>(GetInactiveSpells().size()); i++)
		{
			std::cout << i + 1 << ") ";
			GetInactiveSpells()[i]->PrintSpellOnDisplay();
			std::cout << " \n";
		}
	}

	std::cout << "\n<--- Active Spells --->\n";

	if (GetActiveSpells().empty())
	{
		std::cout << "Empty...\n";
	}
	else
	{
		for (const auto& spell : GetActiveSpells())
		{
			spell->PrintSpellOnDisplay();
			std::cout << " \n";
		}
	}

	std::cout << GetInactiveSpells().size() + 1 << ") Return\n"
		<< "Choice: ";
}
