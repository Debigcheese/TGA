#pragma once
#include "GameStructs.h"
#include "Cheats.h"
#include <string>
#include <vector>

using namespace Cheats;

class WorldMap;
class Enemy;
class Item;

class Player
{
public:
	Player(WorldMap& aWorldMap);
	void Update();
	void EnterCombat();
	void ChooseTarget();
	void ChooseAttack();
	void TakeDamage(const float aDamage);
	void EnterAttributesMenu() const;

	float GetDamageFromAttackType(int aAttackIndex) const;
	int GetRoomId() const;
	void SetRoomId(const int& aNewRoomId);
	void SetName(const std::string& aNewName);
	void SetIsDead(bool aIsDead);
	void SetPosition(const Position& aNewPosition);
	void SetItemAttributes(const Attributes& aItemAttributes);

	float GetDamage() const;
	float GetMaxHealth() const;
	float GetCarryCapacity() const;
	float GetDefense() const;
	const Attributes& GetBaseAttributes() const;
	Attributes GetAttributes() const;

	float GetDefenseMultiplier() const;
	bool IsDead() const;
	bool IsInvalidAttackIndex() const;
	std::string GetName() const;
	Position GetPosition() const;

	void PrintHealth() const;
	void PrintUserName() const;
	void PrintPlayerUI() const;
	void PrintAttributes() const;
	void PrintBaseAttributes() const;
	void PrintDerivedAttributes() const;

private:
	//CONSTANTS
	static constexpr float DEFAULT_BASE_ATTRIBUTE = 10.0f;

	WorldMap& myWorldMap;
	std::string myName;
	Attributes myAttributes{};
	Attributes myItemAttributes{};
	int myRoomId;
	int myTargetIndex;
	int myAttackIndex;
	bool myIsDead;
	Position myPos;
	std::vector<Item*> myInventory;
};
