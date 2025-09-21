#include "Enemy.h"
#include "GameStructs.h"
#include "GameEnums.h"
#include "Player.h"
#include "Utils.h"
#include <cmath>
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
	if (myCurrentHealth <= 0)
	{
		myCurrentHealth = 0;
		myIsDead = true;
		IsDead();
	}
}

void Enemy::Attack(Player& player) const
{
	const float raw = GetDamage();
	const float mult = player.GetDefenseMultiplier();          // e.g., 1.0–2.3...
	const int dmg = static_cast<int>(std::round(raw / mult));  // mitigated
	const int blocked = static_cast<int>(std::round(raw - dmg));

	player.TakeDamage(GetDamage());

	std::cout << EnemyTypeToString(myType)
		<< " -" << dmg << " HP"
		<< " [" << blocked << " blocked damage]\n";
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



