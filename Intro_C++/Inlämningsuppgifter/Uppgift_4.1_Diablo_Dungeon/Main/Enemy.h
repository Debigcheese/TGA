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
	{EnemyType::EnemyType_None, "None", 0.0f, 0.0f },
	{EnemyType::EnemyType_Bat, "Bat", 5.0f, 40.0f },
	{EnemyType::EnemyType_Skeleton, "Skeleton", 10.0f, 100.0f},
	{EnemyType::EnemyType_Undead, "Undead", 12.0f, 130.0f},
	{EnemyType::EnemyType_Beast, "Beast", 16.0f, 200},
	{EnemyType::EnemyType_Humanoid, "Humanoid", 20.0f, 250.0f},
	{EnemyType::EnemyType_Elemental, "Elemental", 30.0f, 300.0f},
	{EnemyType::EnemyType_Demon, "Demon", 50.0f, 500.0f},
	};

	const EnemyAttributes& GetDef(EnemyType aType);
}

class Enemy
{
public:
	Enemy();
	Enemy(EnemyType aType);
	void TakeDamage(const float aDamage);
	void Attack(Player& player) const;
	void SetId(int aId);

	float GetMaxHealth() const;
	float GetDamage() const;
	float GetCurrentHealth() const;
	bool IsDead() const;
	int GetId() const;
	EnemyType GetType()const;
	const char* GetName() const;

private:
	int myId;
	EnemyAttributes myAttributes;
	float myCurrentHealth;
	bool myIsDead;
};

