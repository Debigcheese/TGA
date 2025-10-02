#include "Enemy.h"
#include "Player.h"
#include "Utils.h"
#include "Room.h"
#include <iostream>

using namespace Utils;

Enemy::Enemy(EnemyType* aEnemyType, int aId)
	: myId(aId),
	  myIsDead(false),
	  myItems({})
{
	myEnemyType = aEnemyType;
	myCurrentHealth = myEnemyType->GetAttributes().maxHealth;
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
	const float dmgFloat = myEnemyType->GetAttributes().damage / player.GetDefenseMultiplier();
	const int dmg = static_cast<int>(dmgFloat);
	const int blockedDmg = static_cast<int>(myEnemyType->GetAttributes().damage) - dmg;

	std::cout << myEnemyType->GetAttributes().name << " dealt "
		<< "" << static_cast<int>(dmg) << " dmg to you"
		<< " [" << blockedDmg << " blocked damage]\n";

	player.TakeDamage(dmgFloat);
}
