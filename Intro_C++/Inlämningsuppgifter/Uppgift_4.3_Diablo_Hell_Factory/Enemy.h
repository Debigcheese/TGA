#pragma once
#include "GameStructs.h"
#include "GameEnums.h"
#include "GameConstants.h"
#include "Item.h"

#include <vector>

using namespace GameConstants;
class Player;
class Room;

class Enemy
{
public:
	Enemy(const EnemyAttributes& aAttributes, int aId);
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
