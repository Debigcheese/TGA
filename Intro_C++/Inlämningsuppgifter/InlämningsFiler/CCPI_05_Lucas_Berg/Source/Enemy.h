#pragma once
#include "GameConstants.h"
#include "Item.h"
#include "EnemyType.h"

#include <vector>

using namespace GameConstants;
class Player;
class Room;

class Enemy
{
public:
	Enemy(EnemyType* aEnemyType, int aId);
	void TakeDamage(const float aDamage);
	void Attack(Player& player) const;

	void OnDeath(Room* aCurrentRoom);
	void DropItem(Room* aCurrentRoom);
	void SetDropItems(const std::vector<Item>& aItems);
	bool HasItems() const { return !myItems.empty(); }

	EnemyAttributes GetEnemyAttributes() const { return myEnemyType->GetAttributes(); }
	float GetCurrentHealth() const { return myCurrentHealth; }
	bool IsDead() const { return myIsDead; }
	int GetId() const;

private:
	int myId;
	EnemyType* myEnemyType;
	float myCurrentHealth;
	bool myIsDead;
	std::vector<Item> myItems;
};
