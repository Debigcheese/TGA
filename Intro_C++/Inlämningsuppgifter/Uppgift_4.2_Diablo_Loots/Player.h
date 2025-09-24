#pragma once
#include "GameStructs.h"
#include "GameEnums.h"
#include "Cheats.h"
#include <vector>
#include <string>

using namespace Cheats;

class WorldMap;
class Enemy;

class Player
{
public:
	Player(WorldMap& aWorldMap);
	void Update();
	void EnterCombat();
	void ChooseTarget();
	void ChooseAttack();
	void TakeDamage(const float aDamage);
	void EnterAttributesMenu();

	float GetDamageFromAttackType(const int& aAttackIndex) const;
	int GetRoomId() const;
	void SetRoomId(const int& aNewRoomId);
	void SetName(std::string aNewName);

	float GetDamage() const;
	float GetMaxHealth() const;
	float GetCurrentHealth() const;
	float GetCarryCapacity() const;
	float GetDefense() const;
	float GetDefenseMultiplier() const;
	bool IsDead() const;
	bool IsInvalidAttackIndex() const;
	std::string GetName() const;
	PlayerAttributes GetAttributes() const;

	void PrintTarget(const Enemy& aEnemy) const;
	void PrintHealth() const;
	void PrintUserName() const;
	void PrintPlayerUI() const;
	void PrintAttributes() const;
	void PrintDerivedAttributes() const;

private:
	WorldMap& myWorldMap;
	std::string myName;
	PlayerAttributes myAttributes{};
	int myRoomId;
	int myTargetIndex;
	int myAttackIndex;
	bool myIsDead;
};

