#include "Enemy.h"

Enemy::Enemy(float aMaxHealth, float aDamage) :
	myMaxHealth(aMaxHealth),
	myCurrentHealth(aMaxHealth),
	myDamage(aDamage),
	myIsDead(false)
{

}

float Enemy::GetMaxHealth() const
{
	return myMaxHealth;
}

float Enemy::GetDamage() const
{
	return myDamage;
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

bool Enemy::IsDead() const
{
	return myIsDead;
}

