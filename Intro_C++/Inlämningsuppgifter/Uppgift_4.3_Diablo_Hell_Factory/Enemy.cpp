#include "Enemy.h"
#include "Player.h"
#include "Utils.h"
#include "Room.h"
#include <iostream>

using namespace Utils;

Enemy::Enemy(const EnemyAttributes& aAttributes, int aId)
	: myId(aId),
	  myAttributes(aAttributes),
	  myCurrentHealth(aAttributes.maxHealth),
	  myIsDead(false),
	  myItems({})

{
}

float Enemy::GetMaxHealth() const
{
	return myAttributes.maxHealth;
}

float Enemy::GetDamage() const
{
	return myAttributes.damage;
}

float Enemy::GetCurrentHealth() const
{
	return myCurrentHealth;
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

bool Enemy::HasItems() const
{
	return !myItems.empty();
}

void Enemy::Attack(Player& player) const
{
	const float dmgFloat = GetDamage() / player.GetDefenseMultiplier();
	const int dmg = static_cast<int>(dmgFloat);
	const int blockedDmg = static_cast<int>(GetDamage()) - dmg;

	std::cout << myAttributes.name << " dealt "
		<< "" << static_cast<int>(dmg) << " dmg to you"
		<< " [" << blockedDmg << " blocked damage]\n";

	player.TakeDamage(dmgFloat);
}

bool Enemy::IsDead() const
{
	return myIsDead;
}

void Enemy::SetId(int aId)
{
	myId = aId;
}

int Enemy::GetId() const
{
	return myId;
}

EnemyType Enemy::GetType() const
{
	return myAttributes.type;
}

const char* Enemy::GetName() const
{
	return myAttributes.name;
}
