#include "Enemy.h"

#include "Player.h"
#include "Utils.h"

#include <iostream>
#include <string>

using namespace Utils;

Enemy::Enemy()
{
}

Enemy::Enemy(float aMaxHealth, float aDamage, EnemyType aType) :
	myId(0),
	myAttributes{ aMaxHealth,aDamage },
	myCurrentHealth(aMaxHealth),
	myType(aType),
	myIsDead(false)
{
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
	if (myCurrentHealth <= 0.0f)
	{
		myCurrentHealth = 0.0f;
		myIsDead = true;
		IsDead();
	}
}

void Enemy::Attack(Player& player) const
{
	const int dmg = static_cast<int>(GetDamage() / player.GetDefenseMultiplier());
	const int blockedDmg = static_cast<int>(GetDamage() - dmg);

	player.TakeDamage(dmg);

	std::cout << EnemyTypeToString(myType) << " dealt "
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
	return myType;
}



