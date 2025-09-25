#pragma once
#include "GameStructs.h"
#include "GameEnums.h"
#include "GameConstants.h"

using namespace GameConstants;
class Player;

namespace EnemyDB
{
	const EnemyAttributes EnemyDef[] = {
		// type , name, dmg, hp
		{EnemyType::None, "None", 0.0f, 0.0f},
		{EnemyType::Bat, "Bat", 5.0f, 40.0f},
		{EnemyType::Skeleton, "Skeleton", 10.0f, 100.0f},
		{EnemyType::Undead, "Undead", 12.0f, 130.0f},
		{EnemyType::Beast, "Beast", 16.0f, 200},
		{EnemyType::Humanoid, "Humanoid", 20.0f, 250.0f},
		{EnemyType::Elemental, "Elemental", 30.0f, 300.0f},
		{EnemyType::Demon, "Demon", 50.0f, 500.0f},
	};

	const EnemyAttributes& GetDef(EnemyType aType);
}

class Enemy
{
public:
	Enemy(EnemyType aType);
	void TakeDamage(const float aDamage);
	void Attack(Player& player) const;
	void SetId(int aId);

	float GetMaxHealth() const;
	float GetDamage() const;
	float GetCurrentHealth() const;
	bool IsDead() const;
	int GetId() const;
	EnemyType GetType() const;
	const char* GetName() const;

private:
	int myId;
	EnemyAttributes myAttributes;
	float myCurrentHealth;
	bool myIsDead;
};
