#include "Enemy.h"
#include "Player.h"
#include "Utils.h"

#include <iostream>
#include <string>

using namespace Utils;
using namespace EnemyDB;

Enemy::Enemy()
{
}

Enemy::Enemy(EnemyType aType) :
	myId(),
	myAttributes{ GetDef(aType).myType, GetDef(aType).myName, GetDef(aType).myDamage, GetDef(aType).myMaxHealth },
	myCurrentHealth(GetDef(aType).myMaxHealth),
	myIsDead(false)
{
}

const EnemyAttributes& EnemyDB::GetDef(EnemyType aType)
{
	return EnemyDef[static_cast<int>(aType)];
}


float Enemy::GetMaxHealth() const
{
	return myAttributes.myMaxHealth;
}

float Enemy::GetDamage() const
{
	return myAttributes.myDamage;
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
		IsDead();
	}
}

void Enemy::Attack(Player& player) const
{
	const int dmg = static_cast<int>(GetDamage() / player.GetDefenseMultiplier());
	const int blockedDmg = static_cast<int>(GetDamage() - dmg);

	player.TakeDamage(dmg);

	std::cout << myAttributes.myName << " dealt "
		<< "" << dmg << " dmg to you"
		<< " [" << blockedDmg << " blocked damage]\n";
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
	return myAttributes.myType;
}

const char* Enemy::GetName() const
{
	return myAttributes.myName;
}

