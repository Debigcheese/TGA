#pragma once
#include "GameStructs.h"
#include "GameEnums.h"
#include "GameConstants.h"
#include "Item.h"

#include <vector>

using namespace GameConstants;
class Player;
class Room;

namespace EnemyDB
{
	const EnemyAttributes ENEMY_DEF[] = {
		// type , name, dmg, hp
		{EnemyType::None, "None", 0.0f, 0.0f},
		{EnemyType::Bat, "Bat", 5.0f, 40.0f},
		{EnemyType::Skeleton, "Skeleton", 10.0f, 100.0f},
		{EnemyType::Undead, "Undead", 12.0f, 130.0f},
		{EnemyType::Beast, "Beast", 16.0f, 200},
		{EnemyType::Humanoid, "Humanoid", 17.0f, 250.0f},
		{EnemyType::Elemental, "Elemental", 25.0f, 300.0f},
		{EnemyType::Demon, "Demon", 40.0f, 1500.0f},
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

	void DropItem(Room* aCurrentRoom);
	void SetDropItems(const std::vector<Item>& aItems);
	bool HasItems() const;

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
	std::vector<Item> myItems;
};
