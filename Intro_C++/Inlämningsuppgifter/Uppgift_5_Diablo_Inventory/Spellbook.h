#pragma once
#include "Spell.h"

#include <vector>

class Spellbook
{
public:
	Spellbook();

	void UpdateAttributes();
	void AddSpell(const Spell& aSpell);
	void ApplySpell(int aSpellId);
	void RemoveSpell(int aSpellId);
	void UpdateSpellsOnHitCount();

	const Attributes& GetAttributes() const { return myAttributes; }
	Spell& GetSpellAt(int aSpellId);
	std::vector<const Spell*> GetInactiveSpells() const; // make it into ids and make a getspells, dont use pointers
	std::vector<const Spell*> GetActiveSpells() const;
	void PrintSpells() const;

private:
	std::vector<Spell> mySpells;
	Attributes myAttributes{};
};
