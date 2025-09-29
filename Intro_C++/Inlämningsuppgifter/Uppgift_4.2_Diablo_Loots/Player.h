#pragma once
#include "GameStructs.h"
#include "Cheats.h"
#include <string>
#include <vector>

#include "Spell.h"

using namespace Cheats;

class WorldMap;
class Enemy;
class Item;

class Player
{
public:
	Player(WorldMap& aWorldMap);

	void Attack();
	void ChooseTarget();
	void ChooseAttack();
	void TakeDamage(const float aDamage);
	bool CanPickupItem(const Item& aItem) const;
	float GetInventoryWeight() const;
	void AddItemToInventory(const Item& aItem);
	void RemoveFromInventory(int aIndex);
	void UpdateAttributes();
	void ApplySpell(const Spell& aSpell);
	void RemoveSpell(int aIndex);

	float GetDamageFromAttackType(int aAttackIndex) const;
	int GetRoomId() const;
	void SetRoomId(const int& aNewRoomId);
	void SetName(const std::string& aNewName);
	void SetIsDead(bool aIsDead);
	void SetPosition(const Position& aNewPosition);

	float GetDamage() const;
	float GetMaxHealth() const;
	float GetCarryCapacity() const;
	float GetDefense() const;
	const Attributes& GetBaseAttributes() const;
	Attributes GetAttributes() const;

	void SetAttackIndex(int aAttackIndex) { myAttackIndex = aAttackIndex; }
	void SetTargetIndex(int aTargetIndex) { myTargetIndex = aTargetIndex; }
	int GetAttackIndex() const { return myAttackIndex; }
	int GetTargetIndex() const { return myTargetIndex; }
	float GetDefenseMultiplier() const;
	bool IsDead() const;
	bool IsInvalidAttackIndex() const;
	std::string GetName() const;
	Position GetPosition() const;
	std::vector<Item> GetInventory() const;
	std::vector<Spell> GetSpells() const;

	void PrintHealth() const;
	void PrintUserName() const;
	void PrintPlayerUI() const;
	void PrintAttributes() const;
	void PrintBaseAttributes() const;
	void PrintDerivedAttributes() const;
	void PrintInventory() const;

private:
	//CONSTANTS
	static constexpr float DEFAULT_BASE_ATTRIBUTE = 10.0f;

	WorldMap& myWorldMap;
	std::string myName;
	Attributes myAttributes{};
	Attributes myBuffedAttributes{};
	int myRoomId;
	int myTargetIndex;
	int myAttackIndex;
	bool myIsDead;
	Position myPos;
	std::vector<Item> myInventory;
	std::vector<Spell> mySpells;
};
