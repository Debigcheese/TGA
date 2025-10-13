#pragma once
#include "GameStructs.h"
#include "Inventory.h"
#include "Spellbook.h"
#include <string>
#include <cmath>

#include "WorldMap.h"

class WorldMap;
class Spell;
class Item;

class Player
{
public:
	Player(WorldMap& aWorldMap);

	void TakeDamage(const float aDamage, const std::string aEnemyName);

	void AddSpell(const Spell& aSpell) { mySpellBook.AddSpell(aSpell); }
	void ActivateSpell(int aSpellId) { mySpellBook.ApplySpell(aSpellId); }
	void HealFullHealth() { myAttributes.currentHealth = GetAttributes().maxHealth; }

	float GetDefenseMultiplier() const;

	float GetDamage() const;
	float GetMaxHealth() const;
	float GetCarryCapacity() const;
	float GetDefense() const;
	Attributes GetBaseAttributes() const;
	Attributes GetBuffedAttributes() const;
	Attributes GetAttributes() const;

	bool CanPickupItem(const Item& aItem) const;
	void PickupItem(const Item& aItem) { myInventory.AddItem(aItem); }
	void DropItem(int aItemId) { myInventory.DropItem(aItemId); }
	void UnequipItem(int aSlotIndex) { myInventory.UnequipItem(aSlotIndex); }
	void EquipItem(int aItemId) { myInventory.EquipItem(aItemId); }
	const Inventory& GetInventory() const { return myInventory; }
	const Equipment& GetEquipment() const { return myInventory.GetEquipment(); }
	const Spellbook& GetSpellBook() const { return mySpellBook; }

	void SetName(const std::string& aNewName) { myName = aNewName; }
	std::string GetName() const { return myName; }

	bool IsDead() const { return myIsDead; }
	void SetIsDead(bool aIsDead) { myIsDead = aIsDead; }

	//nav
	int GetRoomId() const { return myRoomId; }
	void SetRoomId(const int& aNewRoomId) { myRoomId = aNewRoomId; }
	Position GetPosition() const { return myPos; }
	void SetPosition(const Position& aNewPosition) { myPos = aNewPosition; }

private:
	//CONSTANTS
	static constexpr float DEFAULT_BASE_ATTRIBUTE = 8.0f;
	WorldMap& myWorldMap;
	Inventory myInventory;
	Spellbook mySpellBook;
	std::string myName;
	Attributes myAttributes{};
	int myRoomId;
	bool myIsDead;
	Position myPos;
};
