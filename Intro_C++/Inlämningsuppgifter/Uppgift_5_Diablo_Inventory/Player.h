#pragma once
#include "GameStructs.h"
#include "Cheats.h"
#include "Spell.h"
#include "Inventory.h"

#include <string>
#include <vector>
#include <cmath>

class WorldMap;
class Enemy;
class Item;

class Player
{
public:
	Player(WorldMap& aWorldMap);

	void Attack() const;
	void ChooseTarget();
	void ChooseAttack();
	void TakeDamage(const float aDamage);

	void ApplySpell(const Spell& aSpell) { mySpells.push_back(aSpell); }
	void RemoveSpell(int aIndex) { mySpells.erase(mySpells.begin() + aIndex); }
	void HealFullHealth() { myAttributes.currentHealth = GetAttributes().maxHealth; }

	float GetDamageFromAttackType(int aAttackIndex) const;
	float GetDefenseMultiplier() const;
	bool IsInvalidAttackIndex() const;

	float GetDamage() const;
	float GetMaxHealth() const;
	float GetCarryCapacity() const;
	float GetDefense() const;
	const Attributes& GetBaseAttributes() const;
	const Attributes& GetBuffedAttributes() const;
	Attributes GetAttributes() const;

	bool CanPickupItem(const Item& aItem) const;
	void PickupItem(const Item& aItem) { myInventory.AddItem(aItem); }
	void DropItem(int aItemId) { myInventory.DropItem(aItemId); }
	void UnequipItem(int aSlotIndex) { myInventory.UnequipItem(aSlotIndex); }
	void EquipItem(int aItemId) { myInventory.EquipItem(aItemId); }
	const Inventory& GetInventory() const { return myInventory; }
	const Equipment& GetEquipment() const { return myInventory.GetEquipment(); }

	std::vector<Spell> GetSpells() const { return mySpells; }

	void SetName(const std::string& aNewName) { myName = aNewName; }
	std::string GetName() const { return myName; }

	//combat
	void SetAttackIndex(int aAttackIndex) { myAttackIndex = aAttackIndex; }
	void SetTargetIndex(int aTargetIndex) { myTargetIndex = aTargetIndex; }
	int GetAttackIndex() const { return myAttackIndex; }
	int GetTargetIndex() const { return myTargetIndex; }
	bool IsDead() const { return myIsDead; }
	void SetIsDead(bool aIsDead) { myIsDead = aIsDead; }

	//nav
	int GetRoomId() const { return myRoomId; }
	void SetRoomId(const int& aNewRoomId) { myRoomId = aNewRoomId; }
	Position GetPosition() const { return myPos; }
	void SetPosition(const Position& aNewPosition) { myPos = aNewPosition; }

	void PrintHealth() const;
	void PrintUserName() const;
	void PrintPlayerUI() const;
	void PrintAttributes() const;
	void PrintBaseAttributes() const;
	void PrintDerivedAttributes() const;
	void PrintSpells() const;

private:
	//CONSTANTS
	static constexpr float DEFAULT_BASE_ATTRIBUTE = 8.0f;

	WorldMap& myWorldMap;
	Inventory myInventory;
	std::string myName;
	Attributes myAttributes{};
	int myRoomId;
	int myTargetIndex;
	int myAttackIndex;
	bool myIsDead;
	Position myPos;
	std::vector<Spell> mySpells;
};
