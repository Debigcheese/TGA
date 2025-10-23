#include "Enemy.h"

#include <iostream>

#include "Player.h"
#include "Utils.h"
#include "Room.h"

using namespace Utils;

Enemy::Enemy(EnemyType* aEnemyType, int aId)
	: myId(aId),
	  myIsDead(false),
	  myItems({})
{
	myEnemyType = aEnemyType;
	myCurrentHealth = GetEnemyAttributes().maxHealth;
}

void Enemy::TakeDamage(const float aDamage)
{
	myCurrentHealth -= aDamage;
	if (myCurrentHealth <= HEALTH_ZERO)
	{
		myCurrentHealth = HEALTH_ZERO;
		myIsDead = true;
	}
}

void Enemy::OnDeath(Room* aCurrentRoom)
{
	std::cout << "\n" << GetEnemyAttributes().name << " has been slained!\n";
	if (HasItems())
	{
		std::cout << GetEnemyAttributes().name << " dropped an item!\n";
	}
	DropItem(aCurrentRoom);
}

void Enemy::DropItem(Room* aCurrentRoom)
{
	for (auto& item : myItems)
	{
		aCurrentRoom->AddItemToRoom(item);
	}
	myItems.clear();
}

void Enemy::SetDropItems(const std::vector<Item>& aItems)
{
	for (auto& item : aItems)
	{
		myItems.push_back(item);
	}
}

int Enemy::GetId() const
{
	return myId;
}

void Enemy::Attack(Player& player) const
{
	player.TakeDamage(GetEnemyAttributes().damage, GetEnemyAttributes().name);
}
